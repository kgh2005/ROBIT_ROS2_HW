#include "cam_opencv/image.hpp"

// ImageWindow constructor
ImageWindow::ImageWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::ImageWindowDesign), qnode(new QNode)  // qnode를 초기화
{
    ui->setupUi(this);  // image.ui의 UI 요소 설정
    setWindowIcon(QIcon(":/resources/images/icon.png"));  // 아이콘 설정

    ui->ImageOriginal->setFixedSize(640, 480);

    // qnode와 종료 시그널 연결
    if (qnode)  // qnode가 nullptr가 아닌 경우에만 연결
    {
        QObject::connect(qnode, SIGNAL(rosShutDown()), this, SLOT(close()));
        QObject::connect(qnode, &QNode::imageReceived, this, &ImageWindow::updateImage);  // 이미지 수신 시그널 연결
    }
}

// ImageWindow destructor
ImageWindow::~ImageWindow()
{
    delete ui;
    delete qnode;  // qnode 포인터도 삭제
}
// 이미지 업데이트 슬롯
void ImageWindow::updateImage(const QImage& image)
{
    QPixmap pixmap = QPixmap::fromImage(image).scaled(ui->ImageOriginal->size(), Qt::KeepAspectRatio);
    ui->ImageOriginal->setPixmap(QPixmap::fromImage(image));  // QLabel에 이미지 표시
}
