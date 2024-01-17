#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void mask_setTo();
void mask_copyTo();
void time_inverse();

int main(void)
{
	mask_setTo();
	mask_copyTo();
	time_inverse();

	return 0;
}

void mask_setTo()
{
	Mat src = imread("lenna.bmp", IMREAD_COLOR);
	Mat mask = imread("mask_smile.bmp", IMREAD_GRAYSCALE);

	if (src.empty() || mask.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	src.setTo(Scalar(0, 255, 255), mask);

	imshow("src", src);
	imshow("mask", mask);

	waitKey();
	destroyAllWindows();
}

void mask_copyTo()
{
	Mat src = imread("airplane.bmp", IMREAD_COLOR);
	Mat mask = imread("mask_plane.bmp", IMREAD_GRAYSCALE);
	Mat dst = imread("field.bmp", IMREAD_COLOR);

	if (src.empty() || mask.empty() || dst.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	src.copyTo(dst, mask);

	//imshow("src", src);
	//imshow("mask", mask);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void time_inverse()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type());

	TickMeter tm;
	tm.start();

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) dst.at<uchar>(j, i) = 255 - src.at<uchar>(j, i);
	}

	tm.stop();
	cout << "Image inverse took " << tm.getTimeMilli() << "ms. " << endl;
}