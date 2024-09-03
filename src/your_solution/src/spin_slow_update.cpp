#include "spin_slow_update.h"

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SlowSolution>());
  rclcpp::shutdown();
  return 0;
}

SlowSolution::SlowSolution() : Node("slowsolution") {
  RCLCPP_INFO(this->get_logger(), "Remove this statement from spin_slow_update.cpp");
  // your code here
}

// your code here