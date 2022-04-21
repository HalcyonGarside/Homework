//#include <opencv2/opencv.hpp>
//
//using namespace cv;
//
//int main()
//{
//	//Image 1
//	Mat inImg = imread("p2_image1.png");
//	Mat IIbw = imread("p2_image1.png", IMREAD_GRAYSCALE);
//	threshold(IIbw, IIbw, 100, 255, THRESH_BINARY_INV);
//
//	Mat strel = getStructuringElement(MORPH_RECT, Size(3, 3));
//	dilate(IIbw, IIbw, strel);
//	dilate(IIbw, IIbw, strel);
//	dilate(IIbw, IIbw, strel);
//	erode(IIbw, IIbw, strel);
//	erode(IIbw, IIbw, strel);
//	erode(IIbw, IIbw, strel);
//
//	std::vector<std::string> dicemat = std::vector<std::string>();
//
//	dicemat.push_back("6_white.png");
//	dicemat.push_back("better5diew.png");
//	dicemat.push_back("4_white.png");
//	dicemat.push_back("better3diew.png");
//	dicemat.push_back("better2diew.png");
//	dicemat.push_back("1_white.png");
//
//	Mat curDice;
//	Mat dieEroded, onSymb;
//	Mat diceReg;
//	int value;
//	Range imgRows, imgCols;
//	char* string = (char*)malloc(10 * sizeof(char));
//
//	for (int i = 0; i < dicemat.size(); i++)
//	{
//		curDice = imread(dicemat[i], IMREAD_GRAYSCALE);
//		threshold(curDice, curDice, 100, 255, THRESH_BINARY_INV);
//
//		dilate(curDice, curDice, strel);
//		dilate(curDice, curDice, strel);
//		erode(curDice, curDice, strel);
//		erode(curDice, curDice, strel);
//		erode(curDice, curDice, strel);
//
//		value = 6 - i;
//
//		erode(IIbw, dieEroded, curDice);
//		dilate(dieEroded, onSymb, curDice);
//
//		IIbw = IIbw - onSymb;
//
//		imgRows = Range((dieEroded.rows / 2) - 100, (dieEroded.rows / 2) + 100);
//		imgCols = Range(1100, 1900);
//		diceReg = dieEroded(imgRows, imgCols);
//		
// 		for (int r = 0; r < diceReg.rows; r++)
//		{
//			for (int c = 0; c < diceReg.cols; c++)
//			{
//				if (diceReg.at<uchar>(r, c) > 0)
//				{
//					putText(inImg, format("%d", value), Point(c + 1100, r + (dieEroded.rows / 2) - 100), FONT_HERSHEY_DUPLEX, 1, CV_RGB(255, 0, 0));
//				}
//			}
//		}
//	}
//
//	imshow("Modded Thing", inImg);
//	waitKey(0);
//
//	imwrite("p2_out1.png", inImg);
//}