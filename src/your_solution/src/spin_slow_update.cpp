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
  
  /*vel_subscription_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
    "measuredvel", 10, std::bind(&SlowSolution::vel_callback, this, std::placeholders::_2));
  */
  publisher_ = this->create_publisher<ArrayMsg>("predictedpos", 10);
  /*timer_ = this->create_wall_timer(
  500ms, std::bind(&SlowSolution::timer_callback, this));
  
  */
  
}
  void SlowSolution::pos_callback(const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
    RCLCPP_INFO(this->get_logger(), "Received position: [%f, %f]", msg->data[0], msg->data[1]);
    auto predictedMsg = ArrayMsg();
    predictedMsg.data = msg->data;
    publisher_ ->publish(predictedMsg);
  /*void SlowSolution::vel_callback(const ArrayMsg::SharedPtr msg) {
  RCLCPP_INFO(this->get_logger(), "Received velocity: [%f, %f]", msg->data[0], msg->data[1]);
} */
}