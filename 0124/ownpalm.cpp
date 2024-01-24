#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void video_capture();

int main(void)
{
	video_capture();

	return 0;
}

void video_capture()
{
	VideoCapture cap(0);

	if (!cap.isOpened()) {
		cerr << "Camera open failed!" << endl;
		exit(0);
	}

	Mat frame;
	while (true) {
		cap >> frame;

		if (frame.empty()) break;

		imshow("frame", frame);

		int c = waitKeyEx(10);
		if (c == 32) imwrite("palm.bmp", frame);  // 스페이스 누르면 사진 캡쳐

		Mat img = imread("palm.bmp", IMREAD_GRAYSCALE);  // 저장한 사진 불러오기

		Mat bin;
		threshold(img, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);  // 저장한 사진 이진화

		vector<vector<Point>> contours;
		findContours(bin, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);  // 외곽선 찾기

		Mat dst;
		cvtColor(bin, dst, COLOR_GRAY2BGR);  // 외곽선의 색깔을 구분하기 위해 이진화 영상 컬러영상으로 변환
		
		for (int i = 0; i < contours.size(); i++) {
			Scalar c(0, 0, 255);  // 외곽선 색 red
			drawContours(dst, contours, i, c, -1);  // 외곽선 내부 색 채우기
		}

		imshow("bin", dst);

		if (c == 27) break;  // esc 누르면 종료
	}

	destroyAllWindows();
}