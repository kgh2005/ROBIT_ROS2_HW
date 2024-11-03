#include "../include/turtlesim_controller/main_window.hpp"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindowDesign)
{
  ui->setupUi(this);

  QIcon icon("://ros-icon.png");
  this->setWindowIcon(icon);

  qnode = new QNode();
  //qnodeThread = new QNodeThread();

  QObject::connect(qnode, SIGNAL(rosShutDown()), this, SLOT(close()));

  ui->pen_slider->setMinimum(1);
  ui->pen_slider->setMaximum(10);

  ui->shape->setMinimum(1);
  ui->shape->setMaximum(5);

  label_5 = ui->label_5;

  connect(ui->shape, SIGNAL(valueChanged(int)), this, SLOT(on_shape_valueChanged(int)));
  connect(ui->pen_slider, SIGNAL(valueChanged(int)), this, SLOT(on_pen_slider_valueChanged(int)));
  connect(qnode, SIGNAL(cmdVelUpdated(double, double)), this, SLOT(updateVelocityDisplay(double, double)));

  connect(qnode, SIGNAL(rosShutDown()), this, SLOT(close()));


  qnode->start();
}

void MainWindow::closeEvent(QCloseEvent* event)
{
  QMainWindow::closeEvent(event);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::updateVelocityDisplay(double linear_x, double angular_z)
{
  label_5->setText(QString("Linear Velocity: %1, Angular: %2").arg(linear_x).arg(angular_z));
}

// 터틀 움직임
void MainWindow::on_btn_w_clicked()
{
  qnode->moveTurtle(1.0, 0.0); // 직진 처리
}
void MainWindow::on_btn_s_clicked()
{
  qnode->moveTurtle(-1.0, 0.0); // 후진 처리
}
void MainWindow::on_btn_a_clicked()
{
  qnode->moveTurtle(0.0, 1.0); // 좌회전 처리
}
void MainWindow::on_btn_d_clicked()
{
  qnode->moveTurtle(0.0, -1.0); // 우회전 처리
}

// background 설정
void MainWindow::on_bg_r_clicked()
{
  int r = 255;
  int g = 0;
  int b = 0;
  qnode->setBackgroundColor(r, g, b);
}
void MainWindow::on_bg_g_clicked()
{
    int r = 0;
    int g = 255;
    int b = 0;
    qnode->setBackgroundColor(r, g, b);
}

void MainWindow::on_bg_b_clicked()
{
    int r = 0;
    int g = 0;
    int b = 255;
    qnode->setBackgroundColor(r, g, b);
}

// pen 설정
void MainWindow::on_pen_slider_valueChanged(int value)
{
  width = value;
  qnode->setPenStyle(r_pen, g_pen, b_pen, width);
}
void MainWindow::on_pen_r_clicked()
{
  r_pen = 255;
  g_pen = 0;
  b_pen = 0;

  qnode->setPenStyle(r_pen, g_pen, b_pen, width);
}
void MainWindow::on_pen_g_clicked()
{
    r_pen = 0;
    g_pen = 255;
    b_pen = 0;

    qnode->setPenStyle(r_pen, g_pen, b_pen, width);
}
void MainWindow::on_pen_b_clicked()
{
    r_pen = 0;
    g_pen = 0;
    b_pen = 255;

    qnode->setPenStyle(r_pen, g_pen, b_pen, width);
}

// shape 설정
void MainWindow::on_shape_valueChanged(int value)
{
  line = value;
  qnode->setLine(value);
}
void MainWindow::on_btn_square_clicked()
{
  qnode->square();
}
void MainWindow::on_btn_circle_clicked()
{
  qnode->circle();
}
void MainWindow::on_btn_triangle_clicked()
{
  qnode->triangle();
}

// turtle shape 설정
void MainWindow::on_btn_ardent_clicked()
{
  //qnode->setTurtleShape("ardent");
}
void MainWindow::on_btn_bouny_clicked()
{
  //qnode->setTurtleShape("bouncy");
}
void MainWindow::on_btn_crystal_clicked()
{
  //qnode->setTurtleShape("crystal");
}
void MainWindow::on_btn_dashing_clicked()
{
  //qnode->setTurtleShape("dashing");
}
