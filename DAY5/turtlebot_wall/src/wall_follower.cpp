#include "turtlebot_wall/wall_follower.hpp"

WallFollower::WallFollower() : Node("wall_follower")
{
    this->declare_parameter<double>("left_distance_to_wall", 0.65);  // 왼쪽 벽과의 목표 거리 설정
    this->declare_parameter<double>("front_distance_to_wall", 3.1); // 전방 벽과의 목표 거리 설정
    subscription_ = this->create_subscription<sensor_msgs::msg::LaserScan>(
        "/scan", 10, std::bind(&WallFollower::scan_callback, this, std::placeholders::_1));
    publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
}

void WallFollower::scan_callback(const sensor_msgs::msg::LaserScan::SharedPtr msg)
{
    double left_distance_to_wall = this->get_parameter("left_distance_to_wall").as_double();   // 왼쪽 목표 거리 가져오기
    double front_distance_to_wall = this->get_parameter("front_distance_to_wall").as_double(); // 전방 목표 거리 가져오기

    int left_index = msg->ranges.size() / 4;  // 왼쪽 90도 방향의 인덱스
    int front_index = msg->ranges.size() / 2; // 전방 0도 방향의 인덱스

    double left_distance = msg->ranges[left_index];
    double front_distance = msg->ranges[front_index];

    RCLCPP_INFO(this->get_logger(), "Front distance: %f, Left distance: %f", front_distance, left_distance);

    geometry_msgs::msg::Twist cmd_vel;

    // 전방이 inf이거나 목표 거리보다 멀 때 오른쪽으로 회전
    if (std::isinf(front_distance) || front_distance > front_distance_to_wall)
    {
        cmd_vel.linear.x = 0.0; // 정지
        cmd_vel.angular.z = -0.5; // 오른쪽으로 회전
    }
    else // 벽을 따라가는 기본 동작
    {
        if (left_distance < left_distance_to_wall) // 왼쪽 벽과 너무 가까울 때
        {
            cmd_vel.linear.x = 0.0; // 정지
            cmd_vel.angular.z = -0.2; // 천천히 오른쪽 회전
        }
        else // 벽과의 적정 거리 유지
        {
            cmd_vel.linear.x = 0.1; // 전진
            cmd_vel.angular.z = 0.0; // 직진
        }
    }

    publisher_->publish(cmd_vel);
}
