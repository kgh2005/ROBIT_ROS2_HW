/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date August 2024
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include "../include/usbcamera/main_window.hpp"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindowDesign)
{
  ui->setupUi(this);

  QIcon icon("://ros-icon.png");
  this->setWindowIcon(icon);

  qnode = new QNode();

  ui->label->setFixedSize(640, 480);

  QObject::connect(qnode, SIGNAL(rosShutDown()), this, SLOT(close()));
  QObject::connect(qnode, SIGNAL(imageReceived(QImage)), this, SLOT(updateImage(QImage)));  // 이미지 수신 시 연결

  //qnode->start();
}

void MainWindow::updateImage(const QImage &image)
{
  if (QThread::currentThread() == this->thread()) // 현재 실행 중인 스레드가 GUI 스레드인지 확인
  {
    // 이지미를 QPixmap으로 변환하고, QLabel 크게 맞추어 비율을 유지하며 조정
    QPixmap pixmap = QPixmap::fromImage(image).scaled(ui->label->size(), Qt::KeepAspectRatio);
    ui->label->setPixmap(pixmap);
  }
  else
  {
    QMetaObject::invokeMethod(this, [this, image]()
    {
      QPixmap pixmap = QPixmap::fromImage(image).scaled(ui->label->size(), Qt::KeepAspectRatio);
      ui->label->setPixmap(pixmap);
    }, Qt::QueuedConnection);
  }
}

void MainWindow::closeEvent(QCloseEvent* event)
{
  QMainWindow::closeEvent(event);
}

MainWindow::~MainWindow()
{
  delete ui;
}
