#include "cam_opencv/image.hpp"
#include "cam_opencv/main_window.hpp"  // 추가할 UI 클래스 헤더 파일
#include <QApplication>

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  QApplication app(argc, argv);

  // 첫 번째 창 생성 및 표시
  MainWindow mainWindow;
  mainWindow.show();

  // 두 번째 창 생성 및 표시
  ImageWindow imageWindow;
  imageWindow.show();

  imageWindow.qnode->start();

  rclcpp::shutdown();
  return app.exec();
}
