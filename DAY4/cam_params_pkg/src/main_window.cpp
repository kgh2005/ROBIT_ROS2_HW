#include "../include/cam_params_pkg/main_window.hpp"

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent), ui(new Ui::MainWindowDesign)
{
  ui->setupUi(this);

  QIcon icon(":/images/icon.png");
  this->setWindowIcon(icon);

  ui->hue_low_slider->setRange(0, 180);
  ui->hue_low_spinbox->setRange(0, 180);
  ui->hue_upp_slider->setRange(0, 180);
  ui->hue_upp_spinbox->setRange(0, 180);
  ui->satr_low_slider->setRange(0, 255);
  ui->satr_low_spinbox->setRange(0, 255);
  ui->satr_upp_slider->setRange(0, 255);
  ui->satr_upp_spinbox->setRange(0, 255);
  ui->val_low_slider->setRange(0, 255);
  ui->val_low_spinbox->setRange(0, 255);
  ui->val_upp_slider->setRange(0, 255);
  ui->val_upp_spinbox->setRange(0, 255);


  // ProcessImgNode 초기화
  processImgNode = new ProcessImgNode(rclcpp::Node::make_shared("process_img_node"), this);
  processImgNode->start();

  // ParameterImgNode 초기화 및 연결 설정
  parameterImgNode = new ParameterImgNode(rclcpp::Node::make_shared("parameter_client_node"), this);
  parameterImgNode->start();

  // ROS 종료 시그널 처리
  connect(parameterImgNode, &ParameterImgNode::finished, this, &MainWindow::close);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
  QMainWindow::closeEvent(event);
}


void MainWindow::sendParameterValue(const QString& paramName, int value) {
    if (parameterImgNode) {
        // 파라미터 이름에 따라 값을 설정
        if (paramName == "hue_low") {
            hueLow_1 = value;
        } else if (paramName == "hue_upp") {
            hueUpp_1 = value;
        } else if (paramName == "saturation_low") {
            satrLow_1 = value;
        } else if (paramName == "saturation_upp") {
            satrUpp_1 = value;
        } else if (paramName == "value_low") {
            valLow_1 = value;
        } else if (paramName == "value_upp") {
            valUpp_1 = value;
        }
        processImgNode->updateHSVParameters(hueLow_1, hueUpp_1, satrLow_1, satrUpp_1, valLow_1, valUpp_1);
        // // `ProcessImgNode`의 HSV 파라미터 업데이트 메서드 호출
        // if (processImgNode) {
        //     processImgNode->updateHSVParameters(hueLow_1, hueUpp_1, satrLow_1, satrUpp_1, valLow_1, valUpp_1);
        // } else {
        //     qWarning() << "ProcessImgNode is not initialized.";
        // }
    } else {
        qWarning() << "parameterImgNode is not initialized.";
    }
}

// 슬라이더와 스핀박스의 값이 변경될 때 파라미터를 업데이트
void MainWindow::on_hue_low_slider_valueChanged(int value) {
    ui->hue_low_spinbox->setValue(value);
    sendParameterValue("hue_low", value);
}

void MainWindow::on_hue_low_spinbox_valueChanged(int value) {
    ui->hue_low_slider->setValue(value);
    sendParameterValue("hue_low", value);
}

void MainWindow::on_hue_upp_slider_valueChanged(int value) {
    ui->hue_upp_spinbox->setValue(value);
    sendParameterValue("hue_upp", value);
}

void MainWindow::on_hue_upp_spinbox_valueChanged(int value) {
    ui->hue_upp_slider->setValue(value);
    sendParameterValue("hue_upp", value);
}

void MainWindow::on_satr_low_slider_valueChanged(int value) {
    ui->satr_low_spinbox->setValue(value);
    sendParameterValue("saturation_low", value);
}

void MainWindow::on_satr_low_spinbox_valueChanged(int value) {
    ui->satr_low_slider->setValue(value);
    sendParameterValue("saturation_low", value);
}

void MainWindow::on_satr_upp_slider_valueChanged(int value) {
    ui->satr_upp_spinbox->setValue(value);
    sendParameterValue("saturation_upp", value);
}

void MainWindow::on_satr_upp_spinbox_valueChanged(int value) {
    ui->satr_upp_slider->setValue(value);
    sendParameterValue("saturation_upp", value);
}

