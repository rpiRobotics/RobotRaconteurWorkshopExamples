
#include "Webcam.h"


Webcam::Webcam()
{
	streaming = camera_found = false;
	
	if (!cam.open(0))
	{
		std::cout << "Failed to open camera" << std::endl;
		return;
	}

	camera_found = true;
	cam >> current_image;

	// Construct camera_interface::ImageHeader object
	if (!current_image.empty())
	{
		img_width = current_image.cols;
		img_height = current_image.rows;
		img_channels = current_image.channels();
		img_step = current_image.elemSize();
	}


}

Webcam::~Webcam()
{
	StopStreaming();
	boost::this_thread::sleep(boost::posix_time::seconds(1));
}

uint8_t Webcam::get_camera_found()
{
	return camera_found;
}
void Webcam::set_camera_found(uint8_t value)
{
	//cannot be set externally - nothing happens
}

RR_SHARED_PTR<edu::rpi::cats::sensors::camera_interface::Image > Webcam::getCurrentImage()
{
	if (!streaming)
		captureImage();
	
	return createRRImage();
}

RR_SHARED_PTR<edu::rpi::cats::sensors::camera_interface::ImageHeader > Webcam::getImageHeader()
{
	boost::lock_guard<boost::mutex> guard(mtx_);
	RR_SHARED_PTR<edu::rpi::cats::sensors::camera_interface::ImageHeader > Ih(new edu::rpi::cats::sensors::camera_interface::ImageHeader);
	Ih->width = img_width;
	Ih->height = img_height;
	Ih->channels = img_channels;
	Ih->step = img_step;
	return Ih;
}

void Webcam::StartStreaming()
{
	if (streaming)
		return;

	streaming = true;
	this->t = boost::thread(boost::bind(&Webcam::background_worker, this));
}

void Webcam::StopStreaming()
{
	if (!streaming)
		return;

	streaming = false;
}

RR_SHARED_PTR<RobotRaconteur::Pipe<RR_SHARED_PTR<edu::rpi::cats::sensors::camera_interface::Image > > > Webcam::get_ImageStream()
{
	return image_stream;
}
void Webcam::set_ImageStream(RR_SHARED_PTR<RobotRaconteur::Pipe<RR_SHARED_PTR<edu::rpi::cats::sensors::camera_interface::Image > > > value)
{
	image_stream = value;

	//Use a PipeBroadcaster to send the same packets to every connected client PipeEndpoint.
	//Set the maximum backlog parameter to 3.  This will drop frames if more than 3 frames
	//have been sent without ack.
	image_stream_broadcaster = RR_MAKE_SHARED<RobotRaconteur::PipeBroadcaster< RR_SHARED_PTR< edu::rpi::cats::sensors::camera_interface::Image > > >();
	image_stream_broadcaster->Init(image_stream, 3);
	
}

void Webcam::captureImage()
{
	boost::lock_guard<boost::mutex> guard(mtx_);
	if (camera_found)
		cam >> current_image;
}

RR_SHARED_PTR<edu::rpi::cats::sensors::camera_interface::Image > Webcam::createRRImage()
{
	boost::lock_guard<boost::mutex> guard(mtx_);

	// convert OpenCV image into camera_interface::Image structure
	RR_SHARED_PTR<edu::rpi::cats::sensors::camera_interface::Image > I(new edu::rpi::cats::sensors::camera_interface::Image);
	I->width = img_width;
	I->height = img_height;
	I->channels = img_channels;
	I->data = RobotRaconteur::AllocateRRArray<uint8_t>(img_width*img_height*img_channels);
	if (!current_image.empty())
		memcpy(I->data->ptr(), current_image.data, img_width*img_height*img_channels);

	return I;
}

void async_frame_send_handler()
{

}

void Webcam::background_worker()
{
	while (streaming)
	{
		try
		{
			if (cam.isOpened())
			{
				captureImage();

				if (!current_image.empty())
					image_stream_broadcaster->AsyncSendPacket(createRRImage(), async_frame_send_handler);
			}

			boost::this_thread::sleep(boost::posix_time::milliseconds(50));
			boost::this_thread::interruption_point();
		}
		catch (...) {
			break;
		}
	}
}