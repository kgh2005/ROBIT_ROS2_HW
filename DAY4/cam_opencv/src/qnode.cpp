#include "../include/cam_opencv/qnode.hpp"
#include <cv_bridge/cv_bridge.h> // OpenCV와 ROS 메시지 변환을 위한 헤더
#include <opencv2/imgproc/imgproc.hpp> // OpenCV 이미지 처리 헤더
#include <opencv2/highgui/highgui.hpp> // OpenCV GUI 헤더


// QNode constructor
QNode::QNode()
{
    // Initialize the ROS node with the name "parameter_sender_node"
    node = rclcpp::Node::make_shared("parameter_sender_node");

    // 이미지 주제 구독
    imageSubscription = node->create_subscription<sensor_msgs::msg::Image>(
        "/camera1/camera/image_raw",
        rclcpp::QoS(10),
        std::bind(&QNode::imageCallback, this, std::placeholders::_1));
}

// 이미지 콜백 함수
void QNode::imageCallback(const sensor_msgs::msg::Image::SharedPtr msg)
{
    // ROS 이미지 메시지를 OpenCV 이미지로 변환
    cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    QImage image = QImage((const unsigned char*)cv_ptr->image.data,
                          cv_ptr->image.cols,
                          cv_ptr->image.rows,
                          cv_ptr->image.step[0],
                          QImage::Format_RGB888).copy();

    emit imageReceived(image);  // 변환된 이미지를 시그널로 방출
}

// QNode destructor
QNode::~QNode()
{
    // No special shutdown logic needed
}

void QNode::start() {
    rclcpp::spin(node);  // ROS 이벤트 루프 시작
}

// Function to send parameters to the ROS node
void QNode::sendParameter(const std::string& paramName, const std::string& paramValue)
{
    // Set the parameter in the ROS node
    node->set_parameter(rclcpp::Parameter(paramName, paramValue));
}
