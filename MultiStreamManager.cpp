#include "MultiStreamManager.h"
#include <QDebug>
#include <QMutexLocker>

MultiStreamManager::MultiStreamManager(QObject *parent)
    : QObject(parent)
{
}

MultiStreamManager::~MultiStreamManager()
{
    removeAllStreams();
}

int MultiStreamManager::addStream(const QString& url)
{
    QMutexLocker locker(&m_mutex);
    
    // 创建解码器
    MultiStreamDecoder* decoder = new MultiStreamDecoder(url);
    
    // 创建句柄
    int handle = m_handleManager.createHandle(decoder);
    
    // 建立反向映射
    m_decoderToHandle[decoder] = handle;
    
    // 连接信号
    connect(decoder, &MultiStreamDecoder::frameReady,
            this, &MultiStreamManager::onFrameReady);
    connect(decoder, &MultiStreamDecoder::connectionStatusChanged,
            this, &MultiStreamManager::onConnectionStatusChanged);
    connect(decoder, &MultiStreamDecoder::errorOccurred,
            this, &MultiStreamManager::onErrorOccurred);
    
    // 启动解码器
    decoder->start();
    
    qDebug() << "Added stream:" << url << "handle:" << handle;
    return handle;
}

void MultiStreamManager::removeStream(int handle)
{
    QMutexLocker locker(&m_mutex);
    
    MultiStreamDecoder* decoder = m_handleManager.getResource(handle);
    if (!decoder) {
        qWarning() << "Invalid handle:" << handle;
        return;
    }
    
    QString url = decoder->getUrl();
    
    // 停止解码器
    decoder->stopDecoding();
    
    // 断开信号连接
    disconnect(decoder, nullptr, this, nullptr);
    
    // 移除反向映射
    m_decoderToHandle.remove(decoder);
    
    // 释放句柄
    m_handleManager.releaseHandle(handle);
    
    qDebug() << "Removed stream:" << url << "handle:" << handle;
}

void MultiStreamManager::removeAllStreams()
{
    QMutexLocker locker(&m_mutex);
    
    QList<int> handles = m_handleManager.getAllHandles();
    for (int handle : handles) {
        MultiStreamDecoder* decoder = m_handleManager.getResource(handle);
        if (decoder) {
            decoder->stopDecoding();
            disconnect(decoder, nullptr, this, nullptr);
        }
        m_handleManager.releaseHandle(handle);
    }
    
    m_decoderToHandle.clear();
    qDebug() << "Removed all streams";
}

void MultiStreamManager::pauseStream(int handle)
{
    MultiStreamDecoder* decoder = m_handleManager.getResource(handle);
    if (decoder) {
        decoder->pauseDecoding();
    }
}

void MultiStreamManager::resumeStream(int handle)
{
    MultiStreamDecoder* decoder = m_handleManager.getResource(handle);
    if (decoder) {
        decoder->resumeDecoding();
    }
}

void MultiStreamManager::pauseAllStreams()
{
    QMutexLocker locker(&m_mutex);
    
    QList<int> handles = m_handleManager.getAllHandles();
    for (int handle : handles) {
        MultiStreamDecoder* decoder = m_handleManager.getResource(handle);
        if (decoder) {
            decoder->pauseDecoding();
        }
    }
}

void MultiStreamManager::resumeAllStreams()
{
    QMutexLocker locker(&m_mutex);
    
    QList<int> handles = m_handleManager.getAllHandles();
    for (int handle : handles) {
        MultiStreamDecoder* decoder = m_handleManager.getResource(handle);
        if (decoder) {
            decoder->resumeDecoding();
        }
    }
}

QImage MultiStreamManager::getCurrentFrame(int handle)
{
    MultiStreamDecoder* decoder = m_handleManager.getResource(handle);
    if (decoder) {
        return decoder->getCurrentFrame();
    }
    return QImage();
}

QString MultiStreamManager::getStreamUrl(int handle)
{
    MultiStreamDecoder* decoder = m_handleManager.getResource(handle);
    if (decoder) {
        return decoder->getUrl();
    }
    return QString();
}

bool MultiStreamManager::isStreamConnected(int handle)
{
    MultiStreamDecoder* decoder = m_handleManager.getResource(handle);
    if (decoder) {
        return decoder->isConnected();
    }
    return false;
}

QList<int> MultiStreamManager::getAllStreamHandles()
{
    return m_handleManager.getAllHandles();
}

int MultiStreamManager::getStreamCount() const
{
    return m_handleManager.size();
}

void MultiStreamManager::onFrameReady(const QImage& frame)
{
    // 获取发送信号的解码器
    MultiStreamDecoder* decoder = qobject_cast<MultiStreamDecoder*>(sender());
    if (!decoder) {
        return;
    }
    
    // 查找对应的句柄
    QMutexLocker locker(&m_mutex);
    auto it = m_decoderToHandle.find(decoder);
    if (it != m_decoderToHandle.end()) {
        int handle = it.value();
        emit frameReady(handle, frame);
    }
}

void MultiStreamManager::onConnectionStatusChanged(bool connected)
{
    MultiStreamDecoder* decoder = qobject_cast<MultiStreamDecoder*>(sender());
    if (!decoder) {
        return;
    }
    
    QMutexLocker locker(&m_mutex);
    auto it = m_decoderToHandle.find(decoder);
    if (it != m_decoderToHandle.end()) {
        int handle = it.value();
        QString url = decoder->getUrl();
        
        if (connected) {
            emit streamConnected(handle, url);
        } else {
            emit streamDisconnected(handle, url);
        }
    }
}

void MultiStreamManager::onErrorOccurred(const QString& error)
{
    MultiStreamDecoder* decoder = qobject_cast<MultiStreamDecoder*>(sender());
    if (!decoder) {
        return;
    }
    
    QMutexLocker locker(&m_mutex);
    auto it = m_decoderToHandle.find(decoder);
    if (it != m_decoderToHandle.end()) {
        int handle = it.value();
        emit streamError(handle, error);
    }
}