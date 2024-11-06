#include "../include/cam_params_pkg/parameter_img_node.hpp"

ParameterImgNode::ParameterImgNode(rclcpp::Node::SharedPtr node, QObject* parent)
  : QThread(parent), node_(node)
{
  // AsyncParametersClient 초기화
  parameters_client_ = std::make_shared<rclcpp::AsyncParametersClient>(node_, "image_processing_node");

  // 파라미터 변경 사항 발행 토픽 설정
  parameter_publisher_ = node_->create_publisher<std_msgs::msg::Int32>("/parameter_update", 10);
}

void ParameterImgNode::declareParameters()
{
    // HSV 파라미터
    node_->declare_parameter("h_lower", 0);
    node_->declare_parameter("h_upper", 179);
    node_->declare_parameter("s_lower", 0);
    node_->declare_parameter("s_upper", 255);
    node_->declare_parameter("v_lower", 0);
    node_->declare_parameter("v_upper", 255);
}
void ParameterImgNode::run()
{
  // 비동기 클라이언트 노드 실행
  rclcpp::spin(node_);
}

void ParameterImgNode::setParameter(const std::string &param_name, int value) {
  auto param = rclcpp::Parameter(param_name, value);
  parameters_client_->set_parameters({param});

  // 파라미터 변경 알림을 위해 메시지를 발행 (optional)
  auto msg = std_msgs::msg::Int32();
  msg.data = value;
  parameter_publisher_->publish(msg);
}




ParameterImgNode::~ParameterImgNode() {}
