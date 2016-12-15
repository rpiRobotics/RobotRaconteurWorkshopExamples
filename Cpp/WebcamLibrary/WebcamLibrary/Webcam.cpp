#include "Webcam.h"


Webcam::Webcam()
{
	camera_found = 0;
	streaming = false;

	if (!cam.open(0))
	{
		std::cout << "Failed to open camera" << std::endl;
		return;
	}

	camera_found = 1;
	cam >> current_image;
}
Webcam::~Webcam()
{
	StopStreaming();
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

cv::Mat Webcam::getCurrentImage()
{
	if (!streaming)
		captureImage();

	return current_image;
}


void Webcam::StartStreaming()
{
	if (streaming)
		return;
	
	streaming = true;
	t = std::thread(&Webcam::background_worker, this);
}
void Webcam::StopStreaming()
{
	if (!streaming)
		return;

	streaming = false;	
}

void Webcam::captureImage()
{
	mtx.lock();
	cam >> current_image;
	mtx.unlock();
}
void Webcam::background_worker()
{
	while (streaming)
	{
		if (cam.isOpened())
			captureImage();
		
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}