#include "MultiStreamView.h"
#include <QDebug>
#include <QMessageBox>
#include <QInputDialog>
#include <QDateTime>

MultiStreamView::MultiStreamView(QWidget *parent)
    : QWidget(parent)
    , m_streamManager(nullptr)
    , m_streamController(nullptr)
    , m_videoGrid(nullptr)
    , m_allStreamsPaused(false)
    , m_selectedStreamHandle(-1)
{
    // 创建核心组件
    m_streamManager = new MultiStreamManager(this);
    m_videoGrid = new VideoGridWidget(this);
    m_streamController = new MultiStreamController(this);
    
    // 设置组件关联
    m_streamController->setStreamManager(m_streamManager);
    m_streamController->setVideoGrid(m_videoGrid);
    
    setupUI();
    connectSignals();
    
    // 设置定时器更新状态
    m_updateTimer = new QTimer(this);
    connect(m_updateTimer, &QTimer::timeout, this, &MultiStreamView::onUpdateTimer);
    m_updateTimer->start(5000); // 每5秒更新一次状态
    
    // 初始状态更新
    updateControlButtons();
    updateStatusPanel();
}

MultiStreamView::~MultiStreamView()
{
    if (m_streamController) {
        m_streamController->removeAllStreams();
    }
}

void MultiStreamView::setupUI()
{
    // 主分割器
    m_mainSplitter = new QSplitter(Qt::Horizontal, this);
    
    // 左侧控制面板
    m_leftPanel = new QWidget();
    m_leftPanel->setMaximumWidth(300);
    m_leftPanel->setMinimumWidth(250);
    
    QVBoxLayout* leftLayout = new QVBoxLayout(m_leftPanel);
    
    setupControlPanel();
    setupStreamList();
    setupStatusPanel();
    
    leftLayout->addWidget(m_controlGroup);
    leftLayout->addWidget(m_streamListGroup);
    leftLayout->addWidget(m_statusGroup);
    leftLayout->addStretch();
    
    // 添加到分割器
    m_mainSplitter->addWidget(m_leftPanel);
    m_mainSplitter->addWidget(m_videoGrid);
    m_mainSplitter->setStretchFactor(0, 0);
    m_mainSplitter->setStretchFactor(1, 1);
    
    // 主布局
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(m_mainSplitter);
    mainLayout->setContentsMargins(5, 5, 5, 5);
}

void MultiStreamView::setupControlPanel()
{
    m_controlGroup = new QGroupBox("流控制");
    QVBoxLayout* controlLayout = new QVBoxLayout(m_controlGroup);
    
    // URL输入
    QHBoxLayout* urlLayout = new QHBoxLayout();
    urlLayout->addWidget(new QLabel("RTSP URL:"));
    m_urlEdit = new QLineEdit();
    m_urlEdit->setPlaceholderText("rtsp://192.168.1.100:554/stream");
    urlLayout->addWidget(m_urlEdit);
    
    // 按钮布局
    QGridLayout* btnLayout = new QGridLayout();
    
    m_addStreamBtn = new QPushButton("添加流");
    m_removeStreamBtn = new QPushButton("移除流");
    m_removeAllBtn = new QPushButton("移除所有");
    m_pauseResumeBtn = new QPushButton("暂停所有");
    m_backToSingleBtn = new QPushButton("返回单路");
    
    btnLayout->addWidget(m_addStreamBtn, 0, 0);
    btnLayout->addWidget(m_removeStreamBtn, 0, 1);
    btnLayout->addWidget(m_removeAllBtn, 1, 0);
    btnLayout->addWidget(m_pauseResumeBtn, 1, 1);
    btnLayout->addWidget(m_backToSingleBtn, 2, 0, 1, 2);
    
    controlLayout->addLayout(urlLayout);
    controlLayout->addLayout(btnLayout);
}

void MultiStreamView::setupStreamList()
{
    m_streamListGroup = new QGroupBox("视频流列表");
    QVBoxLayout* listLayout = new QVBoxLayout(m_streamListGroup);
    
    m_streamList = new QListWidget();
    m_streamList->setMaximumHeight(200);
    listLayout->addWidget(m_streamList);
}

void MultiStreamView::setupStatusPanel()
{
    m_statusGroup = new QGroupBox("状态信息");
    QVBoxLayout* statusLayout = new QVBoxLayout(m_statusGroup);
    
    // 状态标签
    m_streamCountLabel = new QLabel("流数量: 0");
    m_selectedStreamLabel = new QLabel("选中流: 无");
    m_currentLayoutLabel = new QLabel("布局: 2x2");
    m_currentPageLabel = new QLabel("页面: 1/1");
    
    statusLayout->addWidget(m_streamCountLabel);
    statusLayout->addWidget(m_selectedStreamLabel);
    statusLayout->addWidget(m_currentLayoutLabel);
    statusLayout->addWidget(m_currentPageLabel);
    
    // 状态日志
    m_statusText = new QTextEdit();
    m_statusText->setMaximumHeight(150);
    m_statusText->setReadOnly(true);
    statusLayout->addWidget(new QLabel("日志:"));
    statusLayout->addWidget(m_statusText);
}

