#ifndef turtlebot_move_MAIN_WINDOW_H
#define turtlebot_move_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QMainWindow>
#include "QIcon"
#include "qnode.hpp"
#include <QPainter>
#include <QPolygon>
#include <QMouseEvent>
#include <cmath>
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

private Q_SLOTS:
  void updateRobotPosition(double x, double y);

private:
  Ui::MainWindowDesign* ui;

  QNode* qnode;
  QPointF current_pos;
  QPointF goal_pos;

  QPointF guiToMap(const QPoint& gui_point);
  QPoint mapToGui(const QPointF& map_point);
};

#endif  // turtlebot_move_MAIN_WINDOW_H
