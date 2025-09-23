#include "MultiStreamController.h"
#include <QDebug>
#include <QMutexLocker>

MultiStreamController::MultiStreamController(QObject *parent)
    : QObject(parent)
    , m_streamManager(nullptr)
    , m_videoGrid(nullptr)
{
}

MultiStreamController::~MultiStreamController()
{
}

void MultiStreamController::setStreamManager(MultiStreamManager* manager)
{
    if (m_streamManager) {
        disconnect(m_streamManager, nullptr, this, nullptr);
    }
    
    m_streamManager = manager;
    
    if (m_streamManager) {
        connect(m_streamManager, &MultiStreamManager::frameReady,
                this, &MultiStreamController::onFrameReady);
        connect(m_streamManager, &MultiStreamManager::streamConnected,
                this, &MultiStreamController::onStreamConnected);
        connect(m_streamManager, &MultiStreamManager::streamDisconnected,
                this, &MultiStreamController::onStreamDisconnected);
        connect(m_streamManager, &MultiStreamManager::streamError,
                this, &MultiStreamController::onStreamError);
    }
}

void MultiStreamController::setVideoGrid(VideoGridWidget* grid)
{
    if (m_videoGrid) {
        disconnect(m_videoGrid, nullptr, this, nullptr);
    }
    
    m_videoGrid = grid;
    
    if (m_videoGrid) {
        connect(m_videoGrid, &VideoGridWidget::videoClicked,
                this, &MultiStreamController::onVideoClicked);
        connect(m_videoGrid, &VideoGridWidget::layoutChanged,
                this, &MultiStreamController::onGridLayoutChanged);
        connect(m_videoGrid, &VideoGridWidget::pageChanged,
                this, &MultiStreamController::onGridPageChanged);
    }
}

int MultiStreamController::addStream(const QString& url)
{
    if (!m_streamManager) {
        qWarning() << "Stream manager not set";
        return -1;
    }
    
    QMutexLocker locker(&m_mutex);
    
    // 创建流
    int handle = m_streamManager->addStream(url);
    if (handle < 0) {
        qWarning() << "Failed to add stream:" << url;
        return -1;
    }
    
    // 获取显示索引
    int displayIndex = getNextDisplayIndex();
    
    // 建立映射
    m_handleToDisplayIndex[handle] = displayIndex;
    m_displayIndexToHandle[displayIndex] = handle;
    
    // 保存流信息
    StreamInfo info;
    info.handle = handle;
    info.url = url;
    info.connected = false;
    info.displayIndex = displayIndex;
    m_streamInfos[handle] = info;
    
    // 更新视频网格
    if (m_videoGrid) {
        m_videoGrid->setTotalStreamCount(m_streamInfos.size());
    }
    
    emit streamAdded(handle, url);
    qDebug() << "Added stream:" << url << "handle:" << handle << "displayIndex:" << displayIndex;
    
    return handle;
}

void MultiStreamController::removeStream(int handle)
{
    if (!m_streamManager) {
        return;
    }
    
    QMutexLocker locker(&m_mutex);
    
    auto it = m_streamInfos.find(handle);
    if (it == m_streamInfos.end()) {
        qWarning() << "Stream not found:" << handle;
        return;
    }
    
    StreamInfo info = it.value();
    QString url = info.url;
    int displayIndex = info.displayIndex;
    
    // 移除流
    m_streamManager->removeStream(handle);
    
    // 清除映射
    m_handleToDisplayIndex.remove(handle);
    m_displayIndexToHandle.remove(displayIndex);
    
    // 清除流信息
    m_streamInfos.remove(handle);
    
    // 清除视频网格中的帧
    if (m_videoGrid) {
        m_videoGrid->clearVideoFrame(displayIndex);
        m_videoGrid->setTotalStreamCount(m_streamInfos.size());
    }
    
    // 重新映射显示索引
    updateDisplayMapping();
    
    emit streamRemoved(handle, url);
    qDebug() << "Removed stream:" << url << "handle:" << handle;
}

void MultiStreamController::removeAllStreams()
{
    if (!m_streamManager) {
        return;
    }
    
    QMutexLocker locker(&m_mutex);
    
    // 获取所有句柄
    QList<int> handles = m_streamInfos.keys();
    
    // 移除所有流
    m_streamManager->removeAllStreams();
    
    // 清除所有映射和信息
    m_handleToDisplayIndex.clear();
    m_displayIndexToHandle.clear();
    m_streamInfos.clear();
    
    // 清除视频网格
    if (m_videoGrid) {
        m_videoGrid->clearAllFrames();
        m_videoGrid->setTotalStreamCount(0);
    }
    
    // 发送移除信号
    for (int handle : handles) {
        emit streamRemoved(handle, "");
    }
    
    qDebug() << "Removed all streams";
}

QList<int> MultiStreamController::getAllStreamHandles()
{
    QMutexLocker locker(&m_mutex);
    return m_streamInfos.keys();
}

void MultiStreamController::pauseStream(int handle)
{
    if (m_streamManager) {
        m_streamManager->pauseStream(handle);
    }
}

void MultiStreamController::resumeStream(int handle)
{
    if (m_streamManager) {
        m_streamManager->resumeStream(handle);
    }
}

