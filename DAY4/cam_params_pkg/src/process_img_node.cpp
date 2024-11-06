#include "../include/cam_params_pkg/process_img_node.hpp"

ProcessImgNode::ProcessImgNode(rclcpp::Node::SharedPtr node, QObject* parent)
  : QThread(parent), node_(node)
{


  // 이미지 토픽 구독 설정
  image_subscription_ = node_->create_subscription<sensor_msgs::msg::Image>(
      "/camera1/camera/image_raw", 10, std::bind(&ProcessImgNode::imageCallback, this, std::placeholders::_1));

  // // 파라미터 업데이트 토픽 구독
  // parameter_subscription_ = node_->create_subscription<std_msgs::msg::Int32>(
  //   "/parameter_update", 10, std::bind(&ProcessImgNode::updateParameter, this, std::placeholders::_1));

}

void ProcessImgNode::run()
{
  rclcpp::spin(node_);
}

// void ProcessImgNode::updateHSVParameters(int hueLow, int hueUpp, int satrLow, int satrUpp, int valLow, int valUpp) {
//     RCLCPP_INFO(node_->get_logger(), "Updating HSV Parameters: %d, %d, %d, %d, %d, %d", hueLow, hueUpp, satrLow, satrUpp, valLow, valUpp);
//     hueLow_ = hueLow;
//     hueUpp_ = hueUpp;
//     satrLow_ = satrLow;
//     satrUpp_ = satrUpp;
//     valLow_ = valLow;
//     valUpp_ = valUpp;
// }

void ProcessImgNode::imageCallback(const sensor_msgs::msg::Image::SharedPtr msg) {
    try {

      // 파라미터 값을 읽어옴
        node_->get_parameter("hueLow", hueLow_);
        node_->get_parameter("hueUpp", hueUpp_);
        node_->get_parameter("satrLow", satrLow_);
        node_->get_parameter("satrUpp", satrUpp_);
        node_->get_parameter("valLow", valLow_);
        node_->get_parameter("valUpp", valUpp_);


        // shared_ptr로 cv::Mat을 관리하여 메모리 유효성 보장
        auto frame_ptr = std::make_shared<cv::Mat>(cv_bridge::toCvCopy(msg, "bgr8")->image);

        // QImage로 원본 이미지 송출
        QImage qImageOriginal(frame_ptr->data, frame_ptr->cols, frame_ptr->rows, frame_ptr->step, QImage::Format_BGR888);
        emit originalImageProcessed(qImageOriginal.copy());  // 원본 이미지 송출

        // 기본 이진화 처리
        cv::Mat gray, binary;
        cv::cvtColor(*frame_ptr, gray, cv::COLOR_BGR2GRAY);
        cv::threshold(gray, binary, 128, 255, cv::THRESH_BINARY);  // 기본 이진화

        // frame_2에 이진화된 이미지 송출
        QImage qImageBinary(binary.data, binary.cols, binary.rows, binary.step, QImage::Format_Grayscale8);
        emit binaryImageProcessed(qImageBinary.copy());  // frame_2 송출

        // HSV 변환 및 이미지 필터링
        cv::Mat hsvImage;
        cv::cvtColor(*frame_ptr, hsvImage, cv::COLOR_BGR2HSV);

        // 마스크 이미지 생성
        cv::Mat hsvMask;
        cv::inRange(hsvImage,
                    cv::Scalar(hueLow_, satrLow_, valLow_),
                    cv::Scalar(hueUpp_, satrUpp_, valUpp_),
                    // cv::Scalar(10, 100, 100),
                    // cv::Scalar(25, 255, 255),
                    hsvMask);
        RCLCPP_INFO(node_->get_logger(), "Updating HSV Parameters: %d, %d, %d, %d, %d, %d", hueLow_, hueUpp_, satrLow_, satrUpp_, valLow_, valUpp_);
        // 필터링된 이미지 생성
        cv::Mat filteredImage;
        frame_ptr->copyTo(filteredImage, hsvMask);
        // frame_3에 HSV 기반 필터링된 이미지 송출
        QImage qImageFiltered(filteredImage.data, filteredImage.cols, filteredImage.rows,
                              filteredImage.step, QImage::Format_BGR888);
        emit parameterBinaryImageProcessed(qImageFiltered.copy());

        RCLCPP_INFO(node_->get_logger(), "Original and processed images emitted");
    }
    catch (cv_bridge::Exception &e) {
        RCLCPP_ERROR(node_->get_logger(), "Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
}


ProcessImgNode::~ProcessImgNode() {}
