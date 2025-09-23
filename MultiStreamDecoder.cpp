#include "MultiStreamDecoder.h"
#include <QDebug>

MultiStreamDecoder::MultiStreamDecoder(const QString& url, QObject *parent)
    : QThread(parent)
    , m_url(url)
    , m_connected(false)
    , m_paused(false)
    , m_stop(false)
    , m_formatContext(nullptr)
    , m_codecContext(nullptr)
    , m_swsContext(nullptr)
    , m_videoStreamIndex(-1)
{
}

MultiStreamDecoder::~MultiStreamDecoder()
{
    stopDecoding();
    wait(); // 等待线程结束
    cleanupFFmpeg();
}

QImage MultiStreamDecoder::getCurrentFrame()
{
    QMutexLocker locker(&m_frameMutex);
    return m_currentFrame;
}

void MultiStreamDecoder::pauseDecoding()
{
    m_paused = true;
}

void MultiStreamDecoder::resumeDecoding()
{
    m_paused = false;
}

void MultiStreamDecoder::stopDecoding()
{
    m_stop = true;
}

void MultiStreamDecoder::run()
{
    if (!initFFmpeg()) {
        emit errorOccurred("Failed to initialize FFmpeg for: " + m_url);
        return;
    }

    m_connected = true;
    emit connectionStatusChanged(true);

    AVPacket packet;
    AVFrame* frame = av_frame_alloc();
    
    while (!m_stop) {
        if (m_paused) {
            msleep(30);
            continue;
        }

        if (av_read_frame(m_formatContext, &packet) >= 0) {
            if (packet.stream_index == m_videoStreamIndex) {
                if (avcodec_send_packet(m_codecContext, &packet) == 0) {
                    while (avcodec_receive_frame(m_codecContext, frame) == 0) {
                        QImage image = convertFrameToImage(frame);
                        if (!image.isNull()) {
                            {
                                QMutexLocker locker(&m_frameMutex);
                                m_currentFrame = image;
                            }
                            emit frameReady(image);
                        }
                    }
                }
            }
            av_packet_unref(&packet);
        } else {
            // 读取失败，可能是网络中断
            msleep(100);
        }
    }

    av_frame_free(&frame);
    
    m_connected = false;
    emit connectionStatusChanged(false);
}

bool MultiStreamDecoder::initFFmpeg()
{
    // 打开输入流
    m_formatContext = avformat_alloc_context();
    if (avformat_open_input(&m_formatContext, m_url.toUtf8().data(), nullptr, nullptr) != 0) {
        qDebug() << "Cannot open input stream:" << m_url;
        return false;
    }

    // 查找流信息
    if (avformat_find_stream_info(m_formatContext, nullptr) < 0) {
        qDebug() << "Cannot find stream info:" << m_url;
        return false;
    }

    // 查找视频流
    m_videoStreamIndex = -1;
    for (unsigned int i = 0; i < m_formatContext->nb_streams; i++) {
        if (m_formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            m_videoStreamIndex = i;
            break;
        }
    }

    if (m_videoStreamIndex == -1) {
        qDebug() << "Cannot find video stream:" << m_url;
        return false;
    }

    // 获取解码器
    AVCodecParameters* codecpar = m_formatContext->streams[m_videoStreamIndex]->codecpar;
    const AVCodec* codec = avcodec_find_decoder(codecpar->codec_id);
    if (!codec) {
        qDebug() << "Cannot find codec:" << m_url;
        return false;
    }

    // 创建解码器上下文
    m_codecContext = avcodec_alloc_context3(codec);
    if (avcodec_parameters_to_context(m_codecContext, codecpar) < 0) {
        qDebug() << "Cannot copy codec parameters:" << m_url;
        return false;
    }

    // 打开解码器
    if (avcodec_open2(m_codecContext, codec, nullptr) < 0) {
        qDebug() << "Cannot open codec:" << m_url;
        return false;
    }

    return true;
}

void MultiStreamDecoder::cleanupFFmpeg()
{
    if (m_swsContext) {
        sws_freeContext(m_swsContext);
        m_swsContext = nullptr;
    }

    if (m_codecContext) {
        avcodec_free_context(&m_codecContext);
        m_codecContext = nullptr;
    }

    if (m_formatContext) {
        avformat_close_input(&m_formatContext);
        m_formatContext = nullptr;
    }
}

QImage MultiStreamDecoder::convertFrameToImage(AVFrame* frame)
{
    if (!frame || frame->width <= 0 || frame->height <= 0) {
        return QImage();
    }

    // 初始化转换上下文
    if (!m_swsContext) {
        m_swsContext = sws_getContext(
            frame->width, frame->height, static_cast<AVPixelFormat>(frame->format),
            frame->width, frame->height, AV_PIX_FMT_RGB24,
            SWS_BILINEAR, nullptr, nullptr, nullptr
        );
    }

    if (!m_swsContext) {
        return QImage();
    }

    // 分配RGB图像缓冲区
    QImage image(frame->width, frame->height, QImage::Format_RGB888);
    uint8_t* dest[4] = { image.bits(), nullptr, nullptr, nullptr };
    int destLinesize[4] = { 3 * frame->width, 0, 0, 0 };

    // 转换像素格式
    sws_scale(m_swsContext, 
              const_cast<const uint8_t**>(frame->data), frame->linesize,
              0, frame->height, dest, destLinesize);

    return image;
}