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
//	VideoCapture input_cap("p3_video2.avi");
//	VideoWriter output_cap("p3_result2.mp4", VideoWriter::fourcc('H', '2', '6', '4'), 30, cv::Size(2080, 1088));
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
//	Mat frame, frameRef;
//	Mat area, areaRef;
//	int count = 0;
//	while (input_cap.read(frame)) {
//
//		Mat gray, bw;
//		cvtColor(frame, gray, COLOR_BGR2GRAY);
//
//		area = frame(Range((frame.rows / 2) - 25, (frame.rows / 2) + 75), Range(275, 560));
//
//		if (area.at<uchar>(0, 0) > area.at<uchar>(0, 1) && area.at<uchar>(0, 0) > area.at<uchar>(0, 2))
//		{
//			for (int r = 0; r < area.rows; r++)
//			{
//				for (int c = 0; c < area.cols; c++)
//				{
//					if (area.at<uchar>(r, c * 3) > 200 && area.at<uchar>(r, c * 3 + 1) > 200 && area.at<uchar>(r, c * 3 + 2) > 200)
//					{
//						frame.at<uchar>(r + (frame.rows / 2) - 25, (c + 275) * 3 + 0) = 0;
//						frame.at<uchar>(r + (frame.rows / 2) - 25, (c + 275) * 3 + 1) = 0;
//						frame.at<uchar>(r + (frame.rows / 2) - 25, (c + 275) * 3 + 2) = 255;
//					}
//				}
//			}
//		}
//
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