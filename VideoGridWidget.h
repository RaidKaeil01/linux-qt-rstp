#ifndef VIDEOGRIDWIDGET_H
#define VIDEOGRIDWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QVector>
#include <QMap>
#include <QMutex>
#include <QScrollArea>
#include <QSplitter>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QEvent>

#include "VideoLabel.h"

/**
 * @brief 网格布局模式
 */
enum class GridLayout {
    Grid_1x1 = 1,   // 1路显示
    Grid_2x2 = 4,   // 4路显示
    Grid_3x3 = 9,   // 9路显示
    Grid_4x4 = 16,  // 16路显示
    Grid_5x5 = 25,  // 25路显示
    Grid_6x6 = 36   // 36路显示
};

/**
 * @brief 视频网格组件，支持多种网格布局显示
 */
class VideoGridWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VideoGridWidget(QWidget *parent = nullptr);
    ~VideoGridWidget();

    // 网格布局管理
    void setGridLayout(GridLayout layout);           // 设置网格布局
    GridLayout getCurrentLayout() const;             // 获取当前布局
    int getMaxDisplayCount() const;                  // 获取最大显示数量

    // 视频显示管理
    void setVideoFrame(int index, const QImage& frame);  // 设置指定位置的视频帧
    void clearVideoFrame(int index);                     // 清除指定位置的视频帧
    void clearAllFrames();                               // 清除所有视频帧

    // 分页管理
    void setCurrentPage(int page);                       // 设置当前页
    int getCurrentPage() const;                          // 获取当前页
    int getTotalPages() const;                           // 获取总页数
    void setTotalStreamCount(int count);                 // 设置总流数量

    // 选中管理
    void setSelectedIndex(int index);                    // 设置选中的视频索引
    int getSelectedIndex() const;                        // 获取选中的视频索引
    void clearSelection();                               // 清除选择

    // 获取VideoLabel
    VideoLabel* getVideoLabel(int index);               // 获取指定索引的VideoLabel

signals:
    void videoClicked(int globalIndex);                 // 视频被点击，传递全局索引
    void layoutChanged(GridLayout layout);              // 布局改变
    void pageChanged(int page);                         // 页面改变
    
protected:
    bool eventFilter(QObject* watched, QEvent* event) override;  // 事件过滤器

private slots:
    void onLayoutComboChanged();
    void onPageSpinChanged();
    void onPrevPageClicked();
    void onNextPageClicked();

private:
    void setupUI();                                     // 设置UI
    void setupGrid();                                   // 设置网格
    void updatePageControls();                          // 更新分页控件
    void updateVideoLabels();                           // 更新视频标签显示
    int getGridSize(GridLayout layout) const;           // 获取网格大小
    int globalIndexToLocalIndex(int globalIndex) const; // 全局索引转本地索引
    int localIndexToGlobalIndex(int localIndex) const;  // 本地索引转全局索引

    // UI组件
    QVBoxLayout* m_mainLayout;
    QHBoxLayout* m_controlLayout;
    QGridLayout* m_gridLayout;
    QWidget* m_gridWidget;
    QScrollArea* m_scrollArea;
    
    // 控制组件
    QComboBox* m_layoutCombo;
    QSpinBox* m_pageSpinBox;
    QPushButton* m_prevPageBtn;
    QPushButton* m_nextPageBtn;
    QLabel* m_pageInfoLabel;
    
    // 数据成员
    GridLayout m_currentLayout;
    int m_currentPage;
    int m_totalStreamCount;
    int m_selectedIndex;
    
    QVector<VideoLabel*> m_videoLabels;        // 当前显示的VideoLabel
    QMap<int, QImage> m_videoFrames;           // 缓存的视频帧
    
    mutable QMutex m_mutex;
};

#endif // VIDEOGRIDWIDGET_H