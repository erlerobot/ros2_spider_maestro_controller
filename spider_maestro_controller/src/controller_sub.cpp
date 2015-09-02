#include "controller_sub.hpp"

	const int rotation_direction[18] = 	{1,-1, 1,
								 	 	 1,-1, 1,
								 	 	 1,-1, 1,
								 	 	 1,	1,-1,
								 	 	 1,	1,-1,
								 	 	 1,	1,-1};


Controller::Controller(){

  // Get Min and Max joints limits
	node.param("joint_lower_limit", joint_lower_limit, -1.570796327);
	node.param("joint_upper_limit", joint_upper_limit, 1.570796327);
	limit_coef = 127 / ((joint_upper_limit - joint_lower_limit) / 2);

	// Get the interface to connect Erle-Brain with Mini-Maestro
	node.param("port_name", port_name, std::string("/dev/ttyACM0"));

	//LEG 1
	node.param("leg1_1", channels[0], 0);
	node.param("leg1_2", channels[1], 1);
	node.param("leg1_3", channels[2], 2);

	//LEG 2
	node.param("leg2_1", channels[3], 3);
	node.param("leg2_2", channels[4], 4);
	node.param("leg2_3", channels[5], 5);

	//LEG 3
	node.param("leg3_1", channels[6], 6);
	node.param("leg3_2", channels[7], 7);
	node.param("leg3_3", channels[8], 8);

	//LEG 4
	node.param("leg4_1", channels[9], 9);
	node.param("leg4_2", channels[10], 10);
	node.param("leg4_3", channels[11], 11);

	//LEG 5
	node.param("leg5_1", channels[12], 12);
	node.param("leg5_2", channels[13], 13);
	node.param("leg5_3", channels[14], 14);

	//LEG 6
	node.param("leg6_1", channels[15], 15);
	node.param("leg6_2", channels[16], 16);
	node.param("leg6_3", channels[17], 17);

	maestro = Polstro::SerialInterface::createSerialInterface(port_name, 115200);
	auto sub = node->create_subscription("joints_to_controller", 1, &Controller::chatterLegsState, this);
	ROS_INFO("Maestro servo controller is ready...");
}

void Controller::chatterLegsState (const spider_msgs::LegsJointsStateConstPtr &legs_jnts){

	float target_value;
	int s_num;

	for (int i=0; i<num_legs; i++){
		for (int j=0; j<num_joints; j++){
			s_num = i*3+j;
			target_value = 127 + rotation_direction[s_num] * legs_jnts->joints_state[i].joint[j] * limit_coef;
//			target_value = (neutral_ms + rotation_direction[s_num] * (legs_jnts->joints_state[i].joint[j] * coef_ms)) * 4;

			maestro->setTargetMSS(channels[s_num], (unsigned char) target_value);
		}
	}
}

int main(int argc, char **argv)
{
	//INITIALIZE
	//ros::init(argc, argv, "controller_sub"); 
        rclcpp::init(argc, argv, "controller_sub");
	Controller c;
    	
	//SPIN
	//ros::spin();
	rclcpp::spin(node);
}


