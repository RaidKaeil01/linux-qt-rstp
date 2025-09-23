#ifndef MULTISTREAMDECODER_H
#define MULTISTREAMDECODER_H

#include <QObject>
#include <QThread>
#include <QImage>
#include <QMutex>
#include <QTimer>
#include <QDebug>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
}

/**
 * @brief 多路视频流解码器，用于解码单路RTSP视频流
 */
class MultiStreamDecoder : public QThread
{
    Q_OBJECT

public:
    explicit MultiStreamDecoder(const QString& url, QObject *parent = nullptr);
    ~MultiStreamDecoder();

    // 获取当前帧
    QImage getCurrentFrame();
    
    // 获取流信息
    QString getUrl() const { return m_url; }
    bool isConnected() const { return m_connected; }
    
    // 控制解码
    void pauseDecoding();
    void resumeDecoding();
    void stopDecoding();

signals:
    void frameReady(const QImage& frame);
    void connectionStatusChanged(bool connected);
    void errorOccurred(const QString& error);

protected:
    void run() override;

private:
    QString m_url;
    bool m_connected;
    bool m_paused;
    bool m_stop;
    
    QImage m_currentFrame;
    QMutex m_frameMutex;
    
    // FFmpeg 相关
    AVFormatContext* m_formatContext;
    AVCodecContext* m_codecContext;
    SwsContext* m_swsContext;
    int m_videoStreamIndex;
    
    // 初始化FFmpeg
    bool initFFmpeg();
    void cleanupFFmpeg();
    
    // 解码帧
    bool decodeFrame();
    QImage convertFrameToImage(AVFrame* frame);
};

#endif // MULTISTREAMDECODER_H