#include "../include/cam_params_pkg/second_window.hpp"

SecondWindow::SecondWindow(QWidget* parent)
  : QMainWindow(parent), ui(new Ui::SecondWindowDesign)
{
  ui->setupUi(this);

  QIcon icon(":/images/icon.png");
  this->setWindowIcon(icon);

  // ProcessImgNode 초기화 및 시작
  processImgNode = new ProcessImgNode(rclcpp::Node::make_shared("image_processing_node"), this);
  processImgNode->start();  // QThread 실행


  // 이미지 처리 결과를 UI의 라벨에 업데이트하는 연결
  connect(processImgNode, &ProcessImgNode::originalImageProcessed, this, [this](const QImage& image) {
    ui->frame_org->setPixmap(QPixmap::fromImage(image));
  });

  // 이진화 이미지 표시 연결
  connect(processImgNode, &ProcessImgNode::binaryImageProcessed, this, [this](const QImage& image) {
    ui->frame_1->setPixmap(QPixmap::fromImage(image));
  });

  connect(processImgNode, &ProcessImgNode::parameterBinaryImageProcessed, this, [this](const QImage& image) {
    ui->frame_2->setPixmap(QPixmap::fromImage(image));
  });
}

SecondWindow::~SecondWindow()
{
  if (processImgNode) {
    processImgNode->quit();  // QThread 종료 요청
    processImgNode->wait();  // 쓰레드가 종료될 때까지 대기
    delete processImgNode;   // 메모리 해제
  }
  delete ui;
}

void SecondWindow::closeEvent(QCloseEvent* event)
{
  QMainWindow::closeEvent(event);
}
