
#include "Webcam.h"

int main(char *argv[], int argc)
{

	Webcam w = Webcam();

	w.StartStreaming();

	while (true)
	{
		cv::imshow("img", w.getCurrentImage());

		if (cv::waitKey(30) > 0)
			break;
	}

	cv::destroyAllWindows();
	return 0;
}