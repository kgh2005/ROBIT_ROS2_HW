#ifndef CAM_PARAMS_PKG_PROCESS_IMG_NODE_H
#define CAM_PARAMS_PKG_PROCESS_IMG_NODE_H

#include <QThread>
#include <QImage>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include "std_msgs/msg/int32.hpp"
#include "cam_params_pkg/parameter_img_node.hpp"
#include "std_msgs/msg/int32_multi_array.hpp"


class ProcessImgNode : public QThread
{
  Q_OBJECT

public:
  explicit ProcessImgNode(rclcpp::Node::SharedPtr node, QObject* parent = nullptr);
  //void updateHSVParameters(int hueLow, int hueUpp, int satrLow, int satrUpp, int valLow, int valUpp);
  //void updateParameter(const std_msgs::msg::Int32MultiArray::SharedPtr msg);
  ~ProcessImgNode();

protected:
  void run() override;

private:
  rclcpp::Node::SharedPtr node_;
  //rclcpp::Subscription<std_msgs::msg::Int32MultiArray>::SharedPtr parameter_subscription_;
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_subscription_;

  // HSV 파라미터
  int hueLow_ = 0;
  int hueUpp_ = 180;
  int satrLow_ = 0;
  int satrUpp_ = 255;
  int valLow_ = 0;
  int valUpp_ = 255;

  void imageCallback(const sensor_msgs::msg::Image::SharedPtr msg);


  signals:
  void imageProcessed(const QImage& image);       // 원본 이미지 시그널
  void originalImageProcessed(const QImage& image); // 원본 이미지 시그널 추가
  void binaryImageProcessed(const QImage& image);
  void parameterBinaryImageProcessed(const QImage& image);
};

#endif  // CAM_PARAMS_PKG_PROCESS_IMG_NODE_H
