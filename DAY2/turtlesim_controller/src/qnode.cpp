#include "../include/turtlesim_controller/qnode.hpp"


QNode::QNode()
{
  int argc = 0;
  char** argv = NULL;
  rclcpp::init(argc, argv);
  node = rclcpp::Node::make_shared("qt_turtlesim_controller");

  // cmd_vel 퍼블리셔 생성
  velocity_publisher = node->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);

  // 배경색 변경을 위한 파라미터 클라이언트 초기화
  parameter_client_ = std::make_shared<rclcpp::AsyncParametersClient>(node, "turtlesim");
  // 배경 초기화를 위해 clear_client_ 생성
  clear_client_ = node->create_client<std_srvs::srv::Empty>("/clear");

  // cmd_vel 구독 관련 설정
  cmd_vel_subscription = node->create_subscription<geometry_msgs::msg::Twist>(
      "/turtle1/cmd_vel",
      10,
      [this](geometry_msgs::msg::Twist::SharedPtr msg) {
          emit cmdVelUpdated(msg->linear.x, msg->angular.z);
      }
  );

  // pen 설정을 위한 set_pen_client_ 생성
  set_pen_client_ = node->create_client<turtlesim::srv::SetPen>("/turtle1/set_pen");

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

// 거북이 이동 제어 메서드
void QNode::moveTurtle(double linear_x, double angular_z)
{
  auto twist_msg = geometry_msgs::msg::Twist();
  twist_msg.linear.x = linear_x;
  twist_msg.angular.z = angular_z;
  velocity_publisher->publish(twist_msg);

  emit cmdVelUpdated(twist_msg.linear.x, twist_msg.angular.z);
}

// 배경색 제어 메서드
void QNode::setBackgroundColor(int r, int g, int b) {
  if (parameter_client_->wait_for_service(std::chrono::seconds(5))) {
    parameter_client_->set_parameters({
      rclcpp::Parameter("background_r", std::clamp(r, 0, 255)),
      rclcpp::Parameter("background_g", std::clamp(g, 0, 255)),
      rclcpp::Parameter("background_b", std::clamp(b, 0, 255))
    });

    // 배경색 변경 후 화면 클리어
    auto request = std::make_shared<std_srvs::srv::Empty::Request>();
    clear_client_->async_send_request(request);
  }
}

// Pen 제어 메서드
void QNode::setPenStyle(int r, int g, int b, int width) {


  // 요청 객체 생성 -> Pen 설정을 위한 서비스 요청 객체를 생성함
  auto request = std::make_shared<turtlesim::srv::SetPen::Request>();

  request->r = std::max(0, std::min(r, 255));
  request->g = std::max(0, std::min(g, 255));
  request->b = std::max(0, std::min(b, 255));
  request->width = std::max(0, std::min(width, 10));

  auto future = set_pen_client_->async_send_request(request);
}

void QNode::setLine(int new_line) {
    line = new_line;
}

// 직선과 회전 동작을 위한 함수
void QNode::draw_line(int linear_x, double angular_z)
{
  auto twist_msg = geometry_msgs::msg::Twist();
  twist_msg.linear.x = linear_x * 0.5;
  twist_msg.angular.z = angular_z;
  velocity_publisher->publish(twist_msg);

  emit cmdVelUpdated(twist_msg.linear.x, twist_msg.angular.z);
}

// 사각형 그리기
void QNode::square()
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
void QNode::circle()
{
  for(int i = 0; i < 4; i++)
  {
    draw_line(line, 1.57); // 원을 그리기
    sleep(1); // 대기
  }
}

// 삼각형 그리기
void QNode::triangle()
{
  for (int i = 0; i < 3; i++)
  {
    draw_line(line, 0.0);  // 직진
    sleep(1); // 대기
    draw_line(0, 2.09); // 120도 회전 (2.09 라디안)
    sleep(1); // 대기
  }
}

// void QNode::setTurtleShape(const std::string& new_turtle_name, double x, double y, double theta) {
//     // 기존 터틀 제거
//     auto kill_request = std::make_shared<turtlesim::srv::Kill::Request>();
//     kill_request->name = "turtle1"; // 기존 터틀 이름

//     auto kill_future = set_pen_client_->async_send_request(kill_request);
//     if (rclcpp::spin_until_future_complete(node, kill_future) == rclcpp::FutureReturnCode::SUCCESS) {
//         std::cout << "터틀 " << "turtle1" << " 제거 완료." << std::endl;
//     } else {
//         std::cerr << "터틀 제거 요청 실패!" << std::endl;
//         return; // 제거에 실패하면 함수 종료
//     }

//     // 새로운 터틀 생성
//     auto spawn_request = std::make_shared<turtlesim::srv::Spawn::Request>();
//     spawn_request->name = new_turtle_name;
//     spawn_request->x = 5.5;
//     spawn_request->y = 5.5;

//     auto spawn_future = set_pen_client_->async_send_request(spawn_request);
//     if (rclcpp::spin_until_future_complete(node, spawn_future) == rclcpp::FutureReturnCode::SUCCESS) {
//         std::cout << "터틀 " << new_turtle_name << " 생성 완료." << std::endl;
//     } else {
//         std::cerr << "터틀 생성 요청 실패!" << std::endl;
//     }
// }


