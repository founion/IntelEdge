#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;
using namespace cv::dnn;

const String model = "opencv_face_detector_uint8.pb";                                  // �ټ��÷ο��� �Ʒõ� �� ���ϰ� ���� ������ ���.
const String config = "opencv_face_detector.pbtxt";

int main(void)
{
	VideoCapture cap(0);                                                               // ī�޶� ��ġ�� ��� cap�� ����.

	if (!cap.isOpened()) {                                                             // ī�޶� ���� �����ϴ� ��� ���α׷� ����.
		cerr << "Camera open failed!" << endl;
		return -1;
	}

	Net net = readNet(model, config);                                                  // �� ���ϰ� ���� ������ �̿��Ͽ� Net ��ü ����.

	if (net.empty()) {                                                                 // Net ��ü ���� �����ϴ� ��� ���α׷� ����.
		cerr << "Net open failed!" << endl;
		return -1;
	}

	Mat frame1, frame2;                                                                // ī�޶��� �� frame�� ������ Mat ��ü ����.
	while (true) {
		cap >> frame1 >> frame2;                                                       // ī�޶��� �� frame�� ����.

		if (frame1.empty() || frame2.empty()) break;                                   // frame�� ����� �޾� ���� ���ϸ� ����.

		Mat blob = blobFromImage(frame1, 1, Size(300, 300), Scalar(104, 177, 123));    // frame ������ �̿��Ͽ� 
		net.setInput(blob);                                                            // ��Ʈ��ũ �Է� ����� �����ϰ�,
		Mat res = net.forward();                                                       // ��Ʈ��ũ ���� ����� res ��Ŀ� ����.

		Mat detect(res.size[2], res.size[3], CV_32FC1, res.ptr<float>());              // 4������ res ����� 2���� ��� detect�� ��ȯ.

		for (int i = 0; i < detect.rows; i++) {
			float confidence = detect.at<float>(i, 2);
			if (confidence < 0.5) break;                                               // �ŷڵ� ���� 0.5���� ������ ����.

			int x1 = cvRound(detect.at<float>(i, 3) * frame1.cols);                    // �� ���� �簢�� ������ 
			int y1 = cvRound(detect.at<float>(i, 4) * frame1.rows);                    // ���� ��� ��ǥ (x1, y1)��
			int x2 = cvRound(detect.at<float>(i, 5) * frame1.cols);                    // ���� �ϴ� ��ǥ (x2, y2)��
			int y2 = cvRound(detect.at<float>(i, 6) * frame1.rows);                    // ����Ѵ�.

			rectangle(frame1, Rect(Point(x1, y1), Point(x2, y2)), Scalar(0, 255, 0));  // frame ���󿡼� �� ���� ������ ��� �簢�� �׸���.

			String label = format("Face: %4.3f", confidence);                          // �� �ŷڵ� ���.
			putText(frame1, label, Point(x1, y1 - 1), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0, 255, 0));


			imshow("frame1", frame1);                                                  // �� ���� ���� ���.

			Mat face;
			face = frame2(Rect(Point(x1, y1), Point(x2, y2))).clone();                 // ������ �� ������ ������ face ��ü�� ���� ����.

			Mat gray;
			cvtColor(face, gray, COLOR_BGR2GRAY);                                      // face ������ ���������� ���� �׷��̽����Ϸ� ��ȯ.

			Mat bin;
			threshold(gray, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);                 // �׷��̽������� ������ ����ȭ, OTSU �˰��� ���.

			Mat dst;
			morphologyEx(bin, dst, MORPH_OPEN, Mat());                                 // ����ȭ�� bin���� 3x3 ������ ���� ��Ҹ� �̿��Ͽ� ���� ������ �����ϰ� dst�� ����.

			imshow("frame2", dst);                                                     // �������� ���� ������ ������ ���� ���.
		}

		if (waitKey(1) == 27) break;                                                   // esc�� ������ ����.
	}

	return 0;
}
