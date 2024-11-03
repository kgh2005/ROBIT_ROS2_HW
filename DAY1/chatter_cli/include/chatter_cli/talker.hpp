#ifndef chatter_cli_TALKER_HPP_
#define chatter_cli_TALKER_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/
#ifndef Q_MOC_RUN
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include "std_msgs/msg/int64.hpp"
#endif

class Talker : public rclcpp::Node
{
public:
  Talker();
  void publishMessage(const std::string &message);  // 메시지 퍼블리시 메서드
  int64_t publish_count_;

private:
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;  // 퍼블리셔
  rclcpp::Publisher<std_msgs::msg::Int64>::SharedPtr count_publisher_;  // Int64 메시지 퍼블리셔


};

#endif
