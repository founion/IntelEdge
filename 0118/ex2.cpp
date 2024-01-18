#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat frame;
Point ptOld1, ptOld2;

void camera_in_video_out();
void on_mouse(int event, int x, int y, int flags, void*);

int main(void)
{
	camera_in_video_out();

	return 0;
}

void camera_in_video_out()
{
	VideoCapture cap(0);

	if (!cap.isOpened()) {
		cerr << "Camera open failed!" << endl;
		return;
	}

	int w = cvRound(cap.get(CAP_PROP_FRAME_WIDTH));
	int h = cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));
	double fps = cap.get(CAP_PROP_FPS);

	int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');
	int delay = cvRound(1000 / fps);

	VideoWriter outputVideo("output.avi", fourcc, fps, Size(w, h));

	if (!outputVideo.isOpened()) {
		cout << "File open failed!" << endl;
		return;
	}

	Mat captured;
	while (true) {
		cap >> frame;
		if (frame.empty())
			break;

		imshow("frame", frame);
		setMouseCallback("frame", on_mouse);
		if (waitKey(delay) == 27)
			break;

		outputVideo << frame;		
	}

	destroyAllWindows();
}

void on_mouse(int event, int x, int y, int flags, void*)
{
	switch (event) {
	case EVENT_LBUTTONDOWN:
		ptOld1 = Point(x, y);
		break;
	case EVENT_LBUTTONUP:
	{
		ptOld2 = Point(x, y);
		rectangle(frame, ptOld1, ptOld2, Scalar(0), 1);
		imshow("frame", frame);

		Rect roi(ptOld1, ptOld2);
		Mat captured_image = frame(roi).clone();
		imwrite("captured_image.bmp", captured_image);
		imshow("captured_image", captured_image);
	}
	break;
	/*case EVENT_MOUSEMOVE:
		if (flags & EVENT_FLAG_LBUTTON) {
			ptOld2 = Point(x, y);
			Mat imgCopy = frame.clone();
			rectangle(imgCopy, ptOld1, ptOld2, Scalar(0), 1);
			imshow("img", imgCopy);
		}
		break;*/
	default:break;
	}
}

// Q. LBUTTONDOWN 부터 LBUTTONUP 직전 까지만 사각형의 범위를 시각적으로 볼 수 있게 하려면 어떻게 해야 하는지 궁금합니다.