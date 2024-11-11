#include "spin_slow_update.h"

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SlowSolution>());
  rclcpp::shutdown();
  return 0;
}

SlowSolution::SlowSolution() : Node("slowsolution") {
  pos_subscription_ = this->create_subscription<ArrayMsg>(
    "measuredpos", 10, std::bind(&SlowSolution::pos_callback, this, std::placeholders::_1));
  
  vel_subscription_ = this->create_subscription<ArrayMsg>(
    "measuredvel", 10, std::bind(&SlowSolution::vel_callback, this, std::placeholders::_1));
  publisher_ = this->create_publisher<ArrayMsg::SharedPtr::String>("predictedpos", 10);
  timer_ = this->create_wall_timer(
  500ms, std::bind(&MinimalPublisher::timer_callback, this));
  
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<ArrayMsg::SharedPtr::String>::SharedPtr publisher_;
}
njjnknjkn

void SlowSolution::pos_callback(const ArrayMsg::SharedPtr msg) {
  RCLCPP_INFO(this->get_logger(), "Received position: [%f, %f]", msg->data[0], msg->data[1]);
}

void SlowSolution::vel_callback(const ArrayMsg::SharedPtr msg) {
  RCLCPP_INFO(this->get_logger(), "Received velocity: [%f, %f]", msg->data[0], msg->data[1]);
}