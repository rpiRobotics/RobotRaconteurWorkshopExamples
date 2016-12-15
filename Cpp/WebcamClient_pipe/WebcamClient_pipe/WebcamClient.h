
#include "edu__rpi__cats__sensors__camera_interface.h"
#include "edu__rpi__cats__sensors__camera_interface_stubskel.h"

#include "example__webcam.h"
#include "example__webcam_stubskel.h"

#include <RobotRaconteur.h>

#include <iostream>
#include <string>
#include <vector>
//#include <mutex>

#include <opencv2/opencv.hpp>

class WebcamClient
{
public:
	WebcamClient();
	~WebcamClient();
	void ConnectToWebcam(RR_SHARED_PTR<example::webcam::Webcam> w);
	cv::Mat get_current_image();
	
private:
	cv::Mat current_image;
	void new_frame(RR_SHARED_PTR<RobotRaconteur::PipeEndpoint<RR_SHARED_PTR<edu::rpi::cats::sensors::camera_interface::Image> > > pipe_ep);
	void convert_to_opencv(uint8_t *data, size_t s);
};