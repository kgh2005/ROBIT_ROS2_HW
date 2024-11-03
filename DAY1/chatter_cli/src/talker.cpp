#include "../include/chatter_cli/talker.hpp"

Talker::Talker() : Node("talker")
{
  publisher_ = this->create_publisher<std_msgs::msg::String>("chatter_cli", 10);

  count_publisher_ = this->create_publisher<std_msgs::msg::Int64>("chatter_count", 10);
}

void Talker::publishMessage(const std::string &message)
{
  auto msg = std_msgs::msg::String();
  msg.data = message;
  publisher_->publish(msg);

   // 퍼블리시 횟수 증가
  publish_count_++;

  // Int64 메시지 생성 및 퍼블리시
  auto count_msg = std_msgs::msg::Int64();
  count_msg.data = publish_count_;
  RCLCPP_INFO(this->get_logger(), "Publishing : \"%s\", \"%ld\"", message.c_str(), publish_count_);
  count_publisher_->publish(count_msg);
}