void MainWindow::on_val_low_slider_valueChanged(int value) {
    ui->val_low_spinbox->setValue(value);
    sendParameterValue("value_low", value);
}

void MainWindow::on_val_low_spinbox_valueChanged(int value) {
    ui->val_low_slider->setValue(value);
    sendParameterValue("value_low", value);
}

void MainWindow::on_val_upp_slider_valueChanged(int value) {
    ui->val_upp_spinbox->setValue(value);
    sendParameterValue("value_upp", value);
}

void MainWindow::on_val_upp_spinbox_valueChanged(int value) {
    ui->val_upp_slider->setValue(value);
    sendParameterValue("value_upp", value);
}


// // 2
// void MainWindow::on_hue_low_slider_2_valueChanged(int value){
//   ui->hue_low_spinbox_2->setValue(value);
// }
// void MainWindow::on_hue_low_spinbox_2_valueChanged(int arg1){
//   ui->hue_low_slider_2->setValue(arg1);
// }
// void MainWindow::on_hue_upp_slider_2_valueChanged(int value){
//   ui->hue_upp_spinbox_2->setValue(value);
// }
// void MainWindow::on_hue_upp_spinbox_2_valueChanged(int arg1){
//   ui->hue_upp_slider_2->setValue(arg1);
// }
// void MainWindow::on_satr_low_slider_2_valueChanged(int value){
//   ui->satr_low_spinbox_2->setValue(value);
// }
// void MainWindow::on_satr_low_spinbox_2_valueChanged(int arg1){
//   ui->satr_low_slider_2->setValue(arg1);
// }
// void MainWindow::on_satr_upp_slider_2_valueChanged(int value){
//   ui->satr_upp_spinbox_2->setValue(value);
// }
// void MainWindow::on_satr_upp_spinbox_2_valueChanged(int arg1){
//   ui->satr_upp_slider_2->setValue(arg1);
// }
// void MainWindow::on_val_low_slider_2_valueChanged(int value){
//   ui->val_low_spinbox_2->setValue(value);
// }
// void MainWindow::on_val_low_spinbox_2_valueChanged(int arg1){
//   ui->val_low_slider_2->setValue(arg1);
// }
// void MainWindow::on_val_upp_slider_2_valueChanged(int value){
//   ui->val_upp_spinbox_2->setValue(value);
// }
// void MainWindow::on_val_upp_spinbox_2_valueChanged(int arg1){
//   ui->val_upp_slider_2->setValue(arg1);
// }

// // 3
// void MainWindow::on_hue_low_slider_3_valueChanged(int value){
//   ui->hue_low_spinbox_3->setValue(value);
// }
// void MainWindow::on_hue_low_spinbox_3_valueChanged(int arg1){
//   ui->hue_low_slider_3->setValue(arg1);
// }
// void MainWindow::on_hue_upp_slider_3_valueChanged(int value){
//   ui->hue_upp_spinbox_3->setValue(value);
// }
// void MainWindow::on_hue_upp_spinbox_3_valueChanged(int arg1){
//   ui->hue_upp_slider_3->setValue(arg1);
// }
// void MainWindow::on_satr_low_slider_3_valueChanged(int value){
//   ui->satr_low_spinbox_3->setValue(value);
// }
// void MainWindow::on_satr_low_spinbox_3_valueChanged(int arg1){
//   ui->satr_low_slider_3->setValue(arg1);
// }
// void MainWindow::on_satr_upp_slider_3_valueChanged(int value){
//   ui->satr_upp_spinbox_3->setValue(value);
// }
// void MainWindow::on_satr_upp_spinbox_3_valueChanged(int arg1){
//   ui->satr_upp_slider_3->setValue(arg1);
// }
// void MainWindow::on_val_low_slider_3_valueChanged(int value){
//   ui->val_low_spinbox_3->setValue(value);
// }
// void MainWindow::on_val_low_spinbox_3_valueChanged(int arg1){
//   ui->val_low_slider_3->setValue(arg1);
// }
// void MainWindow::on_val_upp_slider_3_valueChanged(int value){
//   ui->val_upp_spinbox_3->setValue(value);
// }
// void MainWindow::on_val_upp_spinbox_3_valueChanged(int arg1){
//   ui->val_upp_slider_3->setValue(arg1);
// }
