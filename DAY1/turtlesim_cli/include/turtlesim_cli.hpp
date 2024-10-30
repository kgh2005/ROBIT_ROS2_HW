#ifndef TURTLESIM_CLI_NODE_HPP
#define TURTLESIM_CLI_NODE_HPP

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

class TurtlesimCli : public rclcpp::Node {
public:
    TurtlesimCli();
    void start_cli();

private:
    void control_mode();
    void set_background_color();
    void set_turtle_shape();
    void set_pen_mode();

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr control_publisher_;
    rclcpp::Client<turtlesim::srv::SetPen>::SharedPtr set_pen_client_;
    rclcpp::Client<std_srvs::srv::Empty>::SharedPtr clear_client_;
    rclcpp::Client<turtlesim::srv::Spawn>::SharedPtr spawn_client_;
    rclcpp::Client<turtlesim::srv::Kill>::SharedPtr kill_client_;
    std::vector<std::pair<std::string, std::string>> available_shapes_;
};

#endif // TURTLESIM_CLI_NODE_HPP
