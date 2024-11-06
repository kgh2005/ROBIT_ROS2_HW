#ifndef CAM_PARAMS_PKG_PARAMETER_IMG_NODE_H
#define CAM_PARAMS_PKG_PARAMETER_IMG_NODE_H

#include <QThread>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/parameter_client.hpp>
#include <std_msgs/msg/string.hpp>
#include "std_msgs/msg/int32.hpp"
#include "cam_params_pkg/process_img_node.hpp"

class ProcessImgNode;

class ParameterImgNode : public QThread
{
  Q_OBJECT

public:
  explicit ParameterImgNode(rclcpp::Node::SharedPtr node, QObject* parent = nullptr);
  ~ParameterImgNode();

  // 파라미터 설정 메서드 추가
  void setParameter(const std::string &param_name, int value);



protected:
  void run() override;

private:
  rclcpp::Node::SharedPtr node_;
  std::shared_ptr<rclcpp::AsyncParametersClient> parameters_client_;

  rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr parameter_publisher_;
};

#endif  // CAM_PARAMS_PKG_PARAMETER_IMG_NODE_H
