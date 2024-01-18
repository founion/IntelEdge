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
	// 아래의 코드를 추가하면 imgCopy창(img창과는 별개)에서 사각형의 범위를 시각적으로 확인할 수 있다.
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

// Q. LBUTTONDOWN 부터 LBUTTONUP 직전 까지만 사각형의 범위를 시각적으로 볼 수 있게 하려면 어떻게 해야 하는지 궁금합니다.