void MultiStreamView::connectSignals()
{
    // 控制按钮信号
    connect(m_addStreamBtn, &QPushButton::clicked,
            this, &MultiStreamView::onAddStreamClicked);
    connect(m_removeStreamBtn, &QPushButton::clicked,
            this, &MultiStreamView::onRemoveStreamClicked);
    connect(m_removeAllBtn, &QPushButton::clicked,
            this, &MultiStreamView::onRemoveAllStreamsClicked);
    connect(m_pauseResumeBtn, &QPushButton::clicked,
            this, &MultiStreamView::onPauseResumeClicked);
    connect(m_backToSingleBtn, &QPushButton::clicked,
            this, &MultiStreamView::onBackToSingleClicked);
    
    // 流列表信号
    connect(m_streamList, &QListWidget::itemClicked,
            this, &MultiStreamView::onStreamListItemClicked);
    connect(m_streamList, &QListWidget::itemDoubleClicked,
            this, &MultiStreamView::onStreamListItemDoubleClicked);
    
    // 流控制器信号
    if (m_streamController) {
        connect(m_streamController, &MultiStreamController::streamAdded,
                this, &MultiStreamView::onStreamAdded);
        connect(m_streamController, &MultiStreamController::streamRemoved,
                this, &MultiStreamView::onStreamRemoved);
        connect(m_streamController, &MultiStreamController::streamConnected,
                this, &MultiStreamView::onStreamConnected);
        connect(m_streamController, &MultiStreamController::streamDisconnected,
                this, &MultiStreamView::onStreamDisconnected);
        connect(m_streamController, &MultiStreamController::streamError,
                this, &MultiStreamView::onStreamError);
        connect(m_streamController, &MultiStreamController::videoSelected,
                this, &MultiStreamView::onVideoSelected);
    }
}

void MultiStreamView::onAddStreamClicked()
{
    QString url = m_urlEdit->text().trimmed();
    if (url.isEmpty()) {
        QMessageBox::warning(this, "警告", "请输入RTSP URL");
        return;
    }
    
    if (m_streamController) {
        int handle = m_streamController->addStream(url);
        if (handle >= 0) {
            m_urlEdit->clear();
            m_statusText->append(QString("[%1] 正在添加流: %2")
                .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                .arg(url));
        } else {
            QMessageBox::critical(this, "错误", "添加流失败");
        }
    }
}

void MultiStreamView::onRemoveStreamClicked()
{
    if (m_selectedStreamHandle < 0) {
        QMessageBox::information(this, "提示", "请先选择要移除的流");
        return;
    }
    
    if (m_streamController) {
        m_streamController->removeStream(m_selectedStreamHandle);
        m_selectedStreamHandle = -1;
    }
}

void MultiStreamView::onRemoveAllStreamsClicked()
{
    if (m_streamController && m_streamController->getStreamCount() > 0) {
        int ret = QMessageBox::question(this, "确认", "确定要移除所有视频流吗？",
                                      QMessageBox::Yes | QMessageBox::No);
        if (ret == QMessageBox::Yes) {
            m_streamController->removeAllStreams();
            m_selectedStreamHandle = -1;
        }
    }
}

void MultiStreamView::onPauseResumeClicked()
{
    if (!m_streamController) return;
    
    if (m_allStreamsPaused) {
        m_streamController->resumeAllStreams();
        m_allStreamsPaused = false;
        m_pauseResumeBtn->setText("暂停所有");
        m_statusText->append(QString("[%1] 恢复所有流")
            .arg(QDateTime::currentDateTime().toString("hh:mm:ss")));
    } else {
        m_streamController->pauseAllStreams();
        m_allStreamsPaused = true;
        m_pauseResumeBtn->setText("恢复所有");
        m_statusText->append(QString("[%1] 暂停所有流")
            .arg(QDateTime::currentDateTime().toString("hh:mm:ss")));
    }
}

void MultiStreamView::onBackToSingleClicked()
{
    if (m_streamController && m_streamController->getStreamCount() > 0) {
        int ret = QMessageBox::question(this, "确认", 
            "返回单路模式将停止所有多路流，确定继续吗？",
            QMessageBox::Yes | QMessageBox::No);
        if (ret == QMessageBox::Yes) {
            m_streamController->removeAllStreams();
            emit backToSingleMode();
        }
    } else {
        emit backToSingleMode();
    }
}

void MultiStreamView::onStreamAdded(int handle, const QString& url)
{
    updateStreamList();
    updateStatusPanel();
    updateControlButtons();
    
    m_statusText->append(QString("[%1] 流已添加: %2 (句柄: %3)")
        .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
        .arg(url).arg(handle));
}

void MultiStreamView::onStreamRemoved(int handle, const QString& url)
{
    updateStreamList();
    updateStatusPanel();
    updateControlButtons();
    
    m_statusText->append(QString("[%1] 流已移除: %2 (句柄: %3)")
        .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
        .arg(url).arg(handle));
}

void MultiStreamView::onStreamConnected(int handle, const QString& url)
{
    updateStreamList();
    m_statusText->append(QString("[%1] 流已连接: %2")
        .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
        .arg(url));
}

