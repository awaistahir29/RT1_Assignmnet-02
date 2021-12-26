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
