#ifndef chatter_gui_LISTENER_HPP_
#define chatter_gui_LISTENER_HPP_

#include <rclcpp/rclcpp.hpp>
#include <QObject>
#include <QString>
#include "std_msgs/msg/string.hpp"

class Listener : public QObject, public rclcpp::Node
{
  Q_OBJECT
public:
  Listener();

signals:
  void messageReceived(const QString &message);

private:
  void messageCallback(const std_msgs::msg::String::SharedPtr msg);  // 수신 메시지 콜백 함수


  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

#endif /* chatter_gui_LISTENER_HPP_ */
