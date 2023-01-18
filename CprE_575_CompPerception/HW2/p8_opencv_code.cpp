#include <opencv2/opencv.hpp>

using namespace cv;

//-------------Find the locations of 'X' in the picture-------------
void separateSymbolLocs(Mat& origIm, Mat& outMat, Mat structElem, Mat replElem)
{
	Mat flippedElem;
	flip(replElem, flippedElem, -1);
	Mat eroded, symbols;
	erode(origIm, eroded, structElem);
	dilate(eroded, outMat, flippedElem);

	imshow("Y struct", eroded);
	waitKey(0);

	for (int i = 0; i < outMat.rows; i++)
	{
		for (int j = 0; j < outMat.cols; j++)
		{
			if (outMat.at<uchar>(i, j) > 0)
			{
				origIm.at<uchar>(i, j) = 0;
			}
		}
	}

	//imshow("Y struct", outMat);
	//waitKey(0);
}

void placeInColor(Mat& origIm, Mat refIm, Vec3i col)
{
	for (int i = 0; i < refIm.rows; i++)
	{
		for (int j = 0; j < refIm.cols; j++)
		{
			if (refIm.at<uchar>(i, j) > 0)
			{
				origIm.at<uchar>(i, j * 3) = col[0];
				origIm.at<uchar>(i, j * 3 + 1) = col[1];
				origIm.at<uchar>(i, j * 3 + 2) = col[2];
			}
		}
	}
}

