#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void contrast1();
void contrast2();

int main(void)
{
	contrast1();  // �⺻���� ������ ��Ϻ� ���� ����
	contrast2();  // ȿ������ ������ ��Ϻ� ���� ���

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