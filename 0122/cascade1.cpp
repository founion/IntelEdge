#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void detect_face();
void detect_eyes();

int main(void)
{
	detect_face();  // 동영상에서 얼굴 검출
	detect_eyes();  // 동영상에서 눈 검출

	return 0;
}

void detect_face()
{
	VideoCapture cap(0);

	if (!cap.isOpened()) {
		cerr << "Camera open failed!" << endl;
		return;
	}

	CascadeClassifier classifier("haarcascade_frontalface_default.xml");

	if (classifier.empty()) {
		cerr << "XML load failed!" << endl;
		return;
	}

	Mat frame;
	while(true){
		cap >> frame;
		if (frame.empty()) break;

		vector<Rect> faces;
		classifier.detectMultiScale(frame, faces);

		for (Rect rc : faces) rectangle(frame, rc, Scalar(255, 0, 255), 2);

		imshow("frame", frame);

		if (waitKey(10) == 27) break;
	}
}

void detect_eyes()
{
	VideoCapture cap(0);

	if (!cap.isOpened()) {
		cerr << "Camera open failed!" << endl;
		return;
	}

	CascadeClassifier face_classifier("haarcascade_frontalface_default.xml");
	CascadeClassifier eye_classifier("haarcascade_eye.xml");

	if (face_classifier.empty() || eye_classifier.empty()) {
		cerr << "XML load failed!" << endl;
		return;
	}

	Mat frame;
	while (true) {
		cap >> frame;

		if (frame.empty()) break;

		vector<Rect> faces;
		face_classifier.detectMultiScale(frame, faces);

		for (Rect face : faces) {
			rectangle(frame, face, Scalar(255, 0, 255), 2);

			Mat faceROI = frame(face);
			vector<Rect> eyes;
			eye_classifier.detectMultiScale(faceROI, eyes);

			for (Rect eye : eyes) {
				Point center(eye.x + eye.width / 2, eye.y + eye.height / 2);
				circle(faceROI, center, eye.width / 2, Scalar(255, 0, 0), 2, LINE_AA);
			}
		}

		imshow("frame", frame);

		if (waitKey(1000) == 27) break;
	}
}