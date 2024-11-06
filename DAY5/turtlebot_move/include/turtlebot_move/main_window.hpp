#ifndef turtlebot_move_MAIN_WINDOW_H
#define turtlebot_move_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QMainWindow>
#include "QIcon"
#include "qnode.hpp"
#include <QPainter>
#include <QMouseEvent>
#include "ui_mainwindow.h"


class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

protected:
  void paintEvent(QPaintEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
  void closeEvent(QCloseEvent* event) override;

private:
  Ui::MainWindowDesign* ui;

  QNode* qnode;

  QPoint clicked_pos;     // 추가: 클릭된 위치 저장
  bool has_clicked{false};
  bool isInsideHexagon(const QPoint& point);
};

#endif  // turtlebot_move_MAIN_WINDOW_H
