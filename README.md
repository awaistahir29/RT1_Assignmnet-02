# RT1_Assignmnet-02
This is the second assignemnt of the Research Track 1. 
ROS(Robot Operating System) has been used to control the robot in the environment.
## Installing and Running
The simulator requires ROS (Robot Operating System), which is a set of software libraries and tools that help you build robot applications. The simulator perfectly runs on the Noetic Release of ROS, I haven't tried the ROS 2 release yet, so let me know if it does actually work.
Once you have install the ROS, you have to create your own workspace where you can build packages. 
Thereafter you have to copy the code into src folder of your workspace
### Step #01
Firstly, you need to run the master node in your terminal to run the ROS in your PC.
```
roscore &
```
### Step #02
Secondly, you need to run the given command in the root of your workspace to build the workspace.
```
catkin_make
```
Then you have to run rospack profile in order to refresh your packages.
```
rospack profile
```
### Step #03
Now you have to run the folloeing nodes in the root of your workspace 
##### Run this command to launch the robot in the given environment.
```
rosrun stage_ros stageros $(rospack find second_assignment)/world/my_world.world
```
##### Firstly, you have to run the robotController Node which control the robot in the environment.
```
rosrun second_assignment robotController_node
```
##### Seccondly, you need to run the Server node which handles service to manage request from the user and give the responce to the user node.
```
rosrun second_assignment server_node
```
##### Finally, you need to run the User node which takes input from the user and send the request to the server node and waiting for the response from the server node.
```
rosrun second_assignment user_node
```
# Simulation
<p align="center">
  
 ## Nodes and their logic

_Here I will explain each node code and tasks, to have a deeper description of the code, check the comments inside of it._

### stageros node (stage_ros package)

The stageros node wraps the Stage 2-D multi-robot simulator, via libstage. Stage simulates a world as defined in a .world file. This file tells stage everything about the world, from obstacles (usually represented via a bitmap to be used as a kind of background), to robots and other objects.
The nodes has the following aspects:
- Subscriptions
  - The node subscribes to the `cmd_vel (geometry_msgs/Twist)` topic, to manage the velocity of the robot.
- Publishing
    - `odom (nav_msgs/Odometry)`: odometry data of the model. 
    - `base_scan (sensor_msgs/LaserScan)`: __scans from the laser model. We will use this one.__
    - `base_pose_ground_truth (nav_msgs/Odometry)`: __the ground truth pose. We will use this one.__
    - `image (sensor_msgs/Image)`: visual camera image.
    - `depth (sensor_msgs/Image)`: depth camera image.
    - `camera_info (sensor_msgs/CameraInfo)`: camera calibration info.
  
  ### robotController node (second_assignment package)
  ### server node (second_assignment package)
  ### User node (second_assignment package)
  
  ## Conclusion and possible improvements
  `rosrun rqt_graph rqt_graph`
