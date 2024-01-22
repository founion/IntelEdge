#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void erode_dilate();
void open_close();

int main(void)
{
	erode_dilate();  // 이진 영상의 침식과 팽창
	open_close();    // 이진 영상의 열기와 닫기

	return 0;
}

void erode_dilate()
{
	Mat src = imread("milkdrop.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);

	Mat dst1, dst2;
	erode(bin, dst1, Mat());
	dilate(bin, dst2, Mat());

	imshow("src", src);
	imshow("bin", bin);
	imshow("erode", dst1);
	imshow("dilate", dst2);

	waitKey();
	destroyAllWindows();
}

void open_close()
{
	Mat src = imread("milkdrop.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);

	Mat dst1, dst2, dst3;
	morphologyEx(bin, dst1, MORPH_OPEN, Mat());
	morphologyEx(bin, dst2, MORPH_CLOSE, Mat());
	morphologyEx(bin, dst3, MORPH_GRADIENT, Mat());

	imshow("src", src);
	imshow("bin", bin);
	imshow("opening", dst1);
	imshow("closing", dst2);
	imshow("gradient", dst3);

	waitKey();
	destroyAllWindows();
}