
#include <RobotRaconteur.h>

#include "WebcamClient.h"
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
	
	WebcamClient wc = WebcamClient();
	wc.ConnectToWebcam(w);
	
	w->StartStreaming();

	while (true)
	{
		cv::imshow("Image", wc.get_current_image());
		if (cv::waitKey(20) > 0)
			break;
	}

	w->StopStreaming();

	return 0;
}