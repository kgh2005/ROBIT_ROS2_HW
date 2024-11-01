#include "../include/chatter_cli/listener.hpp"
#include "../include/chatter_cli/talker.hpp"
#include <QApplication>
#include <iostream>
#include <string>
#include <thread>

int main(int argc, char* argv[])
{
  // Initialize ROS 2
  rclcpp::init(argc, argv);

  auto talker = std::make_shared<Talker>();
  auto listener = std::make_shared<Listener>();

  // Spin listener in a separate thread
  std::thread listener_thread([&]() {
    rclcpp::spin(listener);
  });

  std::string input;
  while (rclcpp::ok()) {
    std::cout << "input: " << std::flush;
    std::getline(std::cin, input);

    talker->publishMessage(input);

    rclcpp::sleep_for(std::chrono::milliseconds(100));
  }

  rclcpp::shutdown();
  listener_thread.join();

  return 0;
}
