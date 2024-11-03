#include "../include/chatter_cli/listener.hpp"
#include "../include/chatter_cli/talker.hpp"
#include <QApplication>
#include <iostream>
#include <string>
#include <thread>

int main(int argc, char* argv[])
{
  //초기화
  rclcpp::init(argc, argv);

  // 노드 생성
  auto talker = std::make_shared<Talker>();
  auto listener = std::make_shared<Listener>();

  std::thread listener_thread([&]() {
    rclcpp::spin(listener);
  });

  std::string input;

  // 메시지 퍼블리시
  while (rclcpp::ok()) {
    std::cout << "input: " << std::flush;
    std::getline(std::cin, input);

    // Talker에 메시지 퍼블리시
    talker->publishMessage(input);

    rclcpp::sleep_for(std::chrono::milliseconds(100));
  }

  rclcpp::shutdown();
  listener_thread.join();

  return 0;
}
