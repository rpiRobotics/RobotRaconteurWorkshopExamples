
#ifdef SendMessage
#undef SendMessage
#endif

#include <RobotRaconteur.h>
#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>

#include "edu__rpi__cats__sensors__camera_interface.h"
#include "edu__rpi__cats__sensors__camera_interface_stubskel.h"
#include "example__webcam.h"
#include "example__webcam_stubskel.h"

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include <opencv2/opencv.hpp>

#include <boost/enable_shared_from_this.hpp>
#include <map>

class Webcam : public example::webcam::Webcam, public boost::enable_shared_from_this<Webcam>
{
public:

	Webcam();
	~Webcam();

	virtual uint8_t get_camera_found();
	virtual void set_camera_found(uint8_t value);

	virtual RR_SHARED_PTR<edu::rpi::cats::sensors::camera_interface::Image > getCurrentImage();
	virtual RR_SHARED_PTR<edu::rpi::cats::sensors::camera_interface::ImageHeader > getImageHeader();

	virtual void StartStreaming();
	virtual void StopStreaming();

	virtual RR_SHARED_PTR<RobotRaconteur::Pipe<RR_SHARED_PTR<edu::rpi::cats::sensors::camera_interface::Image > > > get_ImageStream();
	virtual void set_ImageStream(RR_SHARED_PTR<RobotRaconteur::Pipe<RR_SHARED_PTR<edu::rpi::cats::sensors::camera_interface::Image > > > value);

private:
	cv::VideoCapture cam;
	cv::Mat current_image;
	bool streaming, camera_found;
	int32_t img_width, img_height, img_channels;
	uint8_t img_step;
	boost::thread t;
	boost::mutex mtx_;

	RR_SHARED_PTR<RobotRaconteur::Pipe<RR_SHARED_PTR<edu::rpi::cats::sensors::camera_interface::Image> > > image_stream;
	RR_SHARED_PTR<RobotRaconteur::PipeBroadcaster<RR_SHARED_PTR<edu::rpi::cats::sensors::camera_interface::Image> > > image_stream_broadcaster;
	
	void captureImage();
	RR_SHARED_PTR<edu::rpi::cats::sensors::camera_interface::Image > createRRImage();
	void background_worker();

	//void ImageStream_pipeconnect(RR_SHARED_PTR<RobotRaconteur::PipeEndpoint<RR_SHARED_PTR<edu::rpi::cats::sensors::camera_interface::Image> > > pipe_ep);
	//void ImageStream_pipeclosed(RR_SHARED_PTR<RobotRaconteur::PipeEndpoint<RR_SHARED_PTR<edu::rpi::cats::sensors::camera_interface::Image> > > pipe_ep);
};