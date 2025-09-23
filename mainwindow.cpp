#include "mainwindow.h"
#include "model.h"
#include "view.h"
#include "controller.h"
#include "Tcpserver.h"
#include <QDebug>
#include <QApplication>
#include <QIcon>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_tcpServer(nullptr),
      m_singleView(nullptr), m_model(nullptr), m_controller(nullptr)
{
    // 设置主窗口大小
    this->resize(1300, 650);
    
    // 设置窗口标题
    this->setWindowTitle("RTSP视频监控系统");
    
    // 设置窗口图标
    this->setWindowIcon(QIcon(":icon/logo-xijiangyue"));
    
    // 设置应用程序图标（在任务栏等地方显示）
    QApplication::setWindowIcon(QIcon(":icon/logo-xijiangyue"));

    // 创建TCP服务器并自动启动监听
    m_tcpServer = new Tcpserver();
    m_tcpServer->setAttribute(Qt::WA_DeleteOnClose, false); // 不自动删除
    // 隐藏TCP服务器窗口
    m_tcpServer->hide();
    // 自动启动TCP监听
    m_tcpServer->startListen();
    qDebug() << "TCP服务器已自动启动并开始监听";
    
    setupUI();
    setupMenus();
}

MainWindow::~MainWindow()
{
    // 清理TCP服务器
    if (m_tcpServer) {
        m_tcpServer->stopListen();
        delete m_tcpServer;
        m_tcpServer = nullptr;
    }
}

void MainWindow::setupUI()
{
    // 创建统一视图（包含单路和多路功能）
    setupSingleView();
    
    // 设置为中心窗口部件
    setCentralWidget(m_singleView);
}

void MainWindow::setupSingleView()
{
    // 创建模型对象
    m_model = new Model(this);
    // 创建统一视图对象（支持单路和多路）
    m_singleView = new View(this);
    // 创建控制器对象
    m_controller = new Controller(m_model, m_singleView, this);
    
    // 将TCP服务器指针传递给Controller
    m_controller->setTcpServer(m_tcpServer);
}

void MainWindow::setupMenus()
{
    // 创建菜单栏
    QMenuBar* menuBar = this->menuBar();
    
    // 帮助菜单
    QMenu* helpMenu = menuBar->addMenu("帮助(&H)");
    
    QAction* aboutAction = new QAction("关于(&A)", this);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAbout);
    helpMenu->addAction(aboutAction);
}

void MainWindow::switchToSingleMode()
{
    // 在统一界面中切换到单路模式（通过网格选择1实现）
    if (m_singleView) {
        m_singleView->setVideoDisplayMode(false);
        qDebug() << "切换到单路模式";
    }
}

void MainWindow::switchToMultiMode()
{
    // 在统一界面中切换到多路模式（通过网格选择4/9/16等实现）
    if (m_singleView) {
        m_singleView->setVideoDisplayMode(true);
        qDebug() << "切换到多路模式";
    }
}

void MainWindow::showAbout()
{
    QMessageBox::about(this, "关于",
        "RTSP视频监控系统 - 统一界面版\n\n"
        "功能特性:\n"
        "• 单路RTSP视频播放\n"
        "• 多路RTSP视频同时播放\n"
        "• 统一界面：底部网格选择实现单路/多路切换\n"
        "• 网格布局显示 (1x1/2x2/3x3/4x4/5x5/6x6)\n"
        "• 视频流管理和控制\n"
        "• 目标检测和识别\n"
        "• TCP网络通信\n\n"
        "版本: 2.1 - 统一界面\n"
        "构建时间: " __DATE__ " " __TIME__);
}
