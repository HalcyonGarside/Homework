//#include <opencv2/opencv.hpp>
//
//using namespace cv;
//
//int main()
//{
//	//Image 1
//	Mat inImg = imread("p1_image1.png");
//	Mat IIbw = imread("p1_image1.png", IMREAD_GRAYSCALE);
//
//	imshow("Thing", inImg);
//
//	std::vector<Vec3f> circles;
//	HoughCircles(IIbw, circles, HOUGH_GRADIENT, 1, 10, 60, 100, 20, 60);
//
//	for (int i = 0; i < circles.size(); i++)
//	{
//		Vec3f curCirc = circles.at(i);
//		circle(inImg, Point(curCirc[0], curCirc[1]), curCirc[2], cv::Scalar(255, 0, 0, 255), 4);
//	}
//
//	imshow("Modded Thing", inImg);
//	imwrite("p1_image1_cv_finished.png", inImg);
//	waitKey(0);
//
//	//Image 2
//	inImg = imread("p1_image2.png");
//	IIbw = imread("p1_image2.png", IMREAD_GRAYSCALE);
//
//	imshow("Thing", inImg);
//
//	HoughCircles(IIbw, circles, HOUGH_GRADIENT, 1, 10, 60, 100, 20, 60);
//
//	for (int i = 0; i < circles.size(); i++)
//	{
//		Vec3f curCirc = circles.at(i);
//		circle(inImg, Point(curCirc[0], curCirc[1]), curCirc[2], cv::Scalar(255, 0, 0, 255), 4);
//	}
//
//	imshow("Modded Thing", inImg);
//	imwrite("p1_image2_cv_finished.png", inImg);
//	waitKey(0);
//
//	//Image 3
//	inImg = imread("p1_image3.png");
//	IIbw = imread("p1_image3.png", IMREAD_GRAYSCALE);
//
//	imshow("Thing", inImg);
//
//	HoughCircles(IIbw, circles, HOUGH_GRADIENT, 1, 10, 60, 100, 20, 60);
//
//	for (int i = 0; i < circles.size(); i++)
//	{
//		Vec3f curCirc = circles.at(i);
//		circle(inImg, Point(curCirc[0], curCirc[1]), curCirc[2], cv::Scalar(255, 0, 0, 255), 4);
//	}
//
//	imshow("Modded Thing", inImg);
//	imwrite("p1_image3_cv_finished.png", inImg);
//	waitKey(0);
//}