#ifndef CAM_PARAMS_PKG_MAIN_WINDOW_H
#define CAM_PARAMS_PKG_MAIN_WINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QDebug>
#include "ui_mainwindow.h"
#include "cam_params_pkg/parameter_img_node.hpp"
#include "cam_params_pkg/process_img_node.hpp"


//class ParameterImgNode;  // 전방 선언으로 parameter_img_node 사용

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

private slots:

  void sendParameterValue(const QString& paramName, int value);


  void on_hue_low_slider_valueChanged(int value);
  void on_hue_low_spinbox_valueChanged(int arg1);
  void on_hue_upp_slider_valueChanged(int value);
  void on_hue_upp_spinbox_valueChanged(int arg1);
  void on_satr_low_slider_valueChanged(int value);
  void on_satr_low_spinbox_valueChanged(int arg1);
  void on_satr_upp_slider_valueChanged(int value);
  void on_satr_upp_spinbox_valueChanged(int arg1);
  void on_val_low_slider_valueChanged(int value);
  void on_val_low_spinbox_valueChanged(int arg1);
  void on_val_upp_slider_valueChanged(int value);
  void on_val_upp_spinbox_valueChanged(int arg1);

  // void on_hue_low_slider_2_valueChanged(int value);
  // void on_hue_low_spinbox_2_valueChanged(int arg1);
  // void on_hue_upp_slider_2_valueChanged(int value);
  // void on_hue_upp_spinbox_2_valueChanged(int arg1);
  // void on_satr_low_slider_2_valueChanged(int value);
  // void on_satr_low_spinbox_2_valueChanged(int arg1);
  // void on_satr_upp_slider_2_valueChanged(int value);
  // void on_satr_upp_spinbox_2_valueChanged(int arg1);
  // void on_val_low_slider_2_valueChanged(int value);
  // void on_val_low_spinbox_2_valueChanged(int arg1);
  // void on_val_upp_slider_2_valueChanged(int value);
  // void on_val_upp_spinbox_2_valueChanged(int arg1);

  // void on_hue_low_slider_3_valueChanged(int value);
  // void on_hue_low_spinbox_3_valueChanged(int arg1);
  // void on_hue_upp_slider_3_valueChanged(int value);
  // void on_hue_upp_spinbox_3_valueChanged(int arg1);
  // void on_satr_low_slider_3_valueChanged(int value);
  // void on_satr_low_spinbox_3_valueChanged(int arg1);
  // void on_satr_upp_slider_3_valueChanged(int value);
  // void on_satr_upp_spinbox_3_valueChanged(int arg1);
  // void on_val_low_slider_3_valueChanged(int value);
  // void on_val_low_spinbox_3_valueChanged(int arg1);
  // void on_val_upp_slider_3_valueChanged(int value);
  // void on_val_upp_spinbox_3_valueChanged(int arg1);

  //void updateParameters();


private:
  Ui::MainWindowDesign* ui;
  ParameterImgNode* parameterImgNode;  // 파라미터 설정 노드 객체
  ProcessImgNode* processImgNode;

  rclcpp::Node::SharedPtr node_;
  void closeEvent(QCloseEvent* event);

    int hueLow_1; // Hue low 값
    int hueUpp_1; // Hue upper 값
    int satrLow_1; // Saturation low 값
    int satrUpp_1; // Saturation upper 값
    int valLow_1; // Value low 값
    int valUpp_1; // Value upper 값
    int value; // 사용하고자 하는 값
};

#endif  // CAM_PARAMS_PKG_MAIN_WINDOW_H
