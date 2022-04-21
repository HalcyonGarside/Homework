//#include <opencv2/opencv.hpp>
//
//using namespace cv;
//
////-------------Find the locations of 'X' in the picture-------------
//void findSymbolLocs(Mat origIm, Mat structElem, Mat& outMat)
//{
//	Mat invSymbol;
//	flip(structElem, invSymbol, -1);
//
//	Mat eroded, symbols;
//	erode(origIm, eroded, structElem);
//	dilate(eroded, outMat, invSymbol);
//}
//
//int main()
//{
//
//	//Read, invert, and show the original pic
//	Mat initPic = imread("C:/Users/hoodi/Desktop/Homework/Semester8/HCI575/HW2/HW2/HW2/hw2_files/p5_search.png", IMREAD_GRAYSCALE);
//	Mat picBin, bi;
//	threshold(initPic, picBin, 100, 255, THRESH_BINARY_INV);
//
//	imshow("The Original", picBin);
//
//
//	//-------------Parse just the grid-------------
//	int rst = 0;
//	int rfin = 0;
//
//	int cst = 0;
//	int cfin = 0;
//
//	for (int i = 0; i < picBin.rows; i++)
//	{
//		for (int coord = 0; coord < picBin.cols; coord++)
//		{
//			if (picBin.at<uchar>(i, coord) > 0)
//			{
//				if (rst == 0) rst = i;
//				else rfin = i;
//			}
//		}
//	}
//
//
//	for (int i = 0; i < picBin.cols; i++)
//	{
//		for (int coord = 0; coord < picBin.rows; coord++)
//		{
//			if (picBin.at<uchar>(coord, i) > 0)
//			{
//				if (cst == 0) cst = i;
//				else cfin = i;
//			}
//		}
//	}
//
//	Mat outIm = picBin(Range(rst, rfin), Range(cst, cfin));
//
//	//-------------Get the structuring elements-------------
//	Mat xStructure = imread("C:/Users/hoodi/Desktop/Homework/Semester8/HCI575/HW2/HW2/HW2/Symbol_Cutouts/X.png", IMREAD_GRAYSCALE);
//	Mat oStructure = imread("C:/Users/hoodi/Desktop/Homework/Semester8/HCI575/HW2/HW2/HW2/Symbol_Cutouts/O.png", IMREAD_GRAYSCALE);
//	Mat dStructure = imread("C:/Users/hoodi/Desktop/Homework/Semester8/HCI575/HW2/HW2/HW2/Symbol_Cutouts/dot.png", IMREAD_GRAYSCALE);
//	Mat invX, invO, invD;
//	threshold(xStructure, invX, 100, 255, THRESH_BINARY_INV);
//	threshold(oStructure, invO, 100, 255, THRESH_BINARY_INV);
//	threshold(dStructure, invD, 100, 255, THRESH_BINARY_INV);
//
//	//-------------Find presences of structural elements in picture-------------
//	Mat xs, os, ds;
//	findSymbolLocs(outIm, invX, xs);
//	findSymbolLocs(outIm, invO, os);
//	findSymbolLocs(outIm, invD, ds);
//
//	Mat unInv, finIm;
//	bitwise_not(outIm, unInv);
//	cvtColor(unInv, finIm, COLOR_GRAY2RGB);
//
//	//-------------Assign all presences of 'X' a red color-------------
//	for (int i = 0; i < xs.rows; i++)
//	{
//		for (int j = 0; j < xs.cols; j++)
//		{
//			if (xs.at<uchar>(i, j) > 0)
//			{
//				finIm.at<uchar>(i, j * 3) = 0;
//				finIm.at<uchar>(i, j * 3 + 1) = 0;
//				finIm.at<uchar>(i, j * 3 + 2) = 255;
//			}
//		}
//	}
//
//	//-------------Assign all presences of 'O' a green color-------------
//	for (int i = 0; i < os.rows; i++)
//	{
//		for (int j = 0; j < os.cols; j++)
//		{
//			if (os.at<uchar>(i, j) > 0)
//			{
//				finIm.at<uchar>(i, j * 3) = 0;
//				finIm.at<uchar>(i, j * 3 + 1) = 255;
//				finIm.at<uchar>(i, j * 3 + 2) = 0;
//			}
//		}
//	}
//
//	//-------------Assign all presences of dots a purple color-------------
//	for (int i = 0; i < ds.rows; i++)
//	{
//		for (int j = 0; j < ds.cols; j++)
//		{
//			if (ds.at<uchar>(i, j) > 0)
//			{
//				finIm.at<uchar>(i, j * 3) = 255;
//				finIm.at<uchar>(i, j * 3 + 1) = 50;
//				finIm.at<uchar>(i, j * 3 + 2) = 255;
//			}
//		}
//	}
//
//	imshow("ERODED", finIm);
//	waitKey(0);
//
//	imwrite("C:/Users/hoodi/Desktop/Homework/Semester8/HCI575/HW2/HW2/HW2/hw2_files/p5_search_colored.png", finIm);
//}