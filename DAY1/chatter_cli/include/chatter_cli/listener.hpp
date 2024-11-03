#ifndef chatter_cli_LISTENER_HPP_
#define chatter_cli_LISTENER_HPP_

#include <rclcpp/rclcpp.hpp>
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int64.hpp"

class Listener : public rclcpp::Node
{
public:
  Listener();


private:
  // 수신된 메시지를 저장할 변수
    std::string latest_message_;
    int64_t latest_count_ = 0;
    // String 메시지 콜백 함수
    void messageCallback(const std_msgs::msg::String::SharedPtr msg);
    // Int64 메시지 콜백 함수
    void countCallback(const std_msgs::msg::Int64::SharedPtr msg);
    // 메시지를 출력하는 함수
    void printMessages();


  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
  // Int64 메시지 구독자
  rclcpp::Subscription<std_msgs::msg::Int64>::SharedPtr count_subscription_;
};

#endif
