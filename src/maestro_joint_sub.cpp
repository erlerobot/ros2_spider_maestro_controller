

//#include <ros/ros.h>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/JointState.h>
#include "PolstroSerialInterface.h"

typedef boost::shared_ptr<sensor_msgs::JointState const> JointStateConstPtr;
Polstro::SerialInterface* maestro;

void chatterJointState (const JointStateConstPtr& state)
{
	float target_value;

	for (char i=0; i<3; i++){
		target_value = 6016 + (state->position[i] * 2486.624);
		maestro->setTarget(i, (int) target_value);
		ROS_INFO("Servo %d: [%d]", i, (int) target_value);
	}
}

int main(int argc, char **argv)
{
	std::string portName = "/dev/ttyACM0";
	unsigned int baudRate = 9600;
	maestro = Polstro::SerialInterface::createSerialInterface(portName, baudRate);

	//INITIALIZE
	//ros::init(argc, argv, "maestro_joint_sub");
	rclcpp::init(argc, argv, "maestro_joint_sub");
	
	//CREATE NODE
	//ros::NodeHandle node;
	rclcpp::node node;

	//SUBSCRIBE
	//ros::Subscriber sub = node.subscribe("joint_states", 100, chatterJointState);
	auto sub = node->create_subscription("joint_states", 100, chatterJointState);
	
	return 0;
}
