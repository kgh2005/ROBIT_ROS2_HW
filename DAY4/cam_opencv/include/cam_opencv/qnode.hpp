#ifndef CAM_OPENCV_QNODE_H
#define CAM_OPENCV_QNODE_H

#include <QObject>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <QImage>


class QNode : public QObject
{
    Q_OBJECT

public:
    QNode();
    ~QNode();
    void start();

    void sendParameter(const std::string& paramName, const std::string& paramValue);

signals:
    void imageReceived(const QImage& image);

private:
    rclcpp::Node::SharedPtr node;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr imageSubscription;

    void imageCallback(const sensor_msgs::msg::Image::SharedPtr msg);
};

#endif  // CAM_OPENCV_QNODE_H
