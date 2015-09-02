
#ifndef CONTROLLER_SUB_HPP_
#define CONTROLLER_SUB_HPP_


//#include <ros/ros.h>
#include <rclcpp/rclcpp.hpp> //¿?
#include <spider_msgs/LegsJointsState.h>
#include "PolstroSerialInterface.h"

#define N_CHANNELS 18

class Controller {
	public:
		Controller();

	private:
		//CREATE NODE
		//ros::NodeHandle node;
		auto node;

		std::string port_name;
		Polstro::SerialInterface* maestro;
		double joint_lower_limit, joint_upper_limit, limit_coef;
		const static unsigned int num_joints = 3;
		const static unsigned int num_legs = 6;

		int channels[N_CHANNELS];

		//CREATE SUBSCRIPTION
		//ros::Subscriber sub;
		auto sub;

		void chatterLegsState (const spider_msgs::LegsJointsStateConstPtr &legs_jnts);
};

#endif /* CONTROLLER_SUB_HPP_ */
