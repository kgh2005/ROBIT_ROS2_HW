#include "rclcpp/rclcpp.hpp"
#include "turtlebot_wall/wall_follower.hpp"

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<WallFollower>());
    rclcpp::shutdown();
    return 0;
}
