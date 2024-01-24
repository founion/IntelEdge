#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void video();

int main(void)
{
	video();  // video �Լ� ����

	return 0;
}

void video()
{
	VideoCapture cap(0);  // VideoCapture Ŭ������ ����Ͽ� ī�޶� ����

	if (!cap.isOpened()) {  // ī�޶� ���¿� ���� ��
		cerr << "Camera open failed!" << endl;
		return;
	}

	Mat frame1, frame2, frame3;  // 3���� ȭ���� �����̹Ƿ� Mat Ŭ���� ��ü 3�� ����
	while (true) {
		cap >> frame1 >> frame2 >> frame3;  // frame ��ü�� cap�� �Է�

		if (frame1.empty() || frame2.empty() || frame3.empty()) break;  // �Է� ���� ��
		
		cvtColor(frame1, frame2, COLOR_BGR2GRAY);  // frame2�� frame1 ������ �׷��̽����Ϸ� ��ȯ
		threshold(frame2, frame3, 0, 255, THRESH_BINARY | THRESH_OTSU);  // frame3�� frame2�� ����ȭ(otsu����� ���, �ڵ����� �Ӱ谪 �����ϵ��� �Ͽ���)

		imshow("frame1", frame1);  // frame1 : �Ϲ� ����
		imshow("frame2", frame2);  // frame2 : �׷��̽����Ϸ� ��ȯ�� ����
		imshow("frame3", frame3);  // frame3 : �׷��̽����� ������ ����ȭ�� ����

		if (waitKey(10) == 27) break;  // esc ������ ����
	}

	destroyAllWindows();
}