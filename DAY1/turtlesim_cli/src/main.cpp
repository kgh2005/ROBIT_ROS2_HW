#include "rclcpp/rclcpp.hpp"
#include "turtlesim_cli.hpp"

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtlesimCli>();
    node->start_cli();
    rclcpp::shutdown();
    return 0;
}
