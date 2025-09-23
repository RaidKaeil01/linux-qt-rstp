#pragma once
#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <opencv2/opencv.hpp>
#include "model.h"
#include "view.h"
#include "Picture.h"
#include "Tcpserver.h"
#include "VideoLabel.h"  // 包含RectangleBox定义
#include "detectlist.h"  // 包含DetectList类
#include "MultiStreamManager.h"
#include "MultiStreamController.h"

class Plan; // 前向声明

// 方案数据结构前向声明
struct PlanData;

class Controller : public QObject {
    Q_OBJECT
public:
    Controller(Model* model, View* view, QObject* parent = nullptr);
    ~Controller();
    
    // 设置TCP服务器指针
    void setTcpServer(Tcpserver* tcpServer);

public slots:
    void ButtonClickedHandler();      //主界面标签按键槽
    void ServoButtonClickedHandler(); //云台按键槽
    void FunButtonClickedHandler();   //功能按钮槽
    void onTcpClientConnected(const QString& ip, quint16 port); // 新增：处理TCP客户端连接成功
    
    // 多路模式槽函数
    void onVideoDisplayModeChanged(bool multiMode); // 视频显示模式改变
    void onGridLayoutChanged(int gridNum);           // 网格布局改变
    void onStreamAdded(const QString& url);          // 视频流添加
    void onStreamRemoved(int handle);                // 视频流移除

        
private slots:
    void onAddCameraClicked();      //添加摄像头槽
    void onFrameReady(const QImage& img); //视频帧槽
    void onDetectListSelectionChanged(const QSet<int>& selectedIds); //对象列表选择变化槽 
    void onRectangleConfirmed(const RectangleBox& rect);// 处理用户确认的矩形框（绝对坐标），用于目标选定等功能
    // 处理用户确认的矩形框（归一化坐标和绝对坐标），便于后续处理如检测、标注等
    void onNormalizedRectangleConfirmed(const NormalizedRectangleBox& normRect, const RectangleBox& absRect);
    void onPlanApplied(const PlanData& plan); // 处理方案应用槽
    void onDetectionDataReceived(const QString& detectionData); // 新增：处理检测数据接收槽

private:
    Model* m_model; //模型指针  
    View* m_view;   //视图指针
    bool m_paused = false; //暂停标志
    QImage m_lastImage; // 保存最近一帧图像
    void saveImage();   // 截图保存函数
    void saveAlarmImage(const QString& detectionInfo); // 新增：报警图像保存函数
    
    // 录制相关
    bool m_isRecording = false; // 录制状态标志
    cv::VideoWriter* m_videoWriter = nullptr; // 视频写入器
    QString m_recordFileName; // 当前录制文件名
    void startRecording(); // 开始录制
    void stopRecording();  // 停止录制
    void writeVideoFrame(const QImage& frame); // 写入视频帧
    Tcpserver* tcpWin = nullptr; // TCP服务器窗口指针
    DetectList* m_detectList = nullptr; // 对象检测列表窗口指针
    Plan* m_plan = nullptr; // 方案预选窗口指针
    QSet<int> m_selectedObjectIds; // 当前选中的对象ID集合
    
    // 功能按钮状态管理
    void updateButtonDependencies(int clickedButtonId, bool isChecked);
    
    // 多路模式支持
    bool m_isMultiStreamMode = false;         // 当前是否为多路模式
    void initMultiStreamConnections();        // 初始化多路流信号连接
    void handleSingleStreamMode();            // 处理单路模式逻辑
    void handleMultiStreamMode();             // 处理多路模式逻辑
};
