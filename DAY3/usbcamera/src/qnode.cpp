/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date August 2024
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include "../include/usbcamera/qnode.hpp"

QNode::QNode()
{
  int argc = 0;
  char** argv = NULL;
  rclcpp::init(argc, argv);
  node = rclcpp::Node::make_shared("image_recongnition");

  image_subscription = node->create_subscription<sensor_msgs::msg::Image>(
      "/camera1/camera/image_raw", 10,
      std::bind(&QNode::imageCallback, this, std::placeholders::_1)
      );

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

void QNode::imageCallback(const sensor_msgs::msg::Image::SharedPtr msg)
{
  try
  {
    // ROS 이미지 메시지를 OpenCV 이미지로 변환
    cv::Mat cv_image = cv_bridge::toCvCopy(msg, "bgr8")->image;
    // 데이터를 복사하여 QImage로 변환
    QImage qimage = QImage(cv_image.data, cv_image.cols, cv_image.rows, cv_image.step, QImage::Format_BGR888).copy();
    Q_EMIT imageReceived(qimage);  // QImage로 변환된 이미지를 시그널로 전송
  }
  catch (cv_bridge::Exception& e)
  {
    std::cerr << "cv_bridge exception: " << e.what() << std::endl;  // 콘솔에 예외 메시지 출력
  }
}