void MultiStreamView::onStreamDisconnected(int handle, const QString& url)
{
    updateStreamList();
    m_statusText->append(QString("[%1] 流已断开: %2")
        .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
        .arg(url));
}

void MultiStreamView::onStreamError(int handle, const QString& error)
{
    updateStreamList();
    m_statusText->append(QString("[%1] 流错误 (句柄: %2): %3")
        .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
        .arg(handle).arg(error));
}

void MultiStreamView::onVideoSelected(int globalIndex, int handle)
{
    m_selectedStreamHandle = handle;
    updateStatusPanel();
    
    // 更新流列表选择
    for (int i = 0; i < m_streamList->count(); ++i) {
        QListWidgetItem* item = m_streamList->item(i);
        if (item && item->data(Qt::UserRole).toInt() == handle) {
            m_streamList->setCurrentItem(item);
            break;
        }
    }
}

void MultiStreamView::onStreamListItemClicked()
{
    QListWidgetItem* item = m_streamList->currentItem();
    if (item) {
        int handle = item->data(Qt::UserRole).toInt();
        m_selectedStreamHandle = handle;
        updateStatusPanel();
    }
}

void MultiStreamView::onStreamListItemDoubleClicked()
{
    // 双击切换到该流对应的视频网格位置
    QListWidgetItem* item = m_streamList->currentItem();
    if (item && m_streamController) {
        int handle = item->data(Qt::UserRole).toInt();
        auto streamInfo = m_streamController->getStreamInfo(handle);
        if (streamInfo.handle == handle) {
            m_streamController->selectVideo(streamInfo.displayIndex);
        }
    }
}

void MultiStreamView::onUpdateTimer()
{
    updateStatusPanel();
}

void MultiStreamView::updateStreamList()
{
    m_streamList->clear();
    
    if (!m_streamController) return;
    
    QList<MultiStreamController::StreamInfo> streams = m_streamController->getAllStreamInfo();
    for (const auto& info : streams) {
        QString text = QString("[%1] %2 %3")
            .arg(info.displayIndex + 1)
            .arg(info.url)
            .arg(formatStreamStatus(info.handle));
        
        QListWidgetItem* item = new QListWidgetItem(text);
        item->setData(Qt::UserRole, info.handle);
        
        // 根据连接状态设置颜色
        if (info.connected) {
            item->setBackground(QColor(200, 255, 200)); // 浅绿色
        } else {
            item->setBackground(QColor(255, 200, 200)); // 浅红色
        }
        
        m_streamList->addItem(item);
    }
}

void MultiStreamView::updateStatusPanel()
{
    if (!m_streamController) return;
    
    // 更新基本信息
    int streamCount = m_streamController->getStreamCount();
    m_streamCountLabel->setText(QString("流数量: %1").arg(streamCount));
    
    // 更新选中流信息
    if (m_selectedStreamHandle >= 0) {
        auto info = m_streamController->getStreamInfo(m_selectedStreamHandle);
        if (info.handle == m_selectedStreamHandle) {
            m_selectedStreamLabel->setText(QString("选中流: %1 (%2)")
                .arg(info.displayIndex + 1).arg(info.url));
        }
    } else {
        m_selectedStreamLabel->setText("选中流: 无");
    }
    
    // 更新布局信息
    GridLayout layout = m_streamController->getCurrentLayout();
    QString layoutText;
    switch (layout) {
        case GridLayout::Grid_1x1: layoutText = "1x1"; break;
        case GridLayout::Grid_2x2: layoutText = "2x2"; break;
        case GridLayout::Grid_3x3: layoutText = "3x3"; break;
        case GridLayout::Grid_4x4: layoutText = "4x4"; break;
        case GridLayout::Grid_5x5: layoutText = "5x5"; break;
        case GridLayout::Grid_6x6: layoutText = "6x6"; break;
    }
    m_currentLayoutLabel->setText(QString("布局: %1").arg(layoutText));
    
    // 更新页面信息
    int currentPage = m_streamController->getCurrentPage() + 1;
    int maxDisplay = static_cast<int>(layout);
    int totalPages = maxDisplay > 0 ? (streamCount + maxDisplay - 1) / maxDisplay : 1;
    m_currentPageLabel->setText(QString("页面: %1/%2").arg(currentPage).arg(totalPages));
}

void MultiStreamView::updateControlButtons()
{
    if (!m_streamController) return;
    
    int streamCount = m_streamController->getStreamCount();
    
    m_removeStreamBtn->setEnabled(m_selectedStreamHandle >= 0);
    m_removeAllBtn->setEnabled(streamCount > 0);
    m_pauseResumeBtn->setEnabled(streamCount > 0);
}

QString MultiStreamView::formatStreamStatus(int handle)
{
    if (!m_streamController) return "未知";
    
    auto info = m_streamController->getStreamInfo(handle);
    if (info.handle != handle) return "未知";
    
    if (info.connected) {
        return "[已连接]";
    } else if (!info.lastError.isEmpty()) {
        return QString("[错误: %1]").arg(info.lastError);
    } else {
        return "[连接中...]";
    }
}