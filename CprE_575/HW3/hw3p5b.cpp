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
	VideoCapture input_cap("p5_video3.avi");
	VideoWriter output_cap("p5b_result3.mp4", VideoWriter::fourcc('H', '2', '6', '4'), 30, cv::Size(2080, 1088));

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
	Mat refFrame;
	Mat dispFrame;
	int count = 0;

	Mat history = Mat::zeros(1088, 2080, CV_8UC1);
	Mat circPos;
	Mat histBlur;
	Mat area;

	vector<pair<Point, Point>> lineVec = vector<pair<Point, Point>>();

	Scalar pixcol;
	Scalar curPixcol;
	uchar histPixcol;
	vector<Vec3f> lastCircles = vector<Vec3f>();

	int tolerance = 20;

	//Max 255
	int decayRate = 255;

	bool isMoving;

	while (input_cap.read(frame)) {

		circPos = Mat::zeros(1088, 2080, CV_8UC3);
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

			circle(circPos, center, c[2], Scalar(0, 0, 255), 3, LINE_AA);
		}

		if (!refFrame.empty())
		{
			for (int i = 0; i < circPos.rows; i++)
			{
				for (int j = 0; j < circPos.cols; j++)
				{
					pixcol = refFrame.at<Vec3b>(i, j);
					curPixcol = circPos.at<Vec3b>(i, j);
					histPixcol = history.at<uchar>(i, j);
					if (pixcol.val[0] < curPixcol.val[0] - tolerance || pixcol.val[0] > curPixcol.val[0] + tolerance ||
						pixcol.val[1] < curPixcol.val[1] - tolerance || pixcol.val[1] > curPixcol.val[1] + tolerance ||
						pixcol.val[2] < curPixcol.val[2] - tolerance || pixcol.val[2] > curPixcol.val[2] + tolerance)
						history.at<uchar>(i, j) = 255;
					else if (histPixcol != 0)
					{
						history.at<uchar>(i, j) = 0;
						//printf("Update...\n");
					}
				}
			}
		}

		circles.clear();
		medianBlur(history, histBlur, 5);
		HoughCircles(histBlur, circles, HOUGH_GRADIENT, 1,
			gray.rows / 32,
			100, 30, 20, 60
		);

		//for (size_t num = 0; num < circles.size(); num++) {
		//	Vec3i c = circles[num];
		//	Point center = Point(c[0], c[1]);

		//	Scalar col = frame.at<Vec3b>(center.y, center.x);

		//	circle(frame, center, c[2], Scalar(0, 0, 255), 3, LINE_AA);
		//}

		area = frame(Range((frame.rows / 2) - 25, (frame.rows / 2) + 75), Range(275, 560));
		dispFrame = frame.clone();

		if (area.at<uchar>(0, 0) > area.at<uchar>(0, 1) && area.at<uchar>(0, 0) > area.at<uchar>(0, 2))
		{
			lineVec.clear();
		}
		else if (!lastCircles.empty())
		{
			for (int i = 0; i < circles.size(); i++)
			{
				Vec3f cc = circles.at(i);
				Point lastCent = Point(cc[0], cc[1]);
				float closestDist = INFINITY;
				Vec3f closestCirc = Vec3f();

				isMoving = true;

				for (int j = 0; j < lastCircles.size(); j++)
				{
					Vec3f lc = lastCircles.at(j);
					Point curCent = Point(lc[0], lc[1]);

					Point distPt = (curCent - lastCent);
					float dist = sqrt((distPt.x * distPt.x) + (distPt.y * distPt.y));
					
					if (dist < closestDist)
					{
						closestCirc = lc;
						closestDist = dist;
					}

					if (dist <= 10)
					{
						isMoving = false;
						break;
					}
				}

				if (isMoving && !(closestCirc[0] == 0 && closestCirc[1] == 0) && closestDist < (closestCirc[2] + cc[2]) * 2 && closestDist > (closestCirc[2] + cc[2]) / 4)
				{
					lineVec.push_back(pair<Point, Point>(lastCent, Point(closestCirc[0], closestCirc[1])));
				}
			}
		}

		for (int i = 0; i < lineVec.size(); i++)
		{
			pair<Point, Point> cline = lineVec.at(i);
			line(frame, cline.first, cline.second, Scalar(255, 0, 255), 3);
		}

		
		imshow("output", frame);
		output_cap.write(frame);

		refFrame = circPos.clone();

		lastCircles.clear();
		
		for (int i = 0; i < circles.size(); i++)
			lastCircles.push_back(circles.at(i));

		// wait for ESC key to be pressed
		if (waitKey(30) == 27)
		{
			break;
		}
	}

	// free the capture objects from memory
	input_cap.release();
	output_cap.release();

	return 1;

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