int main()
{

	//Read, invert, and show the original pic
	Mat initPic = imread("C:/Users/hoodi/Desktop/Homework/Semester8/HCI575/HW2/HW2/HW2/hw2_files/p8_search.png", IMREAD_GRAYSCALE);
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


	//-------------Find Vertical and Horizontal Projection-------------
	std::vector<int> vertProj = std::vector<int>(outIm.rows);
	std::vector<int> horzProj = std::vector<int>(outIm.cols);

	Mat justGrid = Mat::zeros(outIm.rows, outIm.cols, outIm.type());
	Mat justShape = Mat::zeros(outIm.rows, outIm.cols, outIm.type());

	for (int i = 0; i < outIm.rows; i++)
	{
		for (int coord = 0; coord < outIm.cols; coord++)
		{
			if (outIm.at<uchar>(i, coord) > 0)
			{
				vertProj.at(i) += 1;
			}
		}
	}


	for (int i = 0; i < outIm.cols; i++)
	{
		for (int coord = 0; coord < outIm.rows; coord++)
		{
			if (outIm.at<uchar>(coord, i) > 0)
			{
				horzProj.at(i) += 1;
			}
		}
	}

	//-------------Assign values for the grid-------------
	for (int i = 0; i < vertProj.size(); i++)
	{
		if (vertProj.at(i) == outIm.cols)
		{
			for (int coord = 0; coord < outIm.cols; coord++)
			{
				justGrid.at<uchar>(i, coord) = 255;
			}
		}
	}

	for (int i = 0; i < horzProj.size(); i++)
	{
		if (horzProj.at(i) == outIm.rows)
		{
			for (int coord = 0; coord < outIm.rows; coord++)
			{
				justGrid.at<uchar>(coord, i) = 255;
			}
		}
	}

	imshow("The Grid", justGrid);

	//-------------Compare grid to original, assign shapes image with inverse-------------
	uchar compPix;
	for (int i = 0; i < justGrid.rows; i++)
	{
		for (int j = 0; j < justGrid.cols; j++)
		{

			compPix = outIm.at<uchar>(i, j);

			if (justGrid.at<uchar>(i, j) != compPix)
			{
				justShape.at<uchar>(i, j) = compPix;
			}
		}
	}

	imshow("The Shapes", justShape);

	//-------------Get the structuring elements-------------
	Mat xStructure = imread("C:/Users/hoodi/Desktop/Homework/Semester8/HCI575/HW2/HW2/HW2/Symbol_Cutouts/X.png", IMREAD_GRAYSCALE);
	Mat yStructure = imread("C:/Users/hoodi/Desktop/Homework/Semester8/HCI575/HW2/HW2/HW2/Symbol_Cutouts/Fancy_Y.png", IMREAD_GRAYSCALE);
	Mat oStructure = imread("C:/Users/hoodi/Desktop/Homework/Semester8/HCI575/HW2/HW2/HW2/Symbol_Cutouts/O.png", IMREAD_GRAYSCALE);
	Mat cStructure = imread("C:/Users/hoodi/Desktop/Homework/Semester8/HCI575/HW2/HW2/HW2/Symbol_Cutouts/curly.png", IMREAD_GRAYSCALE);
	Mat dStructure = imread("C:/Users/hoodi/Desktop/Homework/Semester8/HCI575/HW2/HW2/HW2/Symbol_Cutouts/dot.png", IMREAD_GRAYSCALE);
	Mat fhStructure = imread("C:/Users/hoodi/Desktop/Homework/Semester8/HCI575/HW2/HW2/HW2/Symbol_Cutouts/H.png", IMREAD_GRAYSCALE);
	Mat bStructure = imread("C:/Users/hoodi/Desktop/Homework/Semester8/HCI575/HW2/HW2/HW2/Symbol_Cutouts/backslash.png", IMREAD_GRAYSCALE);
	Mat nStructure = imread("C:/Users/hoodi/Desktop/Homework/Semester8/HCI575/HW2/HW2/HW2/Symbol_Cutouts/N.png", IMREAD_GRAYSCALE);
	Mat hStructure = imread("C:/Users/hoodi/Desktop/Homework/Semester8/HCI575/HW2/HW2/HW2/Symbol_Cutouts/horizontal.png", IMREAD_GRAYSCALE);
	Mat sixStructure = imread("C:/Users/hoodi/Desktop/Homework/Semester8/HCI575/HW2/HW2/HW2/Symbol_Cutouts/six.png", IMREAD_GRAYSCALE);
	Mat pStructure = imread("C:/Users/hoodi/Desktop/Homework/Semester8/HCI575/HW2/HW2/HW2/Symbol_Cutouts/plus.png", IMREAD_GRAYSCALE);
	Mat starStructure = imread("C:/Users/hoodi/Desktop/Homework/Semester8/HCI575/HW2/HW2/HW2/Symbol_Cutouts/star.png", IMREAD_GRAYSCALE);
	Mat sStructure = imread("C:/Users/hoodi/Desktop/Homework/Semester8/HCI575/HW2/HW2/HW2/Symbol_Cutouts/slash.png", IMREAD_GRAYSCALE);
	Mat eStructure = imread("C:/Users/hoodi/Desktop/Homework/Semester8/HCI575/HW2/HW2/HW2/Symbol_Cutouts/surprise.png", IMREAD_GRAYSCALE);
	Mat vStructure = imread("C:/Users/hoodi/Desktop/Homework/Semester8/HCI575/HW2/HW2/HW2/Symbol_Cutouts/vertical.png", IMREAD_GRAYSCALE);
	Mat uStructure = imread("C:/Users/hoodi/Desktop/Homework/Semester8/HCI575/HW2/HW2/HW2/Symbol_Cutouts/U.png", IMREAD_GRAYSCALE);
	Mat invX, invY, invO, invC, invD, invFH, invB, invN, invH, inv6, invP, invStar, invS, invE, invV, invU;
	threshold(xStructure, invX, 100, 255, THRESH_BINARY_INV);
	threshold(yStructure, invY, 100, 255, THRESH_BINARY_INV);
	threshold(oStructure, invO, 100, 255, THRESH_BINARY_INV);
	threshold(cStructure, invC, 100, 255, THRESH_BINARY_INV);
	threshold(dStructure, invD, 100, 255, THRESH_BINARY_INV);
	threshold(fhStructure, invFH, 100, 255, THRESH_BINARY_INV);
	threshold(bStructure, invB, 100, 255, THRESH_BINARY_INV);
	threshold(nStructure, invN, 100, 255, THRESH_BINARY_INV);
	threshold(hStructure, invH, 100, 255, THRESH_BINARY_INV);
	threshold(sixStructure, inv6, 100, 255, THRESH_BINARY_INV);
	threshold(pStructure, invP, 100, 255, THRESH_BINARY_INV);
	threshold(starStructure, invStar, 100, 255, THRESH_BINARY_INV);
	threshold(sStructure, invS, 100, 255, THRESH_BINARY_INV);
	threshold(eStructure, invE, 100, 255, THRESH_BINARY_INV);
	threshold(vStructure, invV, 100, 255, THRESH_BINARY_INV);
	threshold(uStructure, invU, 100, 255, THRESH_BINARY_INV);



	//-------------Find presences of structural elements in picture-------------
	Mat xs, os, ds, bs, hs, ps, ss, vs;
	separateSymbolLocs(justShape, xs, invX, invY);
	separateSymbolLocs(justShape, os, invO, invC);
	separateSymbolLocs(justShape, ds, invD, invFH);
	separateSymbolLocs(justShape, bs, invB, invN);
	separateSymbolLocs(justShape, ps, invP, inv6);
	separateSymbolLocs(justShape, ss, invS, invE);
	separateSymbolLocs(justShape, hs, invH, invStar);
	separateSymbolLocs(justShape, vs, invV, invU);

	Mat unInv, finIm;
	bitwise_not(justGrid, unInv);
	cvtColor(unInv, finIm, COLOR_GRAY2RGB);

	//-------------Place colored images in proper locations on grid-------------
	placeInColor(finIm, xs, Vec3i(0, 0, 0));
	placeInColor(finIm, os, Vec3i(0, 0, 0));
	placeInColor(finIm, ds, Vec3i(0, 0, 0));
	placeInColor(finIm, bs, Vec3i(0, 0, 0));
	placeInColor(finIm, hs, Vec3i(0, 0, 0));
	placeInColor(finIm, ps, Vec3i(0, 0, 0));
	placeInColor(finIm, ss, Vec3i(0, 0, 0));
	placeInColor(finIm, vs, Vec3i(0, 0, 0));

	imshow("ERODED", finIm);
	waitKey(0);

	imwrite("C:/Users/hoodi/Desktop/Homework/Semester8/HCI575/HW2/HW2/HW2/hw2_files/p8_fancy.png", finIm);
}