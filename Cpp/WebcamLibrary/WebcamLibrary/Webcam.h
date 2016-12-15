
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include <chrono>
#include <thread>
#include <mutex>

#include <opencv2/opencv.hpp>


class Webcam
{
public:
	unsigned char camera_found;

	Webcam();
	~Webcam();

	cv::Mat getCurrentImage();


	void StartStreaming();
	void StopStreaming();


private:
	cv::VideoCapture cam;
	int image_width, image_height, image_channels;
	cv::Mat current_image;
	bool streaming;
	std::thread t;
	std::mutex mtx;

	void captureImage();
	void background_worker();
};