//// Headers
//#include <opencv2/core/core.hpp> 
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/opencv.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//// compile command
//// cl /EHsc play_vid_test.cpp /I D:\installs\opencv\opencv\build\include /link /LIBPATH:D:\installs\opencv\opencv\build\x64\vc15\lib opencv_world451.lib
//
//
//int main(int argc, char* argv[]) {
//
//	// Load input video
//	//  If your video is in a different source folder than your code, 
//	//  make sure you specify the directory correctly!
//	VideoCapture input_cap("p5_video3.avi");
//	//VideoWriter output_cap("p5_result3.mp4", VideoWriter::fourcc('H', '2', '6', '4'), 30, cv::Size(2080, 1088));
//
//	// Check validity of target file
//	if (!input_cap.isOpened()) {
//		std::cout << "Input video not found." << std::endl;
//		return -1;
//	}
//
//	//if (!output_cap.isOpened()) {
//	//	std::cout << "Output video failed." << std::endl;
//	//	return -1;
//	//}
//
//	namedWindow("output", WINDOW_AUTOSIZE);
//
//	// Loop to read from input one frame at a time
//	Mat frame, testFrame;
//	Mat refFrame;
//	int count = 0;
//
//	Mat history = Mat::zeros(1088, 2080, CV_8UC1);
//
//	Scalar pixcol;
//	Scalar curPixcol;
//	uchar histPixcol;
//
//	vector<Vec3f> circles = vector<Vec3f>();
//
//	int tolerance = 20;
//
//	//Max 255
//	int decayRate = 85;
//
//	while (input_cap.read(frame)) {
//
//		circles.clear();
//		testFrame = frame.clone();
//		if (!refFrame.empty())
//		{
//			for (int i = 0; i < 1088; i++)
//			{
//				for (int j = 0; j < 2080; j++)
//				{
//					pixcol = refFrame.at<Vec3b>(i, j);
//					curPixcol = frame.at<Vec3b>(i, j);
//					histPixcol = history.at<uchar>(i, j);
//					if (pixcol.val[0] < curPixcol.val[0] - tolerance || pixcol.val[0] > curPixcol.val[0] + tolerance ||
//						pixcol.val[1] < curPixcol.val[1] - tolerance || pixcol.val[1] > curPixcol.val[1] + tolerance ||
//						pixcol.val[2] < curPixcol.val[2] - tolerance || pixcol.val[2] > curPixcol.val[2] + tolerance)
//						history.at<uchar>(i, j) = 255;
//					else if (histPixcol > 0)
//					{
//						history.at<uchar>(i, j) = histPixcol - decayRate;
//						//printf("Update...\n");
//					}
//				}
//			}
//
//			medianBlur(history, history, 5);
//
//			HoughCircles(history, circles, HOUGH_GRADIENT, 1,
//				history.rows / 32,
//				50, 30, 30, 60
//			);
//
//			for (size_t num = 0; num < circles.size(); num++) {
//				Vec3i c = circles[num];
//				Point center = Point(c[0], c[1]);
//
//				Scalar col = frame.at<Vec3b>(center.y, center.x);
//
//				circle(testFrame, center, c[2], Scalar(0, 0, 255), 3, LINE_AA);
//			}
//		}
//
//		imshow("output", testFrame);
//		//output_cap.write(history);
//
//		refFrame = frame.clone();
//
//		// wait for ESC key to be pressed
//		if (waitKey(30) == 27)
//		{
//			break;
//		}
//	}
//
//	// free the capture objects from memory
//	input_cap.release();
//	//output_cap.release();
//
//	return 1;
//
//}