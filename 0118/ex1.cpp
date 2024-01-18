#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

Mat img;
Point ptOld1, ptOld2;
void on_mouse(int event, int x, int y, int flags, void*);

int main(void)
{
	img = imread("lenna.bmp");

	if (img.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	namedWindow("img");
	setMouseCallback("img", on_mouse);

	imshow("img", img);

	waitKey();
	destroyAllWindows();
	
	return 0;
}

void on_mouse(int event, int x, int y, int flags, void*)
{
	Mat imgCopy = img.clone();
	switch (event) {
	case EVENT_LBUTTONDOWN:
		ptOld1 = Point(x, y);
		break;
	case EVENT_LBUTTONUP:
	{
		ptOld2 = Point(x, y);
		rectangle(imgCopy, ptOld1, ptOld2, Scalar(0), 1);
				
		Rect roi(ptOld1, ptOld2);
		Mat captured_img = img(roi).clone();
		imwrite("captured_image.bmp", captured_img);
		imshow("captured_image", captured_img);
	}
		break;
	// �Ʒ��� �ڵ带 �߰��ϸ� imgCopyâ(imgâ���� ����)���� �簢���� ������ �ð������� Ȯ���� �� �ִ�.
	/*case EVENT_MOUSEMOVE:
		if (flags & EVENT_FLAG_LBUTTON) {
			ptOld2 = Point(x, y);
			rectangle(imgCopy, ptOld1, ptOld2, Scalar(0), 1);
			imshow("imgCopy", imgCopy);
		}
		break;*/
	default:break;
	}
}

// Q. LBUTTONDOWN ���� LBUTTONUP ���� ������ �簢���� ������ �ð������� �� �� �ְ� �Ϸ��� ��� �ؾ� �ϴ��� �ñ��մϴ�.