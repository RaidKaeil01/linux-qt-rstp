#pragma once
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QList>
#include <QSlider>
#include <QComboBox>
#include <QPainter>
#include <QMouseEvent>
#include <QRect>
#include <QTextBrowser>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QRadioButton>
#include <QSpinBox>
#include <QStackedWidget>
#include <QInputDialog>
#include "VideoLabel.h"
#include "VideoGridWidget.h"
#include "MultiStreamManager.h"
#include "MultiStreamController.h"
#include "common.h"

class View : public QWidget {
    Q_OBJECT

public:
    explicit View(QWidget* parent = nullptr);
    ~View();
    QLabel* getVideoLabel() const;               // 获取图像面板
    QList<QPushButton*> getTabButtons() const;   // 获取标签按钮
    QList<QPushButton*> getServoButtons() const; // 获取云台按钮
    QList<QPushButton*> getFunButtons() const;   // 获取功能按钮
    int getStepValue() const;                    // 获取步进值
    
    // 多路模式接口
    VideoGridWidget* getVideoGrid() const;       // 获取视频网格组件
    MultiStreamManager* getStreamManager() const; // 获取流管理器
    MultiStreamController* getStreamController() const; // 获取流控制器
    bool isMultiStreamMode() const;              // 是否为多路模式
    void setVideoDisplayMode(bool multiMode);    // 设置视频显示模式
    
    void drawRectangle(const RectangleBox& rect); // 绘制矩形框
    void clearRectangle();                        // 清除矩形框
    RectangleBox getCurrentRectangle() const;     // 获取当前矩形框
    
    // 启用/禁用绘制功能
    void enableDrawing(bool enabled);
    bool isDrawingEnabled() const;
    
    // 事件消息相关方法
    void addEventMessage(const QString& type, const QString& message);

signals:
    void rectangleConfirmed(const RectangleBox& rect); // 矩形框确认信号
    void normalizedRectangleConfirmed(const NormalizedRectangleBox& rect, const RectangleBox& absRect); // 归一化矩形框信号
    
    // 多路模式信号
    void gridLayoutChanged(int gridNum);         // 网格布局改变
    void streamAdded(const QString& url);        // 添加视频流
    void streamRemoved(int handle);              // 移除视频流
    void videoDisplayModeChanged(bool multiMode); // 视频显示模式改变

private slots:
    void onRectangleDrawn(const RectangleBox& rect); // 处理矩形框绘制完成
    void onRectangleConfirmed(const RectangleBox& rect); // 处理矩形框确认
    void onRectangleCancelled(); // 处理矩形框取消
    
    // 多路模式槽函数
    void onGridModeChanged();                    // 网格模式改变
    void onAddMultiStreamClicked();              // 添加多路流
    void onRemoveMultiStreamClicked();           // 移除多路流
    void onPrevPageClicked();                    // 上一页
    void onNextPageClicked();                    // 下一页
    void onPageJumpClicked();                    // 页面跳转

private:
    void initleft();       // 初始化左边面板
    void initmiddle();     // 初始化中间面板
    void initright();      // 初始化右边面板
    void initButtons();    // 初始化按键列表
    void initservo();      // 初始化云台按键列表 
    void initstep();       // 初始化步进布局
    void initFunButtons(); // 初始化功能按钮
    void initVideoLabel(); // 初始化视频标签
    void initVideoGrid();  // 初始化视频网格
    void initGridControls(); // 初始化网格控制组件
    void initMultiStreamComponents(); // 初始化多路流组件
    void updateGridControlsVisibility(); // 更新网格控件可见性

    QList<QPushButton*> tabButtons;  // 存储所有标签按钮的列表
    QList<QPushButton*> ServoButtons;// 存储舵机所有按钮的列表
    QList<QPushButton*> funButtons;  // 存储摄像头功能按钮的列表

    VideoLabel* videoLabel;    //图像面板（使用自定义VideoLabel）
    QLabel* stepLabel;         //步进标签
    QSlider* stepSlider;       //步进滑块
    QComboBox* stepCombox;     //步进下拉框
    QLabel* eventLabel;        //事件消息框标签
    QTextBrowser* eventBrowser; //事件消息显示框

    QWidget* leftPanel;    //左边整体面板
    QWidget* funPanel;     //中上方功能面板
    QWidget* middlePanel;  //中间整体面板
    QWidget* rightPanel;   //右边整体面板
    QWidget* buttonPanel;  //按键整体面板
    QWidget* servoPanel;   //云台整体面板
    QWidget* stepPanel;    //步进整体面板

    // 绘框相关成员变量
    RectangleBox m_rectangle;      // 当前绘制的矩形框
    bool m_hasRectangle;           // 是否有矩形框
    
    // 视频显示组件
    QStackedWidget* m_videoStackedWidget; // 堆叠窗口：单路/多路切换
    VideoGridWidget* m_videoGrid;         // 多路视频网格
    bool m_isMultiStreamMode;             // 是否为多路模式
    
    // 多路流管理组件
    MultiStreamManager* m_streamManager;     // 流管理器
    MultiStreamController* m_streamController; // 流控制器
    
    // 网格控制组件
    QWidget* m_gridControlPanel;          // 网格控制面板
    QLabel* m_gridLabel;                  // 网格标签
    QRadioButton* m_gridRadio1;           // 1x1网格
    QRadioButton* m_gridRadio4;           // 2x2网格  
    QRadioButton* m_gridRadio9;           // 3x3网格
    QRadioButton* m_gridRadio16;          // 4x4网格
    QRadioButton* m_gridRadio25;          // 5x5网格
    QRadioButton* m_gridRadio36;          // 6x6网格
    
    // 分页控制组件
    QWidget* m_pageControlPanel;          // 分页控制面板
    QPushButton* m_prevPageBtn;           // 上一页按钮
    QPushButton* m_nextPageBtn;           // 下一页按钮
    QSpinBox* m_pageSpinBox;              // 页码输入框
    QPushButton* m_jumpPageBtn;           // 跳转按钮
    QLabel* m_pageStatusLabel;            // 页面状态标签
    
    // 多路流控制组件
    QPushButton* m_addStreamBtn;          // 添加流按钮
    QPushButton* m_removeStreamBtn;       // 移除流按钮
}; 
