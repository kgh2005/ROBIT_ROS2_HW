#ifndef QNODE_HPP
#define QNODE_HPP

#include <rclcpp/rclcpp.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <tf2/utils.h>
#include <QThread>
#include <QPoint>
#include <cmath>

class QNode : public QThread {
  Q_OBJECT
public:
  QNode();
  virtual ~QNode();
  void run() override;

private:
  std::shared_ptr<rclcpp::Node> node;
};

#endif
