#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void color_inverse();
void color_grayscale();
void color_split();

int main(void)
{
	//color_inverse();    // 컬러 영상의 픽셀 값 반전
	//color_grayscale();  // 컬러 영상을 그레이스케일 영상으로 변환
	color_split();      // BGR 컬러 영상의 채널 나누기

	return 0;
}

void color_inverse()
{
	Mat src = imread("butterfly.jpg", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type());

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			Vec3b& p1 = src.at<Vec3b>(j, i);
			Vec3b& p2 = dst.at<Vec3b>(j, i);

			p2[0] = 255 - p1[0];
			p2[1] = 255 - p1[1];
			p2[2] = 255 - p1[2];
		}
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void color_grayscale()
{
	Mat src = imread("butterfly.jpg", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst;
	cvtColor(src, dst, COLOR_BGR2GRAY);

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void color_split()
{
	Mat src = imread("candies.png", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	vector<Mat> bgr_planes;
	split(src, bgr_planes);
	
	imshow("src", src);
	imshow("B_plane", bgr_planes[0]);
	imshow("G_plane", bgr_planes[1]);
	imshow("R_plane", bgr_planes[2]);

	waitKey();
	destroyAllWindows();
}