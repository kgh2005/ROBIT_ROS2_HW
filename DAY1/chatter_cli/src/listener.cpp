#include "../include/chatter_cli/listener.hpp"
#include <iostream>

Listener::Listener() : Node("listener")
{

  subscription_ = this->create_subscription<std_msgs::msg::String>(
    "chatter", 10, std::bind(&Listener::messageCallback, this, std::placeholders::_1));
}


void Listener::messageCallback(const std_msgs::msg::String::SharedPtr msg)
{
  RCLCPP_INFO(this->get_logger(), "Received: '%s'", msg->data.c_str());
}

