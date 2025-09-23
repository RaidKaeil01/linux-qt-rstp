#ifndef MULTISTREAMVIEW_H
#define MULTISTREAMVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QListWidget>
#include <QSplitter>
#include <QGroupBox>
#include <QSpinBox>
#include <QTimer>
#include <QTextEdit>

#include "MultiStreamManager.h"
#include "MultiStreamController.h"
#include "VideoGridWidget.h"

/**
 * @brief 多路视频流视图，整合所有多路推流功能的用户界面
 */
class MultiStreamView : public QWidget
{
    Q_OBJECT

public:
    explicit MultiStreamView(QWidget *parent = nullptr);
    ~MultiStreamView();

    // 获取核心组件
    MultiStreamManager* getStreamManager() const { return m_streamManager; }
    MultiStreamController* getStreamController() const { return m_streamController; }
    VideoGridWidget* getVideoGrid() const { return m_videoGrid; }

signals:
    void backToSingleMode();                        // 返回单路模式信号

private slots:
    // 流管理操作
    void onAddStreamClicked();                      // 添加流
    void onRemoveStreamClicked();                   // 移除流
    void onRemoveAllStreamsClicked();               // 移除所有流
    void onPauseResumeClicked();                    // 暂停/恢复
    void onBackToSingleClicked();                   // 返回单路模式

    // 流状态处理
    void onStreamAdded(int handle, const QString& url);
    void onStreamRemoved(int handle, const QString& url);
    void onStreamConnected(int handle, const QString& url);
    void onStreamDisconnected(int handle, const QString& url);
    void onStreamError(int handle, const QString& error);
    void onVideoSelected(int globalIndex, int handle);

    // 流列表操作
    void onStreamListItemClicked();                 // 流列表项点击
    void onStreamListItemDoubleClicked();           // 流列表项双击

    // 定时更新
    void onUpdateTimer();                           // 定时更新状态

private:
    void setupUI();                                 // 设置用户界面
    void setupControlPanel();                       // 设置控制面板
    void setupStreamList();                         // 设置流列表
    void setupStatusPanel();                        // 设置状态面板
    void connectSignals();                          // 连接信号
    void updateStreamList();                        // 更新流列表
    void updateStatusPanel();                       // 更新状态面板
    void updateControlButtons();                    // 更新控制按钮状态
    QString formatStreamStatus(int handle);         // 格式化流状态

    // 核心组件
    MultiStreamManager* m_streamManager;
    MultiStreamController* m_streamController;
    VideoGridWidget* m_videoGrid;

    // 主要布局
    QSplitter* m_mainSplitter;
    QWidget* m_leftPanel;
    
    // 控制面板组件
    QGroupBox* m_controlGroup;
    QLineEdit* m_urlEdit;
    QPushButton* m_addStreamBtn;
    QPushButton* m_removeStreamBtn;
    QPushButton* m_removeAllBtn;
    QPushButton* m_pauseResumeBtn;
    QPushButton* m_backToSingleBtn;
    
    // 流列表组件
    QGroupBox* m_streamListGroup;
    QListWidget* m_streamList;
    
    // 状态面板组件
    QGroupBox* m_statusGroup;
    QTextEdit* m_statusText;
    QLabel* m_streamCountLabel;
    QLabel* m_selectedStreamLabel;
    QLabel* m_currentLayoutLabel;
    QLabel* m_currentPageLabel;
    
    // 定时器
    QTimer* m_updateTimer;
    
    // 状态变量
    bool m_allStreamsPaused;
    int m_selectedStreamHandle;
};

#endif // MULTISTREAMVIEW_H
