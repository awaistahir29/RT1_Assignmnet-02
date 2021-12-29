#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"
#include "second_assignment/speedRequest.h"
#include "second_assignment/robotSpeed.h"
#include "std_srvs/Empty.h"

// Declaring ServiceClient global object.

ros::ServiceClient client1;

// Declaring Publisher object.

ros::Publisher pub;

// The function to read the input char.

int main (int argc, char **argv) 
{
	// Initialize the node, setup the NodeHandle 
	// for handling the communication with the 
	// ROS //system.

	ros::init(argc, argv, "UserInterface"); 
	ros::NodeHandle nh;
	char a;

	// Defining the publishing of the message Accval.

	pub = nh.advertise<second_assignment::robotSpeed>("/robotSpeed", 10); 

	// Creating the client with his attributes.

	client1 = nh.serviceClient<second_assignment::speedRequest>("/speedRequest");

	// Making the function spin.

	while(1){

	// Reading the input from user
	std::cout << "PRESS D, IF YOU WANT TO DECREASE THE SPEED OF THE ROBOT\n";
	std::cout << "PRESS A, IF YOU WANT TO INCREASE THE SPEED OF THE ROBOT\n";
	std::cout << "If you want to reset, press 'r'!\n";
	std::cin >> a;
	
	// Creating a variable to send a request
	// to the server "speedRequest".

	second_assignment::speedRequest a_srv;

	// Sending a char as request.

	a_srv.request.in = a;

	// Waiting for the server to give a response.

	client1.waitForExistence();
	client1.call(a_srv);

	// Creating a message to send the response to
	// robotController.cpp

	second_assignment::robotSpeed n;
	n.speed = a_srv.response.out;
	pub.publish(n);
	ros::spinOnce();
	}

	return 0;
}
