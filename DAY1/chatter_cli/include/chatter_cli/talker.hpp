#ifndef chatter_gui_TALKER_HPP_
#define chatter_gui_TALKER_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/
#ifndef Q_MOC_RUN
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#endif

class Talker : public rclcpp::Node
{
public:
  Talker();
  void publishMessage(const std::string &message);  // 메시지 퍼블리시 메서드

private:
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;  // 퍼블리셔


};

#endif /* chatter_gui_TALKER_HPP_ */
