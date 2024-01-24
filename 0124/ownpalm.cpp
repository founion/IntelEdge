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
		if (c == 32) imwrite("palm.bmp", frame);  // �����̽� ������ ���� ĸ��

		Mat img = imread("palm.bmp", IMREAD_GRAYSCALE);  // ������ ���� �ҷ�����

		Mat bin;
		threshold(img, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);  // ������ ���� ����ȭ

		vector<vector<Point>> contours;
		findContours(bin, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);  // �ܰ��� ã��

		Mat dst;
		cvtColor(bin, dst, COLOR_GRAY2BGR);  // �ܰ����� ������ �����ϱ� ���� ����ȭ ���� �÷��������� ��ȯ
		
		for (int i = 0; i < contours.size(); i++) {
			Scalar c(0, 0, 255);  // �ܰ��� �� red
			drawContours(dst, contours, i, c, -1);  // �ܰ��� ���� �� ä���
		}

		imshow("bin", dst);

		if (c == 27) break;  // esc ������ ����
	}

	destroyAllWindows();
}