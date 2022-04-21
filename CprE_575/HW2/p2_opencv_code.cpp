//#include <opencv2/opencv.hpp>
//
//using namespace cv;
//
//int main()
//{
//
//	//Read, invert, and show the original pic
//	Mat initPic = imread("C:/Users/hoodi/Desktop/Homework/Semester8/HCI575/HW2/HW2/HW2/hw2_files/p2_search.png", IMREAD_GRAYSCALE);
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
//
//	//-------------Find Vertical and Horizontal Projection-------------
//	std::vector<int> vertProj = std::vector<int>(outIm.rows);
//	std::vector<int> horzProj = std::vector<int>(outIm.cols);
//
//	Mat justGrid = Mat::zeros(outIm.rows, outIm.cols, outIm.type());
//	Mat justShape = Mat::zeros(outIm.rows, outIm.cols, outIm.type());
//
//	for (int i = 0; i < outIm.rows; i++)
//	{
//		for (int coord = 0; coord < outIm.cols; coord++)
//		{
//			if (outIm.at<uchar>(i, coord) > 0)
//			{
//				vertProj.at(i) += 1;
//			}
//		}
//	}
//
//
//	for (int i = 0; i < outIm.cols; i++)
//	{
//		for (int coord = 0; coord < outIm.rows; coord++)
//		{
//			if (outIm.at<uchar>(coord, i) > 0)
//			{
//				horzProj.at(i) += 1;
//			}
//		}
//	}
//
//	//-------------Assign values for the grid-------------
//	for (int i = 0; i < vertProj.size(); i++)
//	{
//		if (vertProj.at(i) == outIm.cols)
//		{
//			for (int coord = 0; coord < outIm.cols; coord++)
//			{
//				justGrid.at<uchar>(i, coord) = 255;
//			}
//		}
//	}
//
//	for (int i = 0; i < horzProj.size(); i++)
//	{
//		if (horzProj.at(i) == outIm.rows)
//		{
//			for (int coord = 0; coord < outIm.rows; coord++)
//			{
//				justGrid.at<uchar>(coord, i) = 255;
//			}
//		}
//	}
//
//	imshow("The Grid", justGrid);
//
//	//-------------Compare grid to original, assign shapes image with inverse-------------
//	uchar compPix;
//	for (int i = 0; i < justGrid.rows; i++)
//	{
//		for (int j = 0; j < justGrid.cols; j++)
//		{
//
//			compPix = outIm.at<uchar>(i, j);
//
//			if (justGrid.at<uchar>(i, j) != compPix)
//			{
//				justShape.at<uchar>(i, j) = compPix;
//			}
//		}
//	}
//
//	imshow("The Shapes", justShape);
//
//	waitKey(0);
//
//	//-------------Revert images-------------
//	Mat finGrid;
//	bitwise_not(justGrid, finGrid);
//
//	Mat finShape;
//	bitwise_not(justShape, finShape);
//
//	//-------------Write images-------------
//	imwrite("p2_search_grid.png", finGrid);
//	imwrite("p2_search_shape.png", finShape);
//}