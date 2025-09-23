#include "VideoGridWidget.h"
#include <QDebug>
#include <QMutexLocker>
#include <QApplication>

VideoGridWidget::VideoGridWidget(QWidget *parent)
    : QWidget(parent)
    , m_currentLayout(GridLayout::Grid_2x2)
    , m_currentPage(0)
    , m_totalStreamCount(0)
    , m_selectedIndex(-1)
{
    setupUI();
    setGridLayout(GridLayout::Grid_2x2);
}

VideoGridWidget::~VideoGridWidget()
{
}

void VideoGridWidget::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    
    // 控制面板
    m_controlLayout = new QHBoxLayout();
    
    // 布局选择
    m_layoutCombo = new QComboBox();
    m_layoutCombo->addItem("1x1 (1路)", static_cast<int>(GridLayout::Grid_1x1));
    m_layoutCombo->addItem("2x2 (4路)", static_cast<int>(GridLayout::Grid_2x2));
    m_layoutCombo->addItem("3x3 (9路)", static_cast<int>(GridLayout::Grid_3x3));
    m_layoutCombo->addItem("4x4 (16路)", static_cast<int>(GridLayout::Grid_4x4));
    m_layoutCombo->addItem("5x5 (25路)", static_cast<int>(GridLayout::Grid_5x5));
    m_layoutCombo->addItem("6x6 (36路)", static_cast<int>(GridLayout::Grid_6x6));
    m_layoutCombo->setCurrentIndex(1); // 默认2x2
    
    // 分页控制
    m_prevPageBtn = new QPushButton("上一页");
    m_nextPageBtn = new QPushButton("下一页");
    m_pageSpinBox = new QSpinBox();
    m_pageSpinBox->setMinimum(1);
    m_pageSpinBox->setValue(1);
    m_pageInfoLabel = new QLabel("页面: 1/1");
    
    m_controlLayout->addWidget(new QLabel("布局:"));
    m_controlLayout->addWidget(m_layoutCombo);
    m_controlLayout->addStretch();
    m_controlLayout->addWidget(m_prevPageBtn);
    m_controlLayout->addWidget(m_pageSpinBox);
    m_controlLayout->addWidget(m_nextPageBtn);
    m_controlLayout->addWidget(m_pageInfoLabel);
    
    // 网格区域
    m_gridWidget = new QWidget();
    m_gridLayout = new QGridLayout(m_gridWidget);
    m_gridLayout->setSpacing(2);
    
    m_scrollArea = new QScrollArea();
    m_scrollArea->setWidget(m_gridWidget);
    m_scrollArea->setWidgetResizable(true);
    
    m_mainLayout->addLayout(m_controlLayout);
    m_mainLayout->addWidget(m_scrollArea);
    
    // 连接信号
    connect(m_layoutCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &VideoGridWidget::onLayoutComboChanged);
    connect(m_pageSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &VideoGridWidget::onPageSpinChanged);
    connect(m_prevPageBtn, &QPushButton::clicked,
            this, &VideoGridWidget::onPrevPageClicked);
    connect(m_nextPageBtn, &QPushButton::clicked,
            this, &VideoGridWidget::onNextPageClicked);
}

void VideoGridWidget::setGridLayout(GridLayout layout)
{
    QMutexLocker locker(&m_mutex);
    
    m_currentLayout = layout;
    setupGrid();
    updatePageControls();
    updateVideoLabels();
    
    emit layoutChanged(layout);
}

void VideoGridWidget::setupGrid()
{
    // 清理现有的VideoLabel
    for (VideoLabel* label : m_videoLabels) {
        m_gridLayout->removeWidget(label);
        label->deleteLater();
    }
    m_videoLabels.clear();
    
    int gridSize = getGridSize(m_currentLayout);
    int maxDisplay = static_cast<int>(m_currentLayout);
    
    // 创建新的VideoLabel
    for (int i = 0; i < maxDisplay; ++i) {
        VideoLabel* videoLabel = new VideoLabel();
        videoLabel->setMinimumSize(160, 120);
        videoLabel->setScaledContents(true);
        videoLabel->setStyleSheet("border: 1px solid gray; background-color: black;");
        
        // 设置默认显示文本（从0开始）
        videoLabel->setText(QString("视频 %1").arg(i));
        videoLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        
        // 安装事件过滤器来处理点击事件
        videoLabel->installEventFilter(this);
        
        int row = i / gridSize;
        int col = i % gridSize;
        m_gridLayout->addWidget(videoLabel, row, col);
        
        m_videoLabels.append(videoLabel);
    }
}

GridLayout VideoGridWidget::getCurrentLayout() const
{
    return m_currentLayout;
}

int VideoGridWidget::getMaxDisplayCount() const
{
    return static_cast<int>(m_currentLayout);
}

