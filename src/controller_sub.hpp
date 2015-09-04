
#ifndef CONTROLLER_SUB_HPP_
#define CONTROLLER_SUB_HPP_


//#include <ros/ros.h>
#include <rclcpp/rclcpp.hpp> //¿?
//#include <spider_msgs/LegsJointsState.h> 
//see http://design.ros2.org/articles/generated_interfaces_cpp.html
#include <spider_msgs/msg/legs_joints_state.hpp> 
#include <spider_msgs/msg/legs_joints_state__struct.hpp>
#include "PolstroSerialInterface.h"

#define N_CHANNELS 18
RMW_IMPORT rclcpp::Node::SharedPtr create_node();

class Controller {
	public:
		Controller();

	private:
		//CREATE NODE
		//ros::NodeHandle node;
		rclcpp::Node::SharedPtr node;
		
		std::string port_name;
		Polstro::SerialInterface* maestro;
		double joint_lower_limit, joint_upper_limit, limit_coef;
		const static unsigned int num_joints = 3;
		const static unsigned int num_legs = 6;

		int channels[N_CHANNELS];

		//CREATE SUBSCRIPTION
		//ros::Subscriber sub;
		rclcpp::subscription::SubscriptionBase::SharedPtr sub;
		//void chatterLegsState (const spider_msgs::LegsJointsStateConstPtr &legs_jnts);
		void chatterLegsState (const spider_msgs::msg::LegsJointsState::SharedPtr legs_jnts);
};

#endif /* CONTROLLER_SUB_HPP_ */
