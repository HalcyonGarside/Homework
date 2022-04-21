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
//	VideoWriter output_cap("p5_result3.mp4", VideoWriter::fourcc('H', '2', '6', '4'), 30, cv::Size(2080, 1088));
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
//	Mat refFrame;
//	int count = 0;
//
//	Mat history = Mat::zeros(1088, 2080, CV_8UC3);
//
//	Scalar pixcol;
//	Scalar curPixcol;
//	Scalar histPixcol;
//
//	int tolerance = 20;
//
//	//Max 255
//	int decayRate = 5;
//
//	while (input_cap.read(frame)) {
//
//		if (!refFrame.empty())
//		{
//			for (int i = 0; i < 1088; i++)
//			{
//				for (int j = 0; j < 2080; j++)
//				{
//					pixcol = refFrame.at<Vec3b>(i, j);
//					curPixcol = frame.at<Vec3b>(i, j);
//					histPixcol = history.at<Vec3b>(i, j);
//					if (pixcol.val[0] < curPixcol.val[0] - tolerance || pixcol.val[0] > curPixcol.val[0] + tolerance ||
//						pixcol.val[1] < curPixcol.val[1] - tolerance || pixcol.val[1] > curPixcol.val[1] + tolerance ||
//						pixcol.val[2] < curPixcol.val[2] - tolerance || pixcol.val[2] > curPixcol.val[2] + tolerance)
//						history.at<Vec3b>(i, j) = Vec3b(255, 255, 255);
//					else if (histPixcol.val[0] != 0)
//					{
//						history.at<Vec3b>(i, j) = Vec3b(histPixcol[0] - decayRate, histPixcol[1] - decayRate, histPixcol[2] - decayRate);
//						//printf("Update...\n");
//					}
//				}
//			}
//		}
//
//		imshow("output", history);
//		output_cap.write(history);
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
//	output_cap.release();
//
//	return 1;
//
//}