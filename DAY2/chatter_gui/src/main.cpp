#include <QApplication>
#include <iostream>

#include "../include/chatter_gui/main_window.hpp"

int main(int argc, char* argv[])
{
  // Initialize ROS 2
  rclcpp::init(argc, argv);

  // Initialize Qt application
  QApplication app(argc, argv);
  MainWindow mainWindow;
  mainWindow.show();

  // Spin ROS node in a separate thread
  auto ros_executor = std::make_shared<rclcpp::executors::SingleThreadedExecutor>();
  ros_executor->add_node(mainWindow.talker_node);  // mainWindow 내의 talker_node를 ROS 스핀에 추가
  ros_executor->add_node(mainWindow.listener_node); // mainWindow 내의 listener_node를 ROS 스핀에 추가
  std::thread ros_thread([&]() { ros_executor->spin(); });

  // Execute Qt application
  int result = app.exec();

  // Clean up ROS
  rclcpp::shutdown();
  ros_thread.join();

  return result;
}