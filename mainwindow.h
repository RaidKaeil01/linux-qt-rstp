#pragma once
#include <QMainWindow>

class Model;
class View;
class Controller;
class Tcpserver;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void switchToSingleMode();  // 切换到单路模式
    void switchToMultiMode();   // 切换到多路模式
    void showAbout();           // 显示关于对话框

private:
    void setupUI();             // 设置用户界面
    void setupSingleView();     // 设置统一视图
    void setupMenus();          // 设置菜单

    // TCP服务器
    Tcpserver* m_tcpServer;
    
    // 统一界面组件
    View* m_singleView;         // 统一视图（支持单路和多路）
    Model* m_model;
    Controller* m_controller;
};