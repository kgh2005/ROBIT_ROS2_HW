#include "../include/turtlebot_move/main_window.hpp"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindowDesign)
{
  ui->setupUi(this);

  QIcon icon("://ros-icon.png");
  this->setWindowIcon(icon);

  qnode = new QNode();

  QObject::connect(qnode, SIGNAL(rosShutDown()), this, SLOT(close()));
  QObject::connect(qnode, SIGNAL(updateCurrentPos(double, double)),
                  this, SLOT(updateRobotPosition(double, double)));
}

void MainWindow::paintEvent(QPaintEvent* event)
{
  QMainWindow::paintEvent(event);  // 기본 위젯의 paintEvent 처리

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  // 선 및 색상 설정
  painter.setPen(Qt::black);
  painter.setBrush(QColor(100, 200, 250));

  // 육각형 중심 및 반지름 설정
  int centerX = width() / 2;
  int centerY = height() / 2;
  int radius = 250;

  // 육각형 꼭지점 계산
  QPolygon hexagon;
  for (int i = 0; i < 6; ++i) {
    double angle_deg = 60 * i - 30;  // 각 꼭지점의 각도
    double angle_rad = angle_deg * M_PI / 180.0;  // 각도를 라디안으로 변환
    int x = centerX + radius * std::cos(angle_rad);
    int y = centerY + radius * std::sin(angle_rad);
    hexagon << QPoint(x, y);
  }

  // 육각형 그리기
  painter.drawPolygon(hexagon);


    // 현재 위치 표시 (빨간색 원)
  QPoint current_gui = mapToGui(current_pos);
  painter.setPen(Qt::red);
  painter.setBrush(Qt::red);
  painter.drawEllipse(current_gui, 10, 10);

  // 목표 위치 표시 (녹색 원)
  if (!goal_pos.isNull()) {
    QPoint goal_gui = mapToGui(goal_pos);
    painter.setPen(Qt::green);
    painter.setBrush(Qt::green);
    painter.drawEllipse(goal_gui, 10, 10);
  }
}

// mousePressEvent 구현 추가
void MainWindow::mousePressEvent(QMouseEvent* event)
{
  if (event->button() == Qt::LeftButton) {
    QPointF map_pos = guiToMap(event->pos());

    // 클릭한 위치를 목표 위치로 설정
    goal_pos = map_pos;

    // 터틀봇을 해당 위치로 이동하도록 명령
    qnode->moveToGoal(map_pos.x(), map_pos.y());

    // GUI 업데이트
    update();
  }
}

void MainWindow::updateRobotPosition(double x, double y)
{
  current_pos = QPointF(x, y);
  update();
}

QPointF MainWindow::guiToMap(const QPoint& gui_point)
{
  // GUI 좌표를 맵 좌표로 변환
  double scale = 0.01;
  return QPointF((gui_point.x() - width()/2) * scale,
                (height()/2 - gui_point.y()) * scale);
}

QPoint MainWindow::mapToGui(const QPointF& map_point)
{
  // 맵 좌표를 GUI 좌표로 변환
  double scale = 100.0;
  return QPoint(width()/2 + map_point.x() * scale,
                height()/2 - map_point.y() * scale);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
  QMainWindow::closeEvent(event);
}

MainWindow::~MainWindow()
{
  delete ui;
}
