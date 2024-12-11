**Description**
This project simulates the control and communication of UR5 robotic arm with RTI DDS and Simulink

**Update**
- initial release of the barebone of the project
- define the qos structure in complex system with multiple domains
- add dds performance test
- add ros2 humble to performance test
- add profile generator increase 1st 2nd degree stability
- increase the robot movement frequency (1KHz: comm; 4KHz: movement)
- add shmio from subscriber to display
- add OpenGL GUI display
- add FK position data to shmio
- add simulink files

<video src='resources/doc/gui_demo1.mp4'></video>
<video src='resources/doc/gui_demo2.mp4'></video>