#include "Picture.h"
#include <QHBoxLayout>
#include <QDir>
#include <QFileInfoList>
#include <QPixmap>
#include <QMessageBox>
#include <QCoreApplication>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QWheelEvent>
#include <QSlider>
#include <QLineEdit>
#include <QComboBox>
#include <QFileInfo>
#include <QDateTime>
#include <QRegularExpression>
#include <QGridLayout>
#include <QFile>
#include <QDesktopServices>
#include <QUrl>
#include <QMouseEvent>
#include <algorithm>

Picture::Picture(QWidget* parent)
    : QWidget(parent), currentIndex(0)
{
    this->setWindowTitle("电子相册 - 截图相册");
    this->resize(900, 600);
    // 设置窗口背景为渐变色
    this->setStyleSheet(
        "QWidget { "
        "  background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
        "    stop: 0 #f8f9fa, stop: 1 #e9ecef); "
        "  color: #333; "
        "}"
    );

    // 创建控件
    prevBtn = new QPushButton("上一张", this);
    nextBtn = new QPushButton("下一张", this);
    closeBtn = new QPushButton("关闭", this); // 关闭按钮
    screenshotAlbumBtn = new QPushButton("截图相册", this);
    alarmAlbumBtn = new QPushButton("报警相册", this);
    deleteBtn = new QPushButton("删除图片", this);
    
    // 创建新的控件
    imageSlider = new QSlider(Qt::Horizontal, this);
    jumpEdit = new QLineEdit(this);
    jumpBtn = new QPushButton("跳转", this);
    sortComboBox = new QComboBox(this);
    infoLabel = new QLabel("0/0", this);
    timeLabel = new QLabel("", this);
    
    // 设置滑动条
    imageSlider->setMinimum(1);
    imageSlider->setMaximum(1);
    imageSlider->setValue(1);
    
    // 设置跳转输入框
    jumpEdit->setPlaceholderText("输入序号");
    jumpEdit->setMaximumWidth(80);
    
    // 设置排序下拉框
    sortComboBox->addItem("时间降序");
    sortComboBox->addItem("时间升序");
    sortComboBox->setCurrentIndex(0);
    
    // 设置排序下拉框样式（浅蓝色背景）
    sortComboBox->setStyleSheet(
        "QComboBox {"
        "  background-color: #e3f2fd;"
        "  border: 2px solid #64b5f6;"
        "  border-radius: 8px;"
        "  padding: 6px 12px;"
        "  font-size: 12px;"
        "  font-weight: bold;"
        "  color: #1565c0;"
        "  min-width: 80px;"
        "}"
        "QComboBox:hover {"
        "  background-color: #bbdefb;"
        "  border-color: #42a5f5;"
        "}"
        "QComboBox:focus {"
        "  background-color: #90caf9;"
        "  border-color: #2196f3;"
        "}"
        "QComboBox::drop-down {"
        "  subcontrol-origin: padding;"
        "  subcontrol-position: top right;"
        "  width: 20px;"
        "  border-left: 1px solid #64b5f6;"
        "  border-top-right-radius: 8px;"
        "  border-bottom-right-radius: 8px;"
        "  background-color: #64b5f6;"
        "}"
        "QComboBox::down-arrow {"
        "  image: none;"
        "  border-left: 5px solid transparent;"
        "  border-right: 5px solid transparent;"
        "  border-top: 8px solid white;"
        "  margin-top: 2px;"
        "}"
        "QComboBox QAbstractItemView {"
        "  background-color: #e3f2fd;"
        "  border: 2px solid #64b5f6;"
        "  border-radius: 6px;"
        "  color: #1565c0;"
        "  selection-background-color: #90caf9;"
        "  selection-color: #0d47a1;"
        "  padding: 4px;"
        "}"
        "QComboBox QAbstractItemView::item {"
        "  padding: 6px 12px;"
        "  border-radius: 4px;"
        "}"
        "QComboBox QAbstractItemView::item:hover {"
        "  background-color: #bbdefb;"
        "}"
    );
    
    // 设置信息标签样式
    infoLabel->setStyleSheet(
        "QLabel {"
        "  font-size: 14px;"
        "  font-weight: bold;"
        "  color: #495057;"
        "  padding: 5px;"
        "}"
    );
    
    // 设置时间标签样式（顶部显示）
    timeLabel->setStyleSheet(
        "QLabel {"
        "  background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, "
        "    stop: 0 #667eea, stop: 1 #764ba2);"
        "  border: 2px solid #5a67d8;"
        "  border-radius: 12px;"
        "  color: white;"
        "  font-size: 13px;"
        "  font-weight: bold;"
        "  font-family: 'Microsoft YaHei', sans-serif;"
        "  padding: 8px 16px;"
        "  margin: 0px 10px;"
        "  box-shadow: 0 2px 8px rgba(102, 126, 234, 0.3);"
        "  text-align: center;"
        "}"
    );
    
    // 设置按钮样式
    prevBtn->setStyleSheet(
        "QPushButton {"
        "  background-color: #ffffff;"
        "  border: 2px solid #dee2e6;"
        "  border-radius: 8px;"
        "  font-size: 14px;"
        "  font-weight: bold;"
        "  padding: 8px 16px;"
        "  color: #495057;"
        "}"
        "QPushButton:hover {"
        "  background-color: #e9ecef;"
        "  border-color: #adb5bd;"
        "}"
        "QPushButton:pressed {"
        "  background-color: #dee2e6;"
        "}"
    );
    nextBtn->setStyleSheet(
        "QPushButton {"
        "  background-color: #ffffff;"
        "  border: 2px solid #dee2e6;"
        "  border-radius: 8px;"
        "  font-size: 14px;"
        "  font-weight: bold;"
        "  padding: 8px 16px;"
        "  color: #495057;"
        "}"
        "QPushButton:hover {"
        "  background-color: #e9ecef;"
        "  border-color: #adb5bd;"
        "}"
        "QPushButton:pressed {"
        "  background-color: #dee2e6;"
        "}"
    );
    closeBtn->setStyleSheet(
        "QPushButton {"
        "  background-color: #dc3545;"
        "  border: none;"
        "  border-radius: 6px;"
        "  font-size: 12px;"
        "  font-weight: bold;"
        "  padding: 6px 12px;"
        "  color: white;"
        "}"
        "QPushButton:hover {"
        "  background-color: #c82333;"
        "}"
        "QPushButton:pressed {"
        "  background-color: #bd2130;"
        "}"
    );
    // 截图相册按钮默认选中（橙色），报警相册按钮默认未选中（绿色）
    screenshotAlbumBtn->setStyleSheet(
        "QPushButton {"
        "  background-color: #fd7e14;"
        "  border: 2px solid #fd7e14;"
        "  border-radius: 10px;"
        "  font-size: 14px;"
        "  font-weight: bold;"
        "  padding: 8px 16px;"
        "  color: white;"
        "}"
        "QPushButton:hover {"
        "  background-color: #e8660c;"
        "  border-color: #e8660c;"
        "}"
    );
    alarmAlbumBtn->setStyleSheet(
        "QPushButton {"
        "  background-color: #ffffff;"
        "  border: 2px solid #28a745;"
        "  border-radius: 10px;"
        "  font-size: 14px;"
        "  font-weight: bold;"
        "  padding: 8px 16px;"
        "  color: #28a745;"
        "}"
        "QPushButton:hover {"
        "  background-color: #f8f9fa;"
        "  border-color: #1e7e34;"
        "  color: #1e7e34;"
        "}"
    );
    
    // 删除按钮样式（红色）
    deleteBtn->setStyleSheet(
        "QPushButton {"
        "  background-color: #dc3545;"
        "  border: none;"
        "  border-radius: 6px;"
        "  font-size: 12px;"
        "  font-weight: bold;"
        "  padding: 6px 12px;"
        "  color: white;"
        "}"
        "QPushButton:hover {"
        "  background-color: #c82333;"
        "}"
        "QPushButton:pressed {"
        "  background-color: #bd2130;"
        "}"
    );
    
    // 跳转按钮样式
    jumpBtn->setStyleSheet(
        "QPushButton {"
        "  background-color: #007bff;"
        "  border: none;"
        "  border-radius: 4px;"
        "  font-size: 12px;"
        "  color: white;"
        "  padding: 4px 8px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #0056b3;"
        "}"
    );
    
    // 设置滑动条样式
    imageSlider->setStyleSheet(
        "QSlider::groove:horizontal {"
        "  border: 1px solid #bbb;"
        "  background: white;"
        "  height: 10px;"
        "  border-radius: 4px;"
        "}"
        "QSlider::sub-page:horizontal {"
        "  background: #007bff;"
        "  border: 1px solid #777;"
        "  height: 10px;"
        "  border-radius: 4px;"
        "}"
        "QSlider::add-page:horizontal {"
        "  background: #fff;"
        "  border: 1px solid #777;"
        "  height: 10px;"
        "  border-radius: 4px;"
        "}"
        "QSlider::handle:horizontal {"
        "  background: #007bff;"
        "  border: 1px solid #5c5c5c;"
        "  width: 18px;"
        "  margin-top: -2px;"
        "  margin-bottom: -2px;"
        "  border-radius: 3px;"
        "}"
    );
    
    // 设置按钮大小
    prevBtn->setFixedSize(80, 40);
    nextBtn->setFixedSize(80, 40);
    closeBtn->setFixedSize(60, 30);
    screenshotAlbumBtn->setFixedSize(100, 35);
    alarmAlbumBtn->setFixedSize(100, 35);
    deleteBtn->setFixedSize(80, 30);
    jumpBtn->setFixedSize(50, 25);
    
    imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setMinimumSize(500, 400);
    imageLabel->setStyleSheet(
        "QLabel {"
        "  background-color: #ffffff;"
        "  border: 2px solid #dee2e6;"
        "  border-radius: 12px;"
        "  padding: 20px;"
        "  margin: 10px;"
        "  box-shadow: 0 4px 8px rgba(0,0,0,0.1);"
        "}"
    );

    // 上方按钮布局
    QHBoxLayout* topLayout = new QHBoxLayout();
    
    // 左侧按钮组
    QHBoxLayout* leftButtonLayout = new QHBoxLayout();
    leftButtonLayout->addWidget(screenshotAlbumBtn);
    leftButtonLayout->addWidget(alarmAlbumBtn);
    leftButtonLayout->addStretch(); // 左侧按钮组内部的弹性空间
    
    // 右侧按钮组
    QHBoxLayout* rightButtonLayout = new QHBoxLayout();
    rightButtonLayout->addStretch(); // 右侧按钮组内部的弹性空间
    rightButtonLayout->addWidget(closeBtn);
    
    // 将三个部分添加到顶部布局：左侧按钮组、居中时间标签、右侧按钮组
    topLayout->addLayout(leftButtonLayout, 1); // 左侧占1份空间
    topLayout->addWidget(timeLabel, 0); // 时间标签不占伸缩空间，保持原始大小
    topLayout->addLayout(rightButtonLayout, 1); // 右侧占1份空间

    // 中间区域布局 - 左边按钮、图片区域、右边按钮
    QHBoxLayout* middleLayout = new QHBoxLayout();
    
    // 左侧控制区域
    QVBoxLayout* leftControlLayout = new QVBoxLayout();
    leftControlLayout->addStretch();
    leftControlLayout->addWidget(prevBtn);
    leftControlLayout->addStretch();
    
    // 右侧控制区域
    QVBoxLayout* rightControlLayout = new QVBoxLayout();
    rightControlLayout->addStretch();
    rightControlLayout->addWidget(nextBtn);
    rightControlLayout->addStretch();
    
    middleLayout->addLayout(leftControlLayout, 0);
    middleLayout->addWidget(imageLabel, 1); // 图片区域占主要空间
    middleLayout->addLayout(rightControlLayout, 0);

    // 底部控制区域布局
    QHBoxLayout* bottomControlLayout = new QHBoxLayout();
    
    // 左侧：删除按钮
    bottomControlLayout->addWidget(deleteBtn);
    bottomControlLayout->addStretch();
    
    // 中央：信息标签、滑动条、跳转控件
    bottomControlLayout->addWidget(infoLabel);
    bottomControlLayout->addWidget(imageSlider);
    
    QHBoxLayout* jumpLayout = new QHBoxLayout();
    jumpLayout->addWidget(jumpEdit);
    jumpLayout->addWidget(jumpBtn);
    bottomControlLayout->addLayout(jumpLayout);
    
    // 右侧：排序控件
    bottomControlLayout->addStretch();
    bottomControlLayout->addWidget(new QLabel("排序:"));
    bottomControlLayout->addWidget(sortComboBox);

    // 主布局 - 垂直排列
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(middleLayout, 1); // 中间区域占主要空间
    mainLayout->addLayout(bottomControlLayout); // 底部控制区域
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);

    // 连接信号槽
    connect(prevBtn, &QPushButton::clicked, this, &Picture::onPrevClicked);
    connect(nextBtn, &QPushButton::clicked, this, &Picture::onNextClicked);
    connect(closeBtn, &QPushButton::clicked, this, &Picture::onCloseClicked);
    connect(screenshotAlbumBtn, &QPushButton::clicked, this, &Picture::onScreenshotAlbumClicked);
    connect(alarmAlbumBtn, &QPushButton::clicked, this, &Picture::onAlarmAlbumClicked);
    
    // 新增控件的信号槽连接
    connect(deleteBtn, &QPushButton::clicked, this, &Picture::onDeleteImage);
    connect(imageSlider, &QSlider::valueChanged, this, &Picture::onSliderValueChanged);
    connect(jumpBtn, &QPushButton::clicked, this, &Picture::onJumpToImage);
    connect(jumpEdit, &QLineEdit::returnPressed, this, &Picture::onJumpToImage);
    connect(sortComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Picture::onSortOrderChanged);

    // 加载图片
    loadImages();
    updateImage();
}

