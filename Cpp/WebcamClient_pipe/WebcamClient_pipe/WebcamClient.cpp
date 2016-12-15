#include "WebcamClient.h"

WebcamClient::WebcamClient()
{

}
WebcamClient::~WebcamClient()
{

}


void WebcamClient::ConnectToWebcam(RR_SHARED_PTR<example::webcam::Webcam> w)
{
	RR_SHARED_PTR<edu::rpi::cats::sensors::camera_interface::ImageHeader> Ih = w->getImageHeader();
	current_image = cv::Mat(Ih->height, Ih->width, CV_8UC3);
	
	RR_SHARED_PTR<RobotRaconteur::PipeEndpoint<RR_SHARED_PTR<edu::rpi::cats::sensors::camera_interface::Image> > > pipe_ep = w->get_ImageStream()->Connect(-1);
	pipe_ep->PacketReceivedEvent.connect(boost::bind(&WebcamClient::new_frame, this, _1));
}

cv::Mat WebcamClient::get_current_image()
{
	return current_image;
}

void WebcamClient::convert_to_opencv(uint8_t *data, size_t s)
{
	memcpy(current_image.data, data, s);
}

void WebcamClient::new_frame(RR_SHARED_PTR<RobotRaconteur::PipeEndpoint<RR_SHARED_PTR<edu::rpi::cats::sensors::camera_interface::Image> > > pipe_ep)
{
	while (pipe_ep->Available() > 0)
	{
		RR_SHARED_PTR<edu::rpi::cats::sensors::camera_interface::Image> I = pipe_ep->ReceivePacket();
		convert_to_opencv(I->data->ptr(), I->data->Length());
			
	}
}