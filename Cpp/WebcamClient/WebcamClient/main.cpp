
#include <RobotRaconteur.h>

#include "edu__rpi__cats__sensors__camera_interface.h"
#include "edu__rpi__cats__sensors__camera_interface_stubskel.h"
#include "example__webcam.h"
#include "example__webcam_stubskel.h"

#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

int main(char *argv[], int argc)
{
	// Register Local Transport
	RR_SHARED_PTR<RobotRaconteur::LocalTransport> t1 = RR_MAKE_SHARED<RobotRaconteur::LocalTransport>();
	RobotRaconteur::RobotRaconteurNode::s()->RegisterTransport(t1);

	// Register Tcp Transport
	RR_SHARED_PTR<RobotRaconteur::TcpTransport> t = RR_MAKE_SHARED<RobotRaconteur::TcpTransport>();
	t->EnableNodeDiscoveryListening();
	RobotRaconteur::RobotRaconteurNode::s()->RegisterTransport(t);

	// Register service that client will connect to
	RobotRaconteur::RobotRaconteurNode::s()->RegisterServiceType(RR_MAKE_SHARED<edu::rpi::cats::sensors::camera_interface::edu__rpi__cats__sensors__camera_interfaceFactory>());
	RobotRaconteur::RobotRaconteurNode::s()->RegisterServiceType(RR_MAKE_SHARED<example::webcam::example__webcamFactory>());

	// Connect to service
	RR_SHARED_PTR<example::webcam::Webcam> w = RobotRaconteur::rr_cast<example::webcam::Webcam>(RobotRaconteur::RobotRaconteurNode::s()->ConnectService("tcp://localhost:2345/example.webcam/Webcam"));

	if (w->get_camera_found() <= 0)
		return -1;

	RR_SHARED_PTR<edu::rpi::cats::sensors::camera_interface::ImageHeader> Ih = w->getImageHeader();
	cv::Mat current_image(Ih->height, Ih->width, CV_8UC3);

	RR_SHARED_PTR<edu::rpi::cats::sensors::camera_interface::Image> I;

	while (true)
	{
		I = w->getCurrentImage();
		memcpy(current_image.data, I->data->ptr(), I->height * I->width * I->channels);

		cv::imshow("Image", current_image);
		if (cv::waitKey(20) > 0)
			break;
	}

	return 0;
}