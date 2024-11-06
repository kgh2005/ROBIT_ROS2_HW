#ifndef turtlebot_move_QNODE_HPP_
#define turtlebot_move_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/
#ifndef Q_MOC_RUN
#include <rclcpp/rclcpp.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <QPoint>
#endif
#include <QThread>

/*****************************************************************************
** Class
*****************************************************************************/
class QNode : public QThread
{
  Q_OBJECT
public:
  QNode();
  ~QNode();
  void run() override;
  void moveToGoal(double x, double y);


private:
  std::shared_ptr<rclcpp::Node> node;
  rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr goal_pub;
  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_sub;

  void odomCallback(const nav_msgs::msg::Odometry::SharedPtr msg);

Q_SIGNALS:
  void rosShutDown();
  void updateCurrentPos(double x, double y);
};

#endif /* turtlebot_move_QNODE_HPP_ */
