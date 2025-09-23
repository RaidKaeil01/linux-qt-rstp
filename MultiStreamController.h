#ifndef MULTISTREAMCONTROLLER_H
#define MULTISTREAMCONTROLLER_H

#include <QObject>
#include <QMap>
#include <QTimer>
#include <QMutex>
#include <QImage>
#include <QString>
#include <QList>

#include "MultiStreamManager.h"
#include "VideoGridWidget.h"

/**
 * @brief 多路视频流控制器，协调流管理器和显示组件
 */
class MultiStreamController : public QObject
{
    Q_OBJECT

public:
    explicit MultiStreamController(QObject *parent = nullptr);
    ~MultiStreamController();

    // 组件设置
    void setStreamManager(MultiStreamManager* manager);
    void setVideoGrid(VideoGridWidget* grid);

    // 流管理接口
    int addStream(const QString& url);              // 添加视频流
    void removeStream(int handle);                  // 移除视频流  
    void removeAllStreams();                        // 移除所有流
    QList<int> getAllStreamHandles();               // 获取所有流句柄

    // 流控制接口
    void pauseStream(int handle);                   // 暂停流
    void resumeStream(int handle);                  // 恢复流
    void pauseAllStreams();                         // 暂停所有流
    void resumeAllStreams();                        // 恢复所有流

    // 显示控制接口
    void setGridLayout(GridLayout layout);          // 设置网格布局
    void setCurrentPage(int page);                  // 设置当前页
    void selectVideo(int globalIndex);              // 选择视频

    // 获取状态信息
    int getStreamCount() const;                     // 获取流数量
    GridLayout getCurrentLayout() const;            // 获取当前布局
    int getCurrentPage() const;                     // 获取当前页
    int getSelectedVideoIndex() const;              // 获取选中的视频索引

    // 流信息管理
    struct StreamInfo {
        int handle;
        QString url;
        bool connected;
        QString lastError;
        int displayIndex;  // 在显示中的索引位置
    };
    
    QList<StreamInfo> getAllStreamInfo() const;     // 获取所有流信息
    StreamInfo getStreamInfo(int handle) const;     // 获取指定流信息

signals:
    void streamAdded(int handle, const QString& url);
    void streamRemoved(int handle, const QString& url);
    void streamConnected(int handle, const QString& url);
    void streamDisconnected(int handle, const QString& url);
    void streamError(int handle, const QString& error);
    void videoSelected(int globalIndex, int handle);
    void layoutChanged(GridLayout layout);
    void pageChanged(int page);

private slots:
    // 流管理器信号处理
    void onFrameReady(int handle, const QImage& frame);
    void onStreamConnected(int handle, const QString& url);
    void onStreamDisconnected(int handle, const QString& url);
    void onStreamError(int handle, const QString& error);
    
    // 视频网格信号处理
    void onVideoClicked(int globalIndex);
    void onGridLayoutChanged(GridLayout layout);
    void onGridPageChanged(int page);

private:
    MultiStreamManager* m_streamManager;
    VideoGridWidget* m_videoGrid;
    
    // 流到显示索引的映射
    QMap<int, int> m_handleToDisplayIndex;  // 句柄 -> 显示索引
    QMap<int, int> m_displayIndexToHandle;  // 显示索引 -> 句柄
    
    // 流信息
    QMap<int, StreamInfo> m_streamInfos;
    
    mutable QMutex m_mutex;
    
    // 辅助方法
    void updateDisplayMapping();                    // 更新显示映射
    int getNextDisplayIndex();                      // 获取下一个可用的显示索引
    void refreshVideoGrid();                        // 刷新视频网格显示
};

#endif // MULTISTREAMCONTROLLER_H
