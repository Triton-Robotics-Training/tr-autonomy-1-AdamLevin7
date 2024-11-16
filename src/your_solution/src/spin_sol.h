#ifndef YOUR_SOLUTION_SRC_SPIN_SOL_H_
#define YOUR_SOLUTION_SRC_SPIN_SOL_H_

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
using ArrayMsg = std_msgs::msg::Float64MultiArray;

class SpinSolution : public rclcpp::Node {
 public:
  SpinSolution();
 private:
  void pos_callback(const ArrayMsg::SharedPtr msg);
  void vel_callback(const ArrayMsg::SharedPtr msg);
  void timer_callback();
  rclcpp::Subscription<ArrayMsg>::SharedPtr pos_subscription_;
  rclcpp::Subscription<ArrayMsg>::SharedPtr vel_subscription_;

  rclcpp::TimerBase::SharedPtr timer_;

  rclcpp::Publisher<ArrayMsg>::SharedPtr publisher_;
  ArrayMsg::SharedPtr pos;
  ArrayMsg::SharedPtr vel;

  rclcpp::Time lastTime;
  size_t count_;
};

#endif //YOUR_SOLUTION_SRC_SPIN_SOL_H_
