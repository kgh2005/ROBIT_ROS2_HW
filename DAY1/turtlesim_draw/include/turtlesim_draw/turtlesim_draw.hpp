#ifndef TURTLESIM_DRAW_NODE_HPP
#define TURTLESIM_DRAW_NODE_HPP

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/parameter_client.hpp"
#include "turtlesim/srv/set_pen.hpp"
#include "std_srvs/srv/empty.hpp"
#include "turtlesim/srv/spawn.hpp"
#include "turtlesim/srv/kill.hpp"

#include <iostream>
#include <vector>
#include <string>

class TurtlesimDraw : public rclcpp::Node {
public:
    TurtlesimDraw();
    void start_cli();

    int line = 1;

private:
    void draw_shape();
    void set_size();
    void set_pen_mode();

    void draw_line(int linear_x, double angular_z);
    void square();
    void circle();
    void triangle();

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr control_publisher_;
    rclcpp::Client<turtlesim::srv::SetPen>::SharedPtr set_pen_client_;
};

#endif // TURTLESIM_DRAW_NODE_HPP