Picture::~Picture() {}

void Picture::loadImages()
{
    imageFiles.clear();
    // 确保picture文件夹存在（使用源码路径）
    QString sourcePath = QString(__FILE__).section('/', 0, -2); // 获取源码目录路径
    QString albumPath;
    
    if (isScreenshotAlbum) {
        albumPath = sourcePath + "/picture/save-picture";
    } else {
        albumPath = sourcePath + "/picture/alarm-picture";
    }
    
    QDir dir(albumPath);
    // 如果目录不存在，创建它
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    
    QStringList filters;
    filters << "*.jpg" << "*.png" << "*.jpeg" << "*.bmp" << "*.mp4" << "*.avi" << "*.mov";
    QFileInfoList fileList = dir.entryInfoList(filters, QDir::Files | QDir::NoSymLinks);
    for (const QFileInfo& fileInfo : fileList) {
        imageFiles << fileInfo.absoluteFilePath();
    }
    
    // 对图片进行排序
    sortImages();
    
    currentIndex = 0;
}

void Picture::updateImage()
{
    if (imageFiles.isEmpty()) {
        imageLabel->setText("没有图片");
        prevBtn->setEnabled(false);
        nextBtn->setEnabled(false);
        // 更新信息显示
        infoLabel->setText("0/0");
        timeLabel->setText("");
        // 更新滑动条
        imageSlider->setMinimum(1);
        imageSlider->setMaximum(1);
        imageSlider->setValue(1);
        imageSlider->setEnabled(false);
        return;
    }
    
    QString currentFile = imageFiles[currentIndex];
    QFileInfo fileInfo(currentFile);
    QString suffix = fileInfo.suffix().toLower();
    
    // 检查是否为视频文件
    if (suffix == "mp4" || suffix == "avi" || suffix == "mov") {
        // 对于视频文件，显示视频图标和文件信息
        imageLabel->clear();
        imageLabel->setText(QString("🎬 视频文件\n\n文件名: %1\n大小: %2\n\n双击可用系统默认播放器打开")
                          .arg(fileInfo.fileName())
                          .arg(formatFileSize(fileInfo.size())));
        imageLabel->setStyleSheet(imageLabel->styleSheet() + 
            "QLabel { font-size: 16px; color: #2c3e50; }");
    } else {
        // 对于图片文件，正常显示
        QPixmap pix(currentFile);
        if (pix.isNull()) {
            imageLabel->setText("图片加载失败");
        } else {
            QSize targetSize = imageLabel->size() * scaleFactor;
            imageLabel->setPixmap(pix.scaled(targetSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
        }
    }
    
    // 更新按钮状态
    prevBtn->setEnabled(currentIndex > 0);
    nextBtn->setEnabled(currentIndex < imageFiles.size() - 1);
    
    // 更新图片信息显示
    updateImageInfo();
    
    // 更新滑动条
    imageSlider->setMinimum(1);
    imageSlider->setMaximum(imageFiles.size());
    imageSlider->setValue(currentIndex + 1);
    imageSlider->setEnabled(imageFiles.size() > 1);
    
    // 更新时间标签
    QString timeStr = extractTimeFromFilename(imageFiles[currentIndex]);
    timeLabel->setText(timeStr);
}

void Picture::onPrevClicked()
{
    if (currentIndex > 0) {
        --currentIndex;
        updateImage();
    }
}

void Picture::onNextClicked()
{
    if (currentIndex < imageFiles.size() - 1) {
        ++currentIndex;
        updateImage();
    }
}

void Picture::onCloseClicked()
{
    this->close(); // 关闭窗口，自动释放
}

void Picture::onScreenshotAlbumClicked()
{
    if (!isScreenshotAlbum) {
        // 切换到截图相册模式
        isScreenshotAlbum = true;
        
        // 更新按钮样式 - 截图相册选中（橙色），报警相册未选中（白色边框绿色）
        screenshotAlbumBtn->setStyleSheet(
            "QPushButton {"
            "  background-color: #fd7e14;"
            "  border: 2px solid #fd7e14;"
            "  border-radius: 10px;"
            "  font-size: 14px;"
            "  font-weight: bold;"
            "  padding: 8px 16px;"
            "  color: white;"
            "}"
            "QPushButton:hover {"
            "  background-color: #e8660c;"
            "  border-color: #e8660c;"
            "}"
        );
        alarmAlbumBtn->setStyleSheet(
            "QPushButton {"
            "  background-color: #ffffff;"
            "  border: 2px solid #28a745;"
            "  border-radius: 10px;"
            "  font-size: 14px;"
            "  font-weight: bold;"
            "  padding: 8px 16px;"
            "  color: #28a745;"
            "}"
            "QPushButton:hover {"
            "  background-color: #f8f9fa;"
            "  border-color: #1e7e34;"
            "  color: #1e7e34;"
            "}"
        );
        
        // 重新加载截图相册的图片
        loadImages();
        updateImage();
        
        // 更新窗口标题
        this->setWindowTitle("电子相册 - 截图相册");
    }
}

void Picture::onAlarmAlbumClicked()
{
    if (isScreenshotAlbum) {
        // 切换到报警相册模式
        isScreenshotAlbum = false;
        
        // 更新按钮样式 - 报警相册选中（绿色），截图相册未选中（白色边框橙色）
        screenshotAlbumBtn->setStyleSheet(
            "QPushButton {"
            "  background-color: #ffffff;"
            "  border: 2px solid #fd7e14;"
            "  border-radius: 10px;"
            "  font-size: 14px;"
            "  font-weight: bold;"
            "  padding: 8px 16px;"
            "  color: #fd7e14;"
            "}"
            "QPushButton:hover {"
            "  background-color: #f8f9fa;"
            "  border-color: #e8660c;"
            "  color: #e8660c;"
            "}"
        );
        alarmAlbumBtn->setStyleSheet(
            "QPushButton {"
            "  background-color: #28a745;"
            "  border: 2px solid #28a745;"
            "  border-radius: 10px;"
            "  font-size: 14px;"
            "  font-weight: bold;"
            "  padding: 8px 16px;"
            "  color: white;"
            "}"
            "QPushButton:hover {"
            "  background-color: #1e7e34;"
            "  border-color: #1e7e34;"
            "}"
        );
        
        // 重新加载报警相册的图片
        loadImages();
        updateImage();
        
        // 更新窗口标题
        this->setWindowTitle("电子相册 - 报警相册");
    }
}

void Picture::wheelEvent(QWheelEvent* event)
{
    if (imageFiles.isEmpty()) return;
    if (event->angleDelta().y() > 0) {
        // 向上滚动，放大
        if (scaleFactor < 3.0) {
            scaleFactor += 0.1;
            updateImage();
        }
    } else if (event->angleDelta().y() < 0) {
        // 向下滚动，缩小
        if (scaleFactor > 0.2) {
            scaleFactor -= 0.1;
            updateImage();
        }
    }
    event->accept();
}

void Picture::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (imageFiles.isEmpty()) return;
    
    QString currentFile = imageFiles[currentIndex];
    QFileInfo fileInfo(currentFile);
    QString suffix = fileInfo.suffix().toLower();
    
    // 如果是视频文件，用系统默认播放器打开
    if (suffix == "mp4" || suffix == "avi" || suffix == "mov") {
        QDesktopServices::openUrl(QUrl::fromLocalFile(currentFile));
    }
    
    QWidget::mouseDoubleClickEvent(event);
}

// 新增功能函数实现

void Picture::onSliderValueChanged(int value)
{
    if (imageFiles.isEmpty()) return;
    
    // 滑动条值是1开始的，转换为0开始的索引
    int newIndex = value - 1;
    if (newIndex >= 0 && newIndex < imageFiles.size() && newIndex != currentIndex) {
        currentIndex = newIndex;
        updateImage();
    }
}

void Picture::onJumpToImage()
{
    if (imageFiles.isEmpty()) return;
    
    QString text = jumpEdit->text().trimmed();
    bool ok;
    int targetIndex = text.toInt(&ok);
    
    if (ok && targetIndex >= 1 && targetIndex <= imageFiles.size()) {
        currentIndex = targetIndex - 1; // 转换为0开始的索引
        updateImage();
        jumpEdit->clear(); // 清空输入框
    } else {
        QMessageBox::warning(this, "错误", 
            QString("请输入有效的序号 (1-%1)").arg(imageFiles.size()));
        jumpEdit->clear();
    }
}

void Picture::onDeleteImage()
{
    if (imageFiles.isEmpty()) return;
    
    QString currentFile = imageFiles[currentIndex];
    QString fileName = QFileInfo(currentFile).fileName();
    
    int ret = QMessageBox::question(this, "确认删除", 
        QString("确定要删除图片 \"%1\" 吗？").arg(fileName),
        QMessageBox::Yes | QMessageBox::No);
    
    if (ret == QMessageBox::Yes) {
        // 删除文件
        if (QFile::remove(currentFile)) {
            // 从列表中移除
            imageFiles.removeAt(currentIndex);
            
            // 调整当前索引
            if (imageFiles.isEmpty()) {
                currentIndex = 0;
            } else if (currentIndex >= imageFiles.size()) {
                currentIndex = imageFiles.size() - 1;
            }
            
            // 重新更新显示
            updateImage();
        } else {
            QMessageBox::warning(this, "删除失败", "无法删除该图片文件");
        }
    }
}

void Picture::onSortOrderChanged()
{
    // 获取排序方式
    isAscendingOrder = (sortComboBox->currentIndex() == 1);
    
    // 重新排序
    sortImages();
    
    // 重置到第一张图片
    currentIndex = 0;
    updateImage();
}

void Picture::updateImageInfo()
{
    if (imageFiles.isEmpty()) {
        infoLabel->setText("0/0");
    } else {
        infoLabel->setText(QString("%1/%2").arg(currentIndex + 1).arg(imageFiles.size()));
    }
}

void Picture::sortImages()
{
    if (imageFiles.isEmpty()) return;
    
    // 使用自定义排序函数，根据文件名中的时间戳排序
    std::sort(imageFiles.begin(), imageFiles.end(), [this](const QString& a, const QString& b) {
        QString timeA = extractTimeFromFilename(a);
        QString timeB = extractTimeFromFilename(b);
        
        if (isAscendingOrder) {
            return timeA < timeB; // 升序
        } else {
            return timeA > timeB; // 降序
        }
    });
}

QString Picture::extractTimeFromFilename(const QString& filename)
{
    QFileInfo fileInfo(filename);
    QString baseName = fileInfo.baseName();
    
    // 尝试从文件名中提取时间戳
    // 假设文件名格式为：screenshot_20240101_123456.jpg 或 alarm_20240101_123456.jpg
    QRegularExpression timeRegex(R"((\d{8}_\d{6}))");
    QRegularExpressionMatch match = timeRegex.match(baseName);
    
    if (match.hasMatch()) {
        QString timeStr = match.captured(1);
        // 转换为更易读的格式：20240101_123456 -> 2024-01-01 12:34:56
        if (timeStr.length() == 15) { // 8位日期 + 1位下划线 + 6位时间
            QString date = timeStr.left(8);
            QString time = timeStr.right(6);
            QString formattedDate = QString("%1-%2-%3")
                .arg(date.left(4))     // 年
                .arg(date.mid(4, 2))   // 月
                .arg(date.right(2));   // 日
            QString formattedTime = QString("%1:%2:%3")
                .arg(time.left(2))     // 时
                .arg(time.mid(2, 2))   // 分
                .arg(time.right(2));   // 秒
            return formattedDate + " " + formattedTime;
        }
    }
    
    // 如果无法从文件名提取时间，使用文件修改时间
    QDateTime modifyTime = fileInfo.lastModified();
    return modifyTime.toString("yyyy-MM-dd hh:mm:ss");
}

QString Picture::formatFileSize(qint64 size)
{
    const qint64 KB = 1024;
    const qint64 MB = KB * 1024;
    const qint64 GB = MB * 1024;
    
    if (size >= GB) {
        return QString::number(size / (double)GB, 'f', 2) + " GB";
    } else if (size >= MB) {
        return QString::number(size / (double)MB, 'f', 2) + " MB";
    } else if (size >= KB) {
        return QString::number(size / (double)KB, 'f', 2) + " KB";
    } else {
        return QString::number(size) + " B";
    }
}