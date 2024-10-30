#include "turtlesim_cli.hpp"

TurtlesimCli::TurtlesimCli() : Node("turtlesim_cli") {
    // Publisher, Client 초기화
    control_publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
    set_pen_client_ = this->create_client<turtlesim::srv::SetPen>("/turtle1/set_pen");
    clear_client_ = this->create_client<std_srvs::srv::Empty>("/clear");
    spawn_client_ = this->create_client<turtlesim::srv::Spawn>("/spawn");
    kill_client_ = this->create_client<turtlesim::srv::Kill>("/kill");

    this->declare_parameter("background_r", 0);
    this->declare_parameter("background_g", 0);
    this->declare_parameter("background_b", 0);
}

void TurtlesimCli::start_cli() {
    while (rclcpp::ok()) {
        std::cout << "\n1: 조종\n2: 배경색 설정\n3: 거북이 설정\n4: Pen 설정\n5: 종료\n";
        int mode_number;
        std::cin >> mode_number;

        switch (mode_number) {
            case 1: control_mode();
                break;
            case 2: set_background_color();
                break;
            case 3: set_turtle_shape();
                break;
            case 4: set_pen_mode();
                break;
            case 5:
                return;
            default: std::cout << "Error\n";
                break;
        }
    }
}

// 조종모드
void TurtlesimCli::control_mode() {
    std::cout << "w,a,s,d / q 입력시 종료\n";
    geometry_msgs::msg::Twist twist;
    char input;
    while ((std::cin >> input) && (input != 'q')) {
        twist.linear.x = 0.0;
        twist.angular.z = 0.0;

        switch (input) {
            case 'w':
                twist.linear.x = 1.0;  // 앞
                break;
            case 's':
                twist.linear.x = -1.0; // 뒤
                break;
            case 'a':
                twist.angular.z = 1.0;  // 왼
                break;
            case 'd':
                twist.angular.z = -1.0; // 오
                break;
        }

        control_publisher_->publish(twist);
    }
}

void TurtlesimCli::set_background_color() {
    std::string color_input;
    std::cout << "r,g,b : ";
    std::cin >> color_input;

    int r = 0;
    int g = 0;
    int b = 0;

    if (color_input == "r") {
        r = 255;
    }
    else if (color_input == "g") {
        g = 255;
    }
    else if (color_input == "b") {
        b = 255;
    }


    auto parameter_client = std::make_shared<rclcpp::AsyncParametersClient>(this->shared_from_this(), "turtlesim");
    if (parameter_client->wait_for_service(std::chrono::seconds(5))) {
        parameter_client->set_parameters({
            rclcpp::Parameter("background_r", r),
            rclcpp::Parameter("background_g", g),
            rclcpp::Parameter("background_b", b)
        });

        auto request = std::make_shared<std_srvs::srv::Empty::Request>();
        auto result = clear_client_->async_send_request(request);

        if (rclcpp::spin_until_future_complete(this->shared_from_this(), result) == rclcpp::FutureReturnCode::SUCCESS) {
            std::cout << "배경 색 변경\n";
        }
    }
}

void TurtlesimCli::set_turtle_shape() {
    std::cout << "\n1: ardent\n2: bouncy\n3: crystal\n4: dashing\n";

    int choice;
    std::cin >> choice;

    std::string turtle_name;
    switch(choice) {
        case 1: turtle_name = "ardent"; break;
        case 2: turtle_name = "bouncy"; break;
        case 3: turtle_name = "crystal"; break;
        case 4: turtle_name = "dashing"; break;
    }

    // 기존 거북이 삭제
    auto kill_request = std::make_shared<turtlesim::srv::Kill::Request>();

    if (kill_client_->wait_for_service(std::chrono::seconds(1))) {
        auto kill_result = kill_client_->async_send_request(kill_request);

        if (rclcpp::spin_until_future_complete(this->shared_from_this(), kill_result) == rclcpp::FutureReturnCode::SUCCESS)
            std::cout << "delete\n";
    }


    auto parameter_client = std::make_shared<rclcpp::AsyncParametersClient>(
        this->shared_from_this(),
        "turtlesim"
    );

    if (parameter_client->wait_for_service(std::chrono::seconds(5))) {
        auto set_param_result = parameter_client->set_parameters({rclcpp::Parameter("turtle_shape", turtle_name)});


        if (rclcpp::spin_until_future_complete(this->shared_from_this(), set_param_result) == rclcpp::FutureReturnCode::SUCCESS)
            std::cout << "설정.\n";
    }

    // 새로운 거북이 생성
    auto spawn_request = std::make_shared<turtlesim::srv::Spawn::Request>();
    spawn_request->x = 5.5;        // 화면 중앙 X 좌표
    spawn_request->y = 5.5;        // 화면 중앙 Y 좌표
    spawn_request->theta = 0.0;    // 초기 방향

    if (spawn_client_->wait_for_service(std::chrono::seconds(1))) {
        auto spawn_result = spawn_client_->async_send_request(spawn_request);
        if (rclcpp::spin_until_future_complete(this->shared_from_this(), spawn_result) == rclcpp::FutureReturnCode::SUCCESS)
            std::cout << "생성.\n";
    }
}

void TurtlesimCli::set_pen_mode() {
    auto request = std::make_shared<turtlesim::srv::SetPen::Request>();
    std::string color_input;
    int width;

    std::cout << "r,g,b : ";
    std::cin >> color_input;

    if (color_input == "r") {
        request->r = 255;
        request->g = 0;
        request->b = 0;
    }
    else if (color_input == "g") {
        request->r = 0;
        request->g = 255;
        request->b = 0;
    }
    else if (color_input == "b") {
        request->r = 0;
        request->g = 0;
        request->b = 255;
    }

    std::cout << "0~10 between: ";
    std::cin >> width;

    request->width = static_cast<int>(width);
    request->off = 0;

    set_pen_client_->async_send_request(request);
    std::cout << "설정.\n";
}
