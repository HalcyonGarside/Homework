#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{

	//Read, invert, and show the original pic
	Mat initPic = imread("C:/Users/hoodi/Desktop/Homework/Semester8/HCI575/HW2/HW2/HW2/hw2_files/p3_search.png", IMREAD_GRAYSCALE);
	Mat picBin, bi;
	threshold(initPic, picBin, 100, 255, THRESH_BINARY_INV);

	imshow("The Original", picBin);


	//-------------Parse just the grid-------------
	int rst = 0;
	int rfin = 0;

	int cst = 0;
	int cfin = 0;

	for (int i = 0; i < picBin.rows; i++)
	{
		for (int coord = 0; coord < picBin.cols; coord++)
		{
			if (picBin.at<uchar>(i, coord) > 0)
			{
				if (rst == 0) rst = i;
				else rfin = i;
			}
		}
	}


	for (int i = 0; i < picBin.cols; i++)
	{
		for (int coord = 0; coord < picBin.rows; coord++)
		{
			if (picBin.at<uchar>(coord, i) > 0)
			{
				if (cst == 0) cst = i;
				else cfin = i;
			}
		}
	}

	Mat outIm = picBin(Range(rst, rfin), Range(cst, cfin));

	Mat gridFin, gridCol;
	bitwise_not(outIm, gridFin);
	cvtColor(gridFin, gridCol, COLOR_GRAY2RGB);

	imshow("The Grid But Proper", gridCol);

	for (int i = 1; i < gridCol.rows; i++)
	{
		for (int j = 0; j < gridCol.cols; j++)
		{
			Vec3i col = Vec3i(gridCol.at<uchar>(i, j * 3), gridCol.at<uchar>(i, j * 3 + 1), gridCol.at<uchar>(i, j * 3 + 2));

			if (col(0) == 255 && col(1) == 255 && col(2) == 255)
			{
				Vec3i colAbove = Vec3i(gridCol.at<uchar>(i - 1, j * 3), gridCol.at<uchar>(i - 1, j * 3 + 1), gridCol.at<uchar>(i - 1, j * 3 + 2));
				Vec3i colLeft = Vec3i(gridCol.at<uchar>(i, (j - 1) * 3), gridCol.at<uchar>(i, (j - 1) * 3 + 1), gridCol.at<uchar>(i, (j - 1) * 3 + 2));

				if ((colLeft[0] == 0 && colLeft[1] == 0 && colLeft[2] == 0))
				{
					if ((colAbove[0] == 0 && colAbove[1] == 0 && colAbove[2] == 0))
					{
						gridCol.at<uchar>(i, j * 3) = rand() % 255 + 1;
						gridCol.at<uchar>(i, j * 3 + 1) = rand() % 255 + 1;
						gridCol.at<uchar>(i, j * 3 + 2) = rand() % 255 + 1;
						continue;
					}
					else
					{
						gridCol.at<uchar>(i, j * 3) = colAbove[0];
						gridCol.at<uchar>(i, j * 3 + 1) = colAbove[1];
						gridCol.at<uchar>(i, j * 3 + 2) = colAbove[2];
					}
				}
				else
				{
					gridCol.at<uchar>(i, j * 3) = colLeft[0];
					gridCol.at<uchar>(i, j * 3 + 1) = colLeft[1];
					gridCol.at<uchar>(i, j * 3 + 2) = colLeft[2];
				}
			}
		}
	}

	imshow("colored grid", gridCol);

	waitKey(0);

	imwrite("C:/Users/hoodi/Desktop/Homework/Semester8/HCI575/HW2/HW2/HW2/hw2_files/p3_search_colored.png", gridCol);
}