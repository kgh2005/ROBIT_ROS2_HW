#include "../include/chatter_gui/main_window.hpp"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindowDesign)
{
  ui->setupUi(this);

  // 창 아이콘 설정
  QIcon icon("://ros-icon.png");
  this->setWindowIcon(icon);

  // talker_node와 listener_node 초기화
  talker_node = std::make_shared<Talker>();
  listener_node = std::make_shared<Listener>();

  // 퍼블리시 버튼 클릭 시 on_publishButton_clicked 호출
  QObject::connect(ui->btn_send, &QPushButton::clicked, this, &MainWindow::on_btn_send_clicked);
  QObject::connect(listener_node.get(), &Listener::messageReceived, this, &MainWindow::displayMessage);

}

void MainWindow::on_btn_send_clicked()
{
  // QLineEdit (talker)에서 텍스트를 가져와 퍼블리시
  QString message = ui->lineEdit->text();
  talker_node->publishMessage(message.toStdString());
}
void MainWindow::displayMessage(const QString &message)
{
  ui->label->setText(message);  // QLabel에 메시지 표시
}


void MainWindow::closeEvent(QCloseEvent* event)
{
  QMainWindow::closeEvent(event);
}

MainWindow::~MainWindow()
{
  delete ui;
}
