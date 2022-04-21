//#include <opencv2/opencv.hpp>
//
//using namespace cv;
//
//void countFilled(Mat& img, std::vector<Point>& pos)
//{
//	pos.clear();
//	for (int rows = 0; rows < img.rows; rows++)
//	{
//		for (int cols = 0; cols < img.cols; cols++)
//		{
//			if (img.at<uchar>(rows, cols) > 0)
//				pos.push_back(Point(rows, cols));
//		}
//	}
//}
//
//bool compareColPos(Point p1, Point p2)
//{
//	return (p1.x < p2.x);
//}
//
//void placeInColor(Mat& origIm, Mat refIm, Vec3i col)
//{
//	for (int i = 0; i < refIm.rows; i++)
//	{
//		for (int j = 0; j < refIm.cols; j++)
//		{
//			if (refIm.at<uchar>(i, j) > 0)
//			{
//				origIm.at<uchar>(i, j * 3) = col[0];
//				origIm.at<uchar>(i, j * 3 + 1) = col[1];
//				origIm.at<uchar>(i, j * 3 + 2) = col[2];
//			}
//		}
//	}
//}
//
//int main()
//{
//
//	//Read, invert, and show the original pic
//	Mat initPic = imread("C:/Users/hoodi/Desktop/Homework/Semester8/HCI575/HW2/HW2/HW2/hw2_files/p9_search.png", IMREAD_GRAYSCALE);
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
//
//	//-------------Init pattern recognition loop-------------
//	bool prevBorder = true;
//	int startPos = 0;
//	int endPos = 0;
//
//	Mat resIm = Mat(justGrid);
//	Mat resImNot;
//	bitwise_not(resIm, resImNot);
//	Mat resImCol;
//	cvtColor(resImNot, resImCol, COLOR_GRAY2RGB);
//
//	//Iterate through grid rows
//	for (int i = 0; i < justGrid.rows; i++)
//	{
//		//If the previous row was a border and the current row isn't...
//		//Mark it.
//		if (prevBorder && vertProj.at(i) != justGrid.cols)
//		{
//			prevBorder = false;
//			startPos = i;
//		}
//
//		//If the previous row wasn't a border and the current row is...
//		//Extract the row of symbols just passed
//		else if (!prevBorder && vertProj.at(i) == justGrid.cols)
//		{
//			endPos = i;
//			Mat row = justShape(Range(startPos, endPos), Range(0, justShape.cols - 1));
//
//			prevBorder = true;
//			int patternSize = 0;
//			Mat thisStruct;
//			std::vector<Point> positions = std::vector<Point>();
//
//			//Find pattern in row
//			for (int j = 0; j < justGrid.cols; j++)
//			{
//
//				//If the current column isn't a border but the previous one was...
//				//Take note.
//				if (prevBorder && horzProj.at(j) != justGrid.rows)
//				{
//					prevBorder = false;
//				}
//
//				//If the current column is a border and the previous one wasn't...
//				//Check for a pattern
//				else if (!prevBorder && horzProj.at(j) == justGrid.rows)
//				{
//					patternSize++;
//					prevBorder = true;
//
//					//A single symbol isn't indicative of a pattern
//					if (patternSize > 1)
//					{
//						Mat structElem = row(Range(0, row.rows - 1), Range(0, j));
//						Mat structElemFlip;
//						flip(structElem, structElemFlip, -1);
//						Mat eRowde, resRow;
//						erode(row, eRowde, structElem);
//						
//						countFilled(eRowde, positions);
//
//						if (positions.size() < 2)
//							break;
//
//						thisStruct = structElem;
//					}
//				}
//			}
//
//			//Get the flipped structure (for dilation.  Still unclear as to 
//			//why this has to be done?)
//			Mat thisStructFlipped;
//			flip(thisStruct, thisStructFlipped, -1);
//
//			//Get the pattern locations and isolate to the current row
//			Mat testIm;
//			erode(justShape, testIm, thisStruct);
//
//			testIm(Range(0, startPos), Range(0, testIm.cols - 1)) = 0;
//			testIm(Range(endPos, testIm.rows - 1), Range(0, testIm.cols - 1)) = 0;
//
//			//Count and sort the dilation points in the picture
//			countFilled(testIm, positions);
//			std::sort(positions.begin(), positions.end(), compareColPos);
//
//			//For each point (in order)
//			for (int pnt = 0; pnt < positions.size(); pnt++)
//			{
//				Mat tmpMat = Mat::zeros(justGrid.rows, justGrid.cols, justGrid.type());
//				Point curPt = positions.at(pnt);
//				tmpMat.at<uchar>(curPt.x, curPt.y) = 255;
//
//				Mat dilMat;
//				dilate(tmpMat, dilMat, thisStructFlipped);
//
//				if(pnt % 3 == 0)
//					placeInColor(resImCol, dilMat, Vec3i(0, 0, 255));
//				else if (pnt % 3 == 1)
//					placeInColor(resImCol, dilMat, Vec3i(255, 0, 0));
//				else
//					placeInColor(resImCol, dilMat, Vec3i(0, 255, 0));
//
//			}
//
//			Mat patternPos;
//			erode(justShape, patternPos, thisStruct);
//
//			prevBorder = true;
//		}
//	}
//
//	imshow("currentResult", resImCol);
//	waitKey(0);
//
//	imwrite("C:/Users/hoodi/Desktop/Homework/Semester8/HCI575/HW2/HW2/HW2/hw2_files/p9_fancy.png", resImCol);
//}