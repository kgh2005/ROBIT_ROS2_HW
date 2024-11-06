#include "../include/turtlebot_move/main_window.hpp"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindowDesign)
{
  ui->setupUi(this);

  QIcon icon("://ros-icon.png");
  this->setWindowIcon(icon);

  qnode = new QNode();

  QObject::connect(qnode, SIGNAL(rosShutDown()), this, SLOT(close()));
}

void MainWindow::paintEvent(QPaintEvent* event)
{
  QMainWindow::paintEvent(event);

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  // 육각형 그리기
  int centerX = width() / 2;
  int centerY = height() / 2;
  int radius = 250;

  painter.setPen(Qt::black);
  painter.setBrush(QColor(100, 200, 250));

  QPolygon hexagon;
  for (int i = 0; i < 6; ++i) {
    double angle_deg = 60 * i - 30;
    double angle_rad = angle_deg * M_PI / 180.0;
    int x = centerX + radius * std::cos(angle_rad);
    int y = centerY + radius * std::sin(angle_rad);
    hexagon << QPoint(x, y);
  }
  painter.drawPolygon(hexagon);

  // 클릭한 위치에 점 그리기
  if (has_clicked) {
    painter.setPen(Qt::red);
    painter.setBrush(Qt::red);
    painter.drawEllipse(clicked_pos, 10, 10);
  }
}

bool MainWindow::isInsideHexagon(const QPoint& point)
{
  int centerX = width() / 2;
  int centerY = height() / 2;
  int radius = 250;

  QPolygon hexagon;
  for (int i = 0; i < 6; ++i) {
    double angle_deg = 60 * i - 30;
    double angle_rad = angle_deg * M_PI / 180.0;
    int x = centerX + radius * std::cos(angle_rad);
    int y = centerY + radius * std::sin(angle_rad);
    hexagon << QPoint(x, y);
  }

  return hexagon.containsPoint(point, Qt::OddEvenFill);
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
  if (event->button() == Qt::LeftButton) {
    QPoint click_pos = event->pos();
    if (isInsideHexagon(click_pos)) {
      clicked_pos = click_pos;
      has_clicked = true;
      update();
    }
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
