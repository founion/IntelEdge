#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void brightness1();
void brightness2();
void brightness3();
void brightness4();
void on_brightness(int pos, void* userdata);

int main(void)
{
	brightness1();  // 영상의 밝기를 100만큼 증가하기
	brightness2();  // 포화 연산을 고려하지 않은 영상의 밝기 증가 직접 구현
	brightness3();  // 포화 연산을 고려한 영상의 밝기 증가 직접 구현
	brightness4();  // 트랙바를 이용한 영상의 밝기 조절하기

	return 0;
}

void brightness1()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst = src + 100;

	imshow("src", src);
	imshow("dst", dst);
	
	waitKey();
	destroyAllWindows();
}

void brightness2()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type());

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) dst.at<uchar>(j, i) = src.at<uchar>(j, i) + 100;
	}

	imshow("src", src);
	imshow("dst", dst);
	
	waitKey();
	destroyAllWindows();
}

void brightness3()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type());

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) dst.at<uchar>(j, i) = saturate_cast<uchar>(src.at<uchar>(j, i) + 100);
	}

	imshow("src", src);
	imshow("dst", dst);
	
	waitKey();
	destroyAllWindows();
}

void brightness4()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	namedWindow("dst");
	createTrackbar("Brightness", "dst", 0, 100, on_brightness, (void*)&src);
	on_brightness(0, (void*)&src);

	waitKey();
	destroyAllWindows();
}

void on_brightness(int pos, void* userdata)
{
	Mat src = *(Mat*)userdata;
	Mat dst = src + pos;

	imshow("dst", dst);
}