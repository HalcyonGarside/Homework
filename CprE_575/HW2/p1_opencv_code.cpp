#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	Mat initPic = imread("C:/Users/hoodi/Desktop/Homework/Semester8/HCI575/HW2/HW2/HW2/hw2_files/p1_search.png", IMREAD_GRAYSCALE);
	Mat picBin, bi;
	threshold(initPic, picBin, 100, 255, THRESH_BINARY_INV);

	printf("%d, %d\n", picBin.rows, picBin.cols);
	imshow("OUT IMAGE!!", picBin);
	waitKey(0);

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
				//circle(picBin, Point(i, coord), 1, Vec3i(255, 255, 0));
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
				//circle(picBin, Point(coord, i), 1, Vec3i(255, 0, 255));
			}
		}
	}

	printf("%d, %d\n", cst, cfin);

	printf(
		"ImSize: %d, %d",
		picBin.rows,
		picBin.cols
	);

	imshow("DEBUG", picBin);

	Mat outIm = picBin(Range(rst, rfin), Range(cst, cfin));

	imshow("OUT", outIm);

	Mat finIm;
	bitwise_not(outIm, finIm);
	
	imwrite("C:/Users/hoodi/Desktop/Homework/Semester8/HCI575/HW2/HW2/HW2/hw2_files/p1_search_opencv.png", finIm);

	waitKey(0);
}