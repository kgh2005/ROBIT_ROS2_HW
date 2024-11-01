/**
 * @file /include/image_recongnition/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef image_recongnition_QNODE_HPP_
#define image_recongnition_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/
#ifndef Q_MOC_RUN
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <QImage>
#endif
#include <QThread>

/*****************************************************************************
** Class
*****************************************************************************/
class QNode : public QThread
{
  Q_OBJECT
public:
  QNode();
  ~QNode();

protected:
  void run();

private:
  std::shared_ptr<rclcpp::Node> node;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_subscription;

    void imageCallback(const sensor_msgs::msg::Image::SharedPtr msg);

Q_SIGNALS:
  void rosShutDown();
  void imageReceived(const QImage &image);  // 새로운 시그널 추가
};

#endif /* image_recongnition_QNODE_HPP_ */
