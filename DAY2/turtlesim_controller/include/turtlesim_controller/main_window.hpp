/**
 * @file /include/qt_turtlesim_controller/main_window.hpp
 *
 * @brief Qt based gui for %(package)s.
 *
 * @date August 2024
 **/

#ifndef qt_turtlesim_controller_MAIN_WINDOW_H
#define qt_turtlesim_controller_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QMainWindow>
#include "QIcon"
#include "qnode.hpp"
#include "ui_mainwindow.h"

/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();
  QNode* qnode;
  int line = 1;

private:
  Ui::MainWindowDesign* ui;
  void closeEvent(QCloseEvent* event);

  int width = 1;
  int r_pen = 255;
  int g_pen = 255;
  int b_pen = 255;

  QLabel *label_5;


private slots:
  void on_btn_w_clicked();
  void on_btn_a_clicked();
  void on_btn_s_clicked();
  void on_btn_d_clicked();

  void updateVelocityDisplay(double linear_x, double angular_z);

  void on_bg_r_clicked();
  void on_bg_g_clicked();
  void on_bg_b_clicked();

  void on_pen_r_clicked();
  void on_pen_g_clicked();
  void on_pen_b_clicked();
  void on_pen_slider_valueChanged(int value);

  void on_btn_square_clicked();
  void on_btn_circle_clicked();
  void on_btn_triangle_clicked();
  void on_shape_valueChanged(int value);

  void on_btn_ardent_clicked();
  void on_btn_bouny_clicked();
  void on_btn_crystal_clicked();
  void on_btn_dashing_clicked();
};



#endif  // qt_turtlesim_controller_MAIN_WINDOW_H