void VideoGridWidget::setVideoFrame(int index, const QImage& frame)
{
    QMutexLocker locker(&m_mutex);
    
    // 缓存帧数据
    m_videoFrames[index] = frame;
    
    // 计算本地索引
    int localIndex = globalIndexToLocalIndex(index);
    if (localIndex >= 0 && localIndex < m_videoLabels.size()) {
        VideoLabel* label = m_videoLabels[localIndex];
        if (label && !frame.isNull()) {
            label->setPixmap(QPixmap::fromImage(frame.scaled(
                label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)));
        }
    }
}

void VideoGridWidget::clearVideoFrame(int index)
{
    QMutexLocker locker(&m_mutex);
    
    m_videoFrames.remove(index);
    
    int localIndex = globalIndexToLocalIndex(index);
    if (localIndex >= 0 && localIndex < m_videoLabels.size()) {
        VideoLabel* label = m_videoLabels[localIndex];
        if (label) {
            label->clear();
            label->setText(QString("视频 %1").arg(index));
            label->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        }
    }
}

void VideoGridWidget::clearAllFrames()
{
    QMutexLocker locker(&m_mutex);
    
    m_videoFrames.clear();
    
    for (int i = 0; i < m_videoLabels.size(); ++i) {
        VideoLabel* label = m_videoLabels[i];
        if (label) {
            label->clear();
            int globalIndex = localIndexToGlobalIndex(i);
            label->setText(QString("视频 %1").arg(globalIndex));
            label->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        }
    }
}

void VideoGridWidget::setCurrentPage(int page)
{
    // 确保页码不小于0
    page = qMax(0, page);
    
    if (page != m_currentPage) {
        m_currentPage = page;
        m_pageSpinBox->setValue(page + 1); // SpinBox从1开始
        updateVideoLabels();
        emit pageChanged(page);
    }
}

int VideoGridWidget::getCurrentPage() const
{
    return m_currentPage;
}

int VideoGridWidget::getTotalPages() const
{
    int maxDisplay = static_cast<int>(m_currentLayout);
    if (maxDisplay == 0) return 1;
    return (m_totalStreamCount + maxDisplay - 1) / maxDisplay;
}

void VideoGridWidget::setTotalStreamCount(int count)
{
    m_totalStreamCount = count;
    updatePageControls();
}

void VideoGridWidget::setSelectedIndex(int index)
{
    if (m_selectedIndex != index) {
        int oldSelectedIndex = m_selectedIndex;
        m_selectedIndex = index;
        
        // 更新所有可见的VideoLabel样式
        updateVideoLabels();
        
        qDebug() << "视频选择已更改：从" << oldSelectedIndex << "到" << index;
    }
}

int VideoGridWidget::getSelectedIndex() const
{
    return m_selectedIndex;
}

void VideoGridWidget::clearSelection()
{
    setSelectedIndex(-1);
}

QString VideoGridWidget::getSelectedVideoInfo() const
{
    if (m_selectedIndex >= 0 && m_selectedIndex < m_totalStreamCount) {
        int currentPage = m_selectedIndex / static_cast<int>(m_currentLayout);
        int positionInPage = m_selectedIndex % static_cast<int>(m_currentLayout);
        return QString("视频 %1 (页面 %2, 位置 %3)").arg(m_selectedIndex).arg(currentPage + 1).arg(positionInPage);
    }
    return "未选择视频";
}

VideoLabel* VideoGridWidget::getVideoLabel(int index)
{
    int localIndex = globalIndexToLocalIndex(index);
    if (localIndex >= 0 && localIndex < m_videoLabels.size()) {
        return m_videoLabels[localIndex];
    }
    return nullptr;
}



void VideoGridWidget::onLayoutComboChanged()
{
    int currentData = m_layoutCombo->currentData().toInt();
    GridLayout newLayout = static_cast<GridLayout>(currentData);
    if (newLayout != m_currentLayout) {
        setGridLayout(newLayout);
    }
}

void VideoGridWidget::onPageSpinChanged()
{
    int page = m_pageSpinBox->value() - 1; // SpinBox从1开始，内部从0开始
    setCurrentPage(page);
}

void VideoGridWidget::onPrevPageClicked()
{
    if (m_currentPage > 0) {
        setCurrentPage(m_currentPage - 1);
    }
}

void VideoGridWidget::onNextPageClicked()
{
    int totalPages = getTotalPages();
    if (m_currentPage < totalPages - 1) {
        setCurrentPage(m_currentPage + 1);
    }
}

void VideoGridWidget::updatePageControls()
{
    int totalPages = getTotalPages();
    
    m_pageSpinBox->setMaximum(totalPages);
    m_pageSpinBox->setValue(m_currentPage + 1);
    
    m_prevPageBtn->setEnabled(m_currentPage > 0);
    m_nextPageBtn->setEnabled(m_currentPage < totalPages - 1);
    
    m_pageInfoLabel->setText(QString("页面: %1/%2").arg(m_currentPage + 1).arg(totalPages));
}

