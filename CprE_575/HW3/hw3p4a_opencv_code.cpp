// Headers
#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// compile command
// cl /EHsc play_vid_test.cpp /I D:\installs\opencv\opencv\build\include /link /LIBPATH:D:\installs\opencv\opencv\build\x64\vc15\lib opencv_world451.lib


int main(int argc, char* argv[]) {

	// Load input video
	//  If your video is in a different source folder than your code, 
	//  make sure you specify the directory correctly!
	VideoCapture input_cap("p4_video3.avi");
	VideoWriter output_cap("p4_result3.mp4", VideoWriter::fourcc('H', '2', '6', '4'), 30, cv::Size(2080, 1088));

	// Check validity of target file
	if (!input_cap.isOpened()) {
		std::cout << "Input video not found." << std::endl;
		return -1;
	}

	if (!output_cap.isOpened()) {
		std::cout << "Output video failed." << std::endl;
		return -1;
	}

	namedWindow("output", WINDOW_AUTOSIZE);

	// Loop to read from input one frame at a time
	Mat frame;
	int count = 0;
	while (input_cap.read(frame)) {

		Mat gray;
		cvtColor(frame, gray, COLOR_BGR2GRAY);
		medianBlur(gray, gray, 5);
		vector<Vec3f> circles;
		HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
			gray.rows / 32,
			100, 30, 20, 40
		);
		for (size_t num = 0; num < circles.size(); num++) {
			Vec3i c = circles[num];
			Point center = Point(c[0], c[1]);

			Scalar col = frame.at<Vec3b>(center.y, center.x);

			if (col.val[2] > col.val[1] && col.val[2] > col.val[0])
			{
				circle(frame, center, c[2], Scalar(255, 0, 0, 125), -1, FILLED);
			}
			else
			{
				circle(frame, center, c[2], Scalar(255, 0, 255, 125), -1, FILLED);
			}

			circle(frame, center, c[2], Scalar(0, 0, 0), 3, LINE_AA);
		}

		//imshow("output", frame);
		output_cap.write(frame);

		// wait for ESC key to be pressed
		/*if (waitKey(30) == 27)
		{
			break;
		}*/
	}

	// free the capture objects from memory
	input_cap.release();
	output_cap.release();

	return 1;

}