#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"
#include "second_assignment/robotSpeed.h" // Msg Header
#include "second_assignment/speedRequest.h" // Server Header
#include "std_srvs/Empty.h"

// Declaring the publisher, message and global variables.

ros::Publisher pub;
geometry_msgs::Twist my_vel;
float speed = 0;
float adder = 0;

// Developing the MinDistance() function, we want in input an array of floats 
// and the indexes where we want the function to iterate the for loop().

float MinDistance(int min, int max,float ranges[]){

    float min_value = 100.0;
    for(int i = min; i <= max; i++){
        if (ranges[i]<=min_value) min_value = ranges[i];
    }
    return min_value;
}

// Developing the RobotCallback() function. To control the Robot.

void Callback(const sensor_msgs::LaserScan::ConstPtr& msg){

    // Declaring some local variables.

    float val_min_right, val_min_front, val_min_left, val_minfront_left, val_minfront_right;
    float laserRange[720];
    
    // For loop() to fill an array which will be passed to StudyDistance()
    // function, 

    for(int i = 0; i<721; i++){
        laserRange[i] = msg->ranges[i];
    }

    // Studying the closest distance on the right, front and left.

    val_min_right = MinDistance(0, 100, laserRange); 
    val_minfront_right = MinDistance(210, 310 , laserRange);
    val_min_front = MinDistance(310, 410, laserRange); 
    val_minfront_left = MinDistance(410, 520, laserRange);
    val_min_left = MinDistance(620, 720, laserRange);

    // If the distance on the front is lower than 1.57, the robot will 
    // turn either left or right.

    if(val_min_front<1.5){
		if(val_min_left>val_min_right){
		    my_vel.angular.z = 1;
		    my_vel.linear.x = 0.1;
		    }
        	else if(val_min_right>val_min_left){
		    my_vel.angular.z = -1;
		    my_vel.linear.x = 0.1;
        		}
    		}
    // The Robot will go straight if it will be far away from the wall
    else{
        my_vel.linear.x = 1 + adder;
        my_vel.angular.z = 0;
    }

    // Publishing the velocity of the robot.

    float velocity = my_vel.linear.x;
    ROS_INFO("Right: @[%f]", adder);    
    pub.publish(my_vel);
}

// The SpeedCallback is very important. As we are getting velocity from the user node,
// by using Custom message robotSpeed.

void SpeedCallback(const second_assignment::robotSpeed::ConstPtr& uno){
    adder = uno->speed;
}

int main (int argc, char **argv)
{
    // Initializing the node, setup the NodeHandle.

    ros::init(argc, argv, "robotController");  
    ros::NodeHandle nh;

    // Defining the publisher.
    
    pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1);

    // Declaring first and second suscriber, to robotSpeed topic and to base_scan.

    ros::Subscriber sub2 = nh.subscribe("/robotSpeed", 1, SpeedCallback);
    ros::Subscriber sub = nh.subscribe("/base_scan", 1, Callback);

    // Spinning the callback function.

    ros::spin();
    return 0;
}
