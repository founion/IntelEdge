#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void decode_qrcode();

int main(void)
{
	decode_qrcode();  // QR ÄÚµå °ËÃâ ¹× ÇØ¼®

	return 0;
}

void decode_qrcode()
{
	VideoCapture cap(0);

	if (!cap.isOpened()) {
		cerr << "Camera open failed!" << endl;
		return;
	}

	QRCodeDetector detector;

	Mat frame;
	while (true) {
		cap >> frame;

		if (frame.empty()) {
			cerr << "Frame load failed!" << endl;
			break;
		}

		vector<Point> points;
		String info = detector.detectAndDecode(frame, points);

		if (!info.empty()) {
			polylines(frame, points, true, Scalar(0, 0, 255), 2);
			putText(frame, info, Point(10, 30), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 255));
			cout << "url: " << info << endl;
		}

		imshow("frame", frame);
		if (waitKey(10) == 27) break;
	}
}
