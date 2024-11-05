#ifndef CAM_PARAMS_PKG_SECOND_WINDOW_H
#define CAM_PARAMS_PKG_SECOND_WINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QLabel>
#include "ui_secondwindow.h"
#include "process_img_node.hpp"

class ProcessImgNode;  // 전방 선언으로 process_img_node 사용

class SecondWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit SecondWindow(QWidget* parent = nullptr);
  ~SecondWindow();

private:
  Ui::SecondWindowDesign* ui;
  ProcessImgNode* processImgNode;  // 이미지 처리 노드 객체
  void closeEvent(QCloseEvent* event);
};

#endif  // CAM_PARAMS_PKG_SECOND_WINDOW_H
