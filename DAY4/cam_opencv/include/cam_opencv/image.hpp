#ifndef cam_opencv_IMAGE_WINDOW_H
#define cam_opencv_IMAGE_WINDOW_H

#include <QMainWindow>
#include "QIcon"
#include "QLabel"
#include "qnode.hpp"
#include "ui_image.h"  // image.ui 파일에 대응하는 헤더 파일을 포함합니다.

class ImageWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit ImageWindow(QWidget* parent = nullptr);
  ~ImageWindow();

  QNode* qnode;               // QNode 인스턴스를 통해 ROS 노드와 상호작용

private slots:
    void updateImage(const QImage& image);  // 이미지 업데이트 슬롯

private:
  Ui::ImageWindowDesign* ui;  // ImageWindowDesign으로 수정

};

#endif
