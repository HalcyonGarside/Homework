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
//	VideoCapture input_cap("p4_video1.avi");
//	VideoWriter output_cap("p4b_result1.mp4", VideoWriter::fourcc('H', '2', '6', '4'), 30, cv::Size(2080, 1088));
//
//	// Check validity of target file
//	if (!input_cap.isOpened()) {
//		std::cout << "Input video not found." << std::endl;
//		return -1;
//	}
//
//	if (!output_cap.isOpened()) {
//		std::cout << "Output video failed." << std::endl;
//		return -1;
//	}
//
//	namedWindow("output", WINDOW_AUTOSIZE);
//
//	// Loop to read from input one frame at a time
//	Mat frame;
//
//	vector<Mat> matVec = vector<Mat>(25);
//	vector<Range> topBotMid = vector<Range>(3);
//	vector<Range> positions = vector<Range>(12);
//
//	topBotMid.at(0) = Range(50, 500);
//	topBotMid.at(1) = Range(588, 1038);
//	topBotMid.at(2) = Range(350, 750);
//
//	for (int i = 0; i < 6; i++)
//	{
//		positions.at(i) = Range(70 + (135 * i), 200 + (135 * i));
//		positions.at(i + 6) = Range(1060 + (135 * i), 1190 + (135 * i));
//	}
//
//	Mat testMat, testMat2;
//	int count = 0;
//	while (input_cap.read(frame)) {
//
//		Mat gray;
//		cvtColor(frame, gray, COLOR_BGR2GRAY);
//		medianBlur(gray, gray, 5);
//		vector<Vec3f> circles;
//
//		for (int i = 0; i < 2; i++)
//		{
//			for (int j = 0; j < 6; j++)
//			{
//				testMat = gray(topBotMid.at(i), positions.at(j));
//
//				circles.clear();
//
//				HoughCircles(testMat, circles, HOUGH_GRADIENT, 1, testMat.rows / 15, 100, 30, 20, 40);
//				if (circles.size() > 0)
//				{
//					Point center = Point(circles[0][0], circles[0][1]);
//					Scalar col = frame.at<Vec3b>(center.y + topBotMid.at(i).start, center.x + positions.at(j).start);
//					if (col.val[2] > col.val[1] && col.val[2] > col.val[0])
//					{
//						putText(frame, format("%dr", circles.size()), Point(positions.at(j).start, topBotMid.at(i).start), FONT_HERSHEY_DUPLEX, 1, CV_RGB(255, 0, 0));
//					}
//					else
//					{
//						putText(frame, format("%dw", circles.size()), Point(positions.at(j).start, topBotMid.at(i).start), FONT_HERSHEY_DUPLEX, 1, CV_RGB(255, 0, 0));
//					}
//				}
//				else
//				{
//					putText(frame, "0", Point(positions.at(j).start, topBotMid.at(i).start), FONT_HERSHEY_DUPLEX, 1, CV_RGB(255, 0, 0));
//				}
//
//				testMat = gray(topBotMid.at(i), positions.at(j + 6));
//
//				circles.clear();
//				HoughCircles(testMat, circles, HOUGH_GRADIENT, 1, testMat.rows / 15, 100, 30, 20, 40);
//				if (circles.size() > 0)
//				{
//					Point center = Point(circles[0][0], circles[0][1]);
//					Scalar col = frame.at<Vec3b>(center.y + topBotMid.at(i).start, center.x + positions.at(j + 6).start);
//					if (col.val[2] > col.val[1] && col.val[2] > col.val[0])
//					{
//						putText(frame, format("%dr", circles.size()), Point(positions.at(j + 6).start, topBotMid.at(i).start), FONT_HERSHEY_DUPLEX, 1, CV_RGB(255, 0, 0));
//					}
//					else
//					{
//						putText(frame, format("%dw", circles.size()), Point(positions.at(j + 6).start, topBotMid.at(i).start), FONT_HERSHEY_DUPLEX, 1, CV_RGB(255, 0, 0));
//					}
//				}
//				else
//				{
//					putText(frame, "0", Point(positions.at(j + 6).start, topBotMid.at(i).start), FONT_HERSHEY_DUPLEX, 1, CV_RGB(255, 0, 0));
//				}
//			}
//		}
//
//		circles.clear();
//
//		matVec.at(24) = frame(topBotMid.at(2), Range(920, 1070));
//
//		testMat = gray(topBotMid.at(2), Range(920, 1070));
//
//		HoughCircles(testMat, circles, HOUGH_GRADIENT, 1, testMat.rows / 15, 100, 30, 20, 40);
//		if (circles.size() > 0)
//		{
//			Point center = Point(circles[0][0], circles[0][1]);
//			Scalar col = frame.at<Vec3b>(center.y + topBotMid.at(2).start, center.x + 920);
//			if (col.val[2] > col.val[1] && col.val[2] > col.val[0])
//			{
//				putText(frame, format("%dr", circles.size()), Point(920, topBotMid.at(2).start), FONT_HERSHEY_DUPLEX, 1, CV_RGB(255, 0, 0));
//			}
//			else
//			{
//				putText(frame, format("%dw", circles.size()), Point(920, topBotMid.at(2).start), FONT_HERSHEY_DUPLEX, 1, CV_RGB(255, 0, 0));
//			}
//		}
//		else
//		{
//			putText(frame, "0", Point(920, topBotMid.at(2).start), FONT_HERSHEY_DUPLEX, 1, CV_RGB(255, 0, 0));
//		}
//
//		imshow("output", frame);
//		output_cap.write(frame);
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
//	output_cap.release();
//
//	return 1;
//
//}