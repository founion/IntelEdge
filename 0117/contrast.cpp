#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void contrast1();
void contrast2();

int main(void)
{
	contrast1();  // 기본적인 영상의 명암비 증가 예제
	contrast2();  // 효과적인 영상의 명암비 조절 방법

	return 0;
}

void contrast1()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	float s = 2.f;
	Mat dst = s * src;

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void contrast2()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	float alpha = 1.f;
	Mat dst = src + (src - 128) * alpha;

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}