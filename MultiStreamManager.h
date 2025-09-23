#ifndef MULTISTREAMMANAGER_H
#define MULTISTREAMMANAGER_H

#include <QObject>
#include <QMutex>
#include <QVector>
#include <QString>
#include <QImage>
#include <QMap>

#include "MultiStreamDecoder.h"
#include "HandleManager.h"

/**
 * @brief 多路视频流管理器，负责管理多个RTSP视频流
 */
class MultiStreamManager : public QObject
{
    Q_OBJECT

public:
    explicit MultiStreamManager(QObject *parent = nullptr);
    ~MultiStreamManager();

    // 流管理接口
    int addStream(const QString& url);           // 添加视频流，返回句柄
    void removeStream(int handle);               // 移除视频流
    void removeAllStreams();                     // 移除所有视频流

    // 流控制接口
    void pauseStream(int handle);                // 暂停指定流
    void resumeStream(int handle);               // 恢复指定流
    void pauseAllStreams();                      // 暂停所有流
    void resumeAllStreams();                     // 恢复所有流

    // 获取流信息
    QImage getCurrentFrame(int handle);          // 获取当前帧
    QString getStreamUrl(int handle);            // 获取流URL
    bool isStreamConnected(int handle);          // 检查流连接状态
    QList<int> getAllStreamHandles();            // 获取所有流句柄
    int getStreamCount() const;                  // 获取流数量

signals:
    void frameReady(int handle, const QImage& frame);      // 新帧就绪
    void streamConnected(int handle, const QString& url);  // 流连接成功
    void streamDisconnected(int handle, const QString& url); // 流断开连接
    void streamError(int handle, const QString& error);    // 流错误

private slots:
    void onFrameReady(const QImage& frame);
    void onConnectionStatusChanged(bool connected);
    void onErrorOccurred(const QString& error);

private:
    HandleManager<MultiStreamDecoder> m_handleManager;
    QMap<MultiStreamDecoder*, int> m_decoderToHandle;  // 反向映射，用于信号处理
    mutable QMutex m_mutex;
};

#endif // MULTISTREAMMANAGER_H