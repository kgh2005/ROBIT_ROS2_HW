#include "rclcpp/rclcpp.hpp"
#include "turtlesim_draw/turtlesim_draw.hpp"

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtlesimDraw>();
    node->start_cli();
    rclcpp::shutdown();
    return 0;
}
