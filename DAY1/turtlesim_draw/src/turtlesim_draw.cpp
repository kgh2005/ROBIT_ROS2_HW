#include "turtlesim_draw/turtlesim_draw.hpp"

TurtlesimDraw::TurtlesimDraw() : Node("turtlesim_draw") {
    // Publisher, Client 초기화
    control_publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
    set_pen_client_ = this->create_client<turtlesim::srv::SetPen>("/turtle1/set_pen");
}

void TurtlesimDraw::start_cli() {
    while (rclcpp::ok()) {
        std::cout << "\n1: 도형\n2: 크기\n3: pen 설정\n4: 종료\n";
        int mode_number;
        std::cin >> mode_number;

        switch (mode_number) {
            case 1:
              draw_shape();
              break;
            case 2:
              set_size();
              break;
            case 3:
              set_pen_mode();
              break;
            case 4:
                return;
            default:
              std::cout << "Error\n";
              break;
        }
    }
}

// 직선과 회전 동작을 위한 함수
void TurtlesimDraw::draw_line(int linear_x, double angular_z)
{
  geometry_msgs::msg::Twist twist;
  twist.linear.x = linear_x * 0.5;
  twist.angular.z = angular_z;
  control_publisher_->publish(twist);
}


// 사각형 그리기
void TurtlesimDraw::square()
{
  for (int i = 0; i < 4; i++)
  {
    draw_line(line, 0);  // 직진
    sleep(1); // 대기
    draw_line(0, 1.57); // 90도 회전 (1.57 라디안)
    sleep(1); // 대기
  }
}

// 원 그리기
void TurtlesimDraw::circle()
{
  for(int i = 0; i < 4; i++)
  {
    draw_line(line, 1.57); // 원을 그리기
    sleep(1); // 대기
  }
}

// 삼각형 그리기
void TurtlesimDraw::triangle()
{
  for (int i = 0; i < 3; i++)
  {
    draw_line(line, 0.0);  // 직진
    sleep(1); // 대기
    draw_line(0, 2.09); // 120도 회전 (2.09 라디안)
    sleep(1); // 대기
  }
}

void TurtlesimDraw::draw_shape()
{
  int shape_number;
  std::cout << "1. 사각형\n2. 원\n3. 삼각형\n";
  std::cin >> shape_number;

  switch (shape_number)
  {
  case 1:
    square();
    break;
  case 2:
    circle();
    break;
  case 3:
    triangle();
    break;
  default:
    std::cout << "Error\n";
    break;
  }
}

void TurtlesimDraw::set_size()
{
  while (1)
  {
    std::cout << "1~10 사이로 입력\n";
    std::cin >> line;

    if (line <= 10) {
      break;
    }
  }
}


void TurtlesimDraw::set_pen_mode()
{
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
