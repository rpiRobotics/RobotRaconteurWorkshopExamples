# RobotRaconteurWorkshopExamples
Example code for Robot Raconteur service and client generation

get Robot Raconteur 0.8.1 (or higher) at http://robotraconteur.com/

All Python scripts are dependent on numpy and scipy (http://scipy.org/)
All C++ service and client scripts are dependent on boost 1.60 (http://boost.org)
Python and C++ Webcam examples are dependent on OpenCV 3.0 (http://opencv.org)

For C++ webcam projects make sure to include external libraries
opencv_ts300(d).lib
opencv_world300(d).lib;
and move the opencv dll "opencv_world300(d).dll" into the executable path

For C++ Robot Raconteur projects make sure to include external libraries
Mswsock.lib
ws2_32.lib
IPHLPAPI.lib
Crypt32.lib
Secur32.lib
libRobotRaconteurCore.lib