void MultiStreamController::pauseAllStreams()
{
    if (m_streamManager) {
        m_streamManager->pauseAllStreams();
    }
}

void MultiStreamController::resumeAllStreams()
{
    if (m_streamManager) {
        m_streamManager->resumeAllStreams();
    }
}

void MultiStreamController::setGridLayout(GridLayout layout)
{
    if (m_videoGrid) {
        m_videoGrid->setGridLayout(layout);
    }
}

void MultiStreamController::setCurrentPage(int page)
{
    if (m_videoGrid) {
        m_videoGrid->setCurrentPage(page);
    }
}

void MultiStreamController::selectVideo(int globalIndex)
{
    if (m_videoGrid) {
        m_videoGrid->setSelectedIndex(globalIndex);
        
        // 查找对应的句柄
        QMutexLocker locker(&m_mutex);
        auto it = m_displayIndexToHandle.find(globalIndex);
        if (it != m_displayIndexToHandle.end()) {
            emit videoSelected(globalIndex, it.value());
        }
    }
}

int MultiStreamController::getStreamCount() const
{
    QMutexLocker locker(&m_mutex);
    return m_streamInfos.size();
}

GridLayout MultiStreamController::getCurrentLayout() const
{
    if (m_videoGrid) {
        return m_videoGrid->getCurrentLayout();
    }
    return GridLayout::Grid_2x2;
}

int MultiStreamController::getCurrentPage() const
{
    if (m_videoGrid) {
        return m_videoGrid->getCurrentPage();
    }
    return 0;
}

int MultiStreamController::getSelectedVideoIndex() const
{
    if (m_videoGrid) {
        return m_videoGrid->getSelectedIndex();
    }
    return -1;
}

QList<MultiStreamController::StreamInfo> MultiStreamController::getAllStreamInfo() const
{
    QMutexLocker locker(&m_mutex);
    return m_streamInfos.values();
}

MultiStreamController::StreamInfo MultiStreamController::getStreamInfo(int handle) const
{
    QMutexLocker locker(&m_mutex);
    return m_streamInfos.value(handle);
}

void MultiStreamController::onFrameReady(int handle, const QImage& frame)
{
    QMutexLocker locker(&m_mutex);
    
    // 查找显示索引
    auto it = m_handleToDisplayIndex.find(handle);
    if (it != m_handleToDisplayIndex.end()) {
        int displayIndex = it.value();
        if (m_videoGrid) {
            m_videoGrid->setVideoFrame(displayIndex, frame);
        }
    }
}

void MultiStreamController::onStreamConnected(int handle, const QString& url)
{
    QMutexLocker locker(&m_mutex);
    
    auto it = m_streamInfos.find(handle);
    if (it != m_streamInfos.end()) {
        it.value().connected = true;
        it.value().lastError.clear();
    }
    
    emit streamConnected(handle, url);
}

void MultiStreamController::onStreamDisconnected(int handle, const QString& url)
{
    QMutexLocker locker(&m_mutex);
    
    auto it = m_streamInfos.find(handle);
    if (it != m_streamInfos.end()) {
        it.value().connected = false;
    }
    
    emit streamDisconnected(handle, url);
}

void MultiStreamController::onStreamError(int handle, const QString& error)
{
    QMutexLocker locker(&m_mutex);
    
    auto it = m_streamInfos.find(handle);
    if (it != m_streamInfos.end()) {
        it.value().lastError = error;
        it.value().connected = false;
    }
    
    emit streamError(handle, error);
}

void MultiStreamController::onVideoClicked(int globalIndex)
{
    selectVideo(globalIndex);
}

void MultiStreamController::onGridLayoutChanged(GridLayout layout)
{
    emit layoutChanged(layout);
}

void MultiStreamController::onGridPageChanged(int page)
{
    emit pageChanged(page);
}

void MultiStreamController::updateDisplayMapping()
{
    // 重新排列显示索引，使其连续
    QMap<int, int> newHandleToDisplay;
    QMap<int, int> newDisplayToHandle;
    
    QList<int> handles = m_streamInfos.keys();
    std::sort(handles.begin(), handles.end());
    
    for (int i = 0; i < handles.size(); ++i) {
        int handle = handles[i];
        newHandleToDisplay[handle] = i;
        newDisplayToHandle[i] = handle;
        
        // 更新流信息中的显示索引
        m_streamInfos[handle].displayIndex = i;
    }
    
    m_handleToDisplayIndex = newHandleToDisplay;
    m_displayIndexToHandle = newDisplayToHandle;
    
    // 刷新视频网格
    refreshVideoGrid();
}

int MultiStreamController::getNextDisplayIndex()
{
    // 返回下一个可用的显示索引
    return m_streamInfos.size();
}

void MultiStreamController::refreshVideoGrid()
{
    if (!m_videoGrid || !m_streamManager) {
        return;
    }
    
    // 清除所有帧
    m_videoGrid->clearAllFrames();
    
    // 重新设置所有帧
    for (auto it = m_handleToDisplayIndex.begin(); it != m_handleToDisplayIndex.end(); ++it) {
        int handle = it.key();
        int displayIndex = it.value();
        
        QImage frame = m_streamManager->getCurrentFrame(handle);
        if (!frame.isNull()) {
            m_videoGrid->setVideoFrame(displayIndex, frame);
        }
    }
}
