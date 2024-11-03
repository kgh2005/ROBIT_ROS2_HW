#include "../include/chatter_cli/listener.hpp"
#include <iostream>

Listener::Listener() : Node("listener")
{

  subscription_ = this->create_subscription<std_msgs::msg::String>(
    "chatter_cli", 10, std::bind(&Listener::messageCallback, this, std::placeholders::_1));

    // Int64 메시지 구독
  count_subscription_ = this->create_subscription<std_msgs::msg::Int64>(
    "chatter_count", 10, std::bind(&Listener::countCallback, this, std::placeholders::_1));
}


// String 메시지를 처리하는 콜백 함수
void Listener::messageCallback(const std_msgs::msg::String::SharedPtr msg)
{
    // String 메시지를 저장
    latest_message_ = msg->data;

    // 출력 형식 조정
    printMessages();
}

// Int64 메시지를 처리하는 콜백 함수
void Listener::countCallback(const std_msgs::msg::Int64::SharedPtr msg)
{
    // Int64 메시지를 저장
    latest_count_ = msg->data;

    // 출력 형식 조정
    printMessages();
}

// 메시지를 출력하는 함수
void Listener::printMessages()
{
    // String 메시지와 Int64 메시지가 모두 수신된 경우 출력
    if (!latest_message_.empty() && latest_count_ != 0) {
        RCLCPP_INFO(this->get_logger(), "Subscribed: \"%s\", \"%ld\"", latest_message_.c_str(), latest_count_);

        // 상태 초기화 (원하는 경우)
        latest_message_.clear();
        latest_count_ = 0;
    }
}