void VideoGridWidget::updateVideoLabels()
{
    for (int i = 0; i < m_videoLabels.size(); ++i) {
        int globalIndex = localIndexToGlobalIndex(i);
        VideoLabel* label = m_videoLabels[i];
        
        // 总是显示标签，即使没有视频流
        label->show();
        
        // 检查是否有对应的视频帧
        auto it = m_videoFrames.find(globalIndex);
        if (it != m_videoFrames.end() && !it.value().isNull()) {
            // 有视频帧，显示图像
            label->setPixmap(QPixmap::fromImage(it.value().scaled(
                label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)));
        } else {
            // 没有视频帧，显示默认文本（确保globalIndex从0开始）
            label->clear();
            label->setText(QString("视频 %1").arg(globalIndex));
            label->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        }
        
        // 设置视频标签样式
        updateVideoLabelStyle(label, globalIndex);
    }
}

void VideoGridWidget::updateVideoLabelStyle(VideoLabel* label, int globalIndex)
{
    if (!label) return;
    
    if (globalIndex == m_selectedIndex) {
        // 选中状态：明显的红色边框，突出显示
        label->setStyleSheet(
            "VideoLabel {"
            "   border: 5px solid #FF0000; "           // 5像素宽的纯红色边框
            "   background-color: #1a1a2e; "           // 深蓝色背景
            "   border-radius: 3px; "                   // 圆角
            "   font-weight: bold; "                    // 粗体字
            "   color: #FFD700; "                       // 金色文字
            "   font-size: 14px; "                      // 稍大的字体
            "   padding: 5px; "                         // 内边距，让文字不贴边
            "}"
        );
        qDebug() << "设置视频" << globalIndex << "为选中状态（红色边框）";
    } else {
        // 未选中状态：细灰边框，正常显示
        label->setStyleSheet(
            "VideoLabel {"
            "   border: 1px solid #666666; "           // 1像素灰色边框
            "   background-color: black; "              // 黑色背景
            "   border-radius: 2px; "                   // 小圆角
            "   color: white; "                         // 白色文字
            "   font-size: 12px; "                      // 正常字体
            "   padding: 3px; "                         // 内边距，让文字不贴边
            "}"
        );
    }
}

int VideoGridWidget::getGridSize(GridLayout layout) const
{
    switch (layout) {
        case GridLayout::Grid_1x1: return 1;
        case GridLayout::Grid_2x2: return 2;
        case GridLayout::Grid_3x3: return 3;
        case GridLayout::Grid_4x4: return 4;
        case GridLayout::Grid_5x5: return 5;
        case GridLayout::Grid_6x6: return 6;
    }
    return 2;
}

int VideoGridWidget::globalIndexToLocalIndex(int globalIndex) const
{
    int maxDisplay = static_cast<int>(m_currentLayout);
    int pageStartIndex = m_currentPage * maxDisplay;
    
    if (globalIndex >= pageStartIndex && globalIndex < pageStartIndex + maxDisplay) {
        return globalIndex - pageStartIndex;
    }
    return -1; // 不在当前页
}

int VideoGridWidget::localIndexToGlobalIndex(int localIndex) const
{
    int maxDisplay = static_cast<int>(m_currentLayout);
    return m_currentPage * maxDisplay + localIndex;
}

bool VideoGridWidget::eventFilter(QObject* watched, QEvent* event)
{
    VideoLabel* label = qobject_cast<VideoLabel*>(watched);
    if (!label) {
        return QWidget::eventFilter(watched, event);
    }
    
    int localIndex = m_videoLabels.indexOf(label);
    if (localIndex < 0) {
        return QWidget::eventFilter(watched, event);
    }
    
    int globalIndex = localIndexToGlobalIndex(localIndex);
    
    if (event->type() == QEvent::MouseButtonPress) {
        // 处理鼠标点击事件
        setSelectedIndex(globalIndex);
        emit videoClicked(globalIndex);
        return true; // 已处理事件
    }
    else if (event->type() == QEvent::Enter) {
        // 鼠标进入事件 - 添加悬停效果
        if (globalIndex != m_selectedIndex && globalIndex < m_totalStreamCount) {
            label->setStyleSheet(
                "border: 2px solid #888888; "
                "background-color: #2a2a2a; "
                "border-radius: 2px; "
                "color: #CCCCCC;"
            );
        }
    }
    else if (event->type() == QEvent::Leave) {
        // 鼠标离开事件 - 恢复原始样式
        if (globalIndex != m_selectedIndex && globalIndex < m_totalStreamCount) {
            label->setStyleSheet(
                "border: 1px solid #666666; "
                "background-color: black; "
                "border-radius: 2px; "
                "color: white;"
            );
        }
    }
    
    return QWidget::eventFilter(watched, event);
}