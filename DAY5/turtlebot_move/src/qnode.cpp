#include "../include/turtlebot_move/qnode.hpp"

QNode::QNode()
{
  int argc = 0;
  char** argv = NULL;
  rclcpp::init(argc, argv);
  node = rclcpp::Node::make_shared("turtlebot_move");

  // Publisher와 Subscriber 설정
  goal_pub = node->create_publisher<geometry_msgs::msg::PoseStamped>("/goal_pose", 10);
  odom_sub = node->create_subscription<nav_msgs::msg::Odometry>(
    "/odom", 10,
    std::bind(&QNode::odomCallback, this, std::placeholders::_1));


  this->start();
}

QNode::~QNode()
{
  if (rclcpp::ok())
  {
    rclcpp::shutdown();
  }
}

void QNode::run()
{
  rclcpp::WallRate loop_rate(20);
  while (rclcpp::ok())
  {
    rclcpp::spin_some(node);
    loop_rate.sleep();
  }
  rclcpp::shutdown();
  Q_EMIT rosShutDown();
}

void QNode::odomCallback(const nav_msgs::msg::Odometry::SharedPtr msg)
{
  Q_EMIT updateCurrentPos(msg->pose.pose.position.x, msg->pose.pose.position.y);
}

void QNode::moveToGoal(double x, double y)
{
  auto goal_msg = std::make_unique<geometry_msgs::msg::PoseStamped>();
  goal_msg->header.stamp = node->now();
  goal_msg->header.frame_id = "map";

  goal_msg->pose.position.x = x;
  goal_msg->pose.position.y = y;
  goal_msg->pose.orientation.w = 1.0;

  goal_pub->publish(std::move(goal_msg));
}
