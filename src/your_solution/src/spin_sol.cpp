#include "spin_sol.h"

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SpinSolution>());
  rclcpp::shutdown();
  return 0;
}

//your code here

SpinSolution::SpinSolution() : Node("spinsolution") {
  RCLCPP_INFO(this->get_logger(), "Remove this statement from spin_sol.cpp");
  // your code here
  pos_subscription_ = this->create_subscription<ArrayMsg>(
    "measuredpos", 10, std::bind(&SpinSolution::pos_callback, this, std::placeholders::_1));
  
  vel_subscription_ = this->create_subscription<ArrayMsg>(
    "measuredvel", 10, std::bind(&SpinSolution::vel_callback, this, std::placeholders::_1));
  
  publisher_ = this->create_publisher<ArrayMsg>("predictedpos", 10);
  
  timer_ = this->create_wall_timer(
    std::chrono::milliseconds(50), 
    std::bind(&SpinSolution::timer_callback, this));
  
  
  
}
  void SpinSolution::pos_callback(const ArrayMsg::SharedPtr msg) {
    RCLCPP_INFO(this->get_logger(), "Received position: [%f, %f]", msg->data[0], msg->data[1]);
    pos = msg;
    lastTime = this->now();
  }
  void SpinSolution::vel_callback(const ArrayMsg::SharedPtr msg) {
    RCLCPP_INFO(this->get_logger(), "Received velocity: [%f, %f]", msg->data[0], msg->data[1]);
    vel = msg;
  }
  void SpinSolution::timer_callback(){
    if(pos == nullptr || vel == nullptr){
      return;
    }
    auto predictedMsg = ArrayMsg();
    predictedMsg.data.resize(2);

    rclcpp::Time currTime = this->now();
    double delta_t = currTime.seconds() - lastTime.seconds();

    predictedMsg.data[0] = pos->data[0] + delta_t * vel->data[0];
    predictedMsg.data[1] = pos->data[1] + delta_t * vel->data[1];
    
    publisher_ ->publish(predictedMsg);
  }
  
