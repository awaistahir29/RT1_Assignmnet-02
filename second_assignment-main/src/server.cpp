#include "second_assignment/robotSpeed.h"
#include "second_assignment/speedRequest.h"
#include "ros/ros.h"
#include "std_srvs/Empty.h"

// Initializing the object for already provided service 

std_srvs::Empty res_server;

float pos = 0;
	
// Developing ServerCallback() function, the function dedicated to
// change the speed by communicating with UI node.

bool ServerCallback(second_assignment::speedRequest::Request &req, second_assignment::speedRequest::Response &res){

	// If the input is 'a' or 'A' The speed of the robot wil increace.

	if(req.in == 'a' || req.in == 'A'){
		pos += 0.5;
		}	
	// If the input is 's', The speed of the robot will decreace.

	if(req.in == 'd' || req.in == 'D'){
		pos -= 0.5;
		}

	// If the input is 'r', the position of robot will reset 
	// By calling reset serrvice

	if(req.in == 'r' || req.in == 'R'){
		ros::service::call("/reset_positions", res_server);
		}

	// We put in the response the value.

	res.out = pos;
	ROS_INFO("Right: @[%f]", res.out);    
	return true;
}

int main(int argc, char **argv){

	// Initializing the node.

	ros::init(argc, argv, "Server");
	ros::NodeHandle nh;

	// Declaring the service /speedRequest.

	ros::ServiceServer service =  nh.advertiseService("/speedRequest", ServerCallback);

	// Spinning the ServerCallback function.
	
	ros::spin();
	return 0;
}
