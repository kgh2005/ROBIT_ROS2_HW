#ifndef qt_turtlesim_controller_QNODE_HPP_
#define qt_turtlesim_controller_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/
#ifndef Q_MOC_RUN
#include <rclcpp/rclcpp.hpp>
#endif
#include <QThread>
#include "geometry_msgs/msg/twist.hpp"
#include "std_srvs/srv/empty.hpp"
#include "turtlesim/srv/set_pen.hpp" // pen 설정을 위한 서비스 헤더 파일 추가(1일차 과제 응용)
#include <turtlesim/srv/spawn.hpp>
#include <turtlesim/srv/kill.hpp>
#include <rclcpp/parameter_client.hpp>
#include <memory>

/*****************************************************************************
** Class
*****************************************************************************/
class QNode : public QThread
{
  Q_OBJECT
public:
  QNode();
  ~QNode();
  // 거북이 제어를 위한 메서드
  void moveTurtle(double linear_x, double angular_z);
  // 거북이 배경색 제어를 위한 메서드
  void setBackgroundColor(int r, int g, int b);
  void setPenStyle(int r, int g, int b, int width);

  void draw_line(int linear, double angular);
  void square();
  void circle();
  void triangle();
  void setLine(int new_line);

  //void setTurtleShape(const std::string& turtle_name);


protected:
  void run();

private:
  int line = 1;
  std::shared_ptr<rclcpp::Node> node;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr velocity_publisher;

  rclcpp::Client<std_srvs::srv::Empty>::SharedPtr clear_client_;
  // 파라미터 클라이언트
  std::shared_ptr<rclcpp::AsyncParametersClient> parameter_client_;

  rclcpp::Client<turtlesim::srv::Spawn>::SharedPtr spawn_client_;
  rclcpp::Client<turtlesim::srv::Kill>::SharedPtr kill_client_;

  // cmd_vel 구독
  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_subscription;

  // Pen 설정
  rclcpp::Client<turtlesim::srv::SetPen>::SharedPtr set_pen_client_;

Q_SIGNALS:
  void rosShutDown();
  void cmdVelUpdated(double linear_x, double angular_z);
};


#endif /* qt_turtlesim_controller_QNODE_HPP_ */
