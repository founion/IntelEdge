#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void template_matching();
void detect_face();
void detect_eyes();

int main(void)
{
	template_matching();  // ÅÛÇÃ¸´ ¸ÅÄª
	detect_face();        // ¾ó±¼ °ËÃâ
	detect_eyes();        // ´« °ËÃâ

	return 0;
}

void template_matching()
{
	Mat img = imread("circuit.bmp", IMREAD_COLOR);
	Mat templ = imread("crystal.bmp", IMREAD_COLOR);

	if(img.empty() || templ.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	img = img + Scalar(50, 50, 50);

	Mat noise(img.size(), CV_32SC3);
	randn(noise, 0, 10);
	add(img, noise, img, Mat(), CV_8UC3);

	Mat res, res_norm;
	matchTemplate(img, templ, res, TM_CCOEFF_NORMED);
	normalize(res, res_norm, 0, 255, NORM_MINMAX, CV_8U);

	double maxv;
	Point maxloc;
	minMaxLoc(res, 0, &maxv, 0, &maxloc);
	cout << "maxv: " << maxv << endl;

	rectangle(img, Rect(maxloc.x, maxloc.y, templ.cols, templ.rows), Scalar(0, 0, 255), 2);

	imshow("templ", templ);
	imshow("res_norm", res_norm);
	imshow("img", img);

	waitKey();
	destroyAllWindows();
}

void detect_face()
{
	Mat src = imread("kids.png");

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	CascadeClassifier classifier("haarcascade_frontalface_default.xml");

	if (classifier.empty()) {
		cerr << "XML load failed!" << endl;
		return;
	}

	vector<Rect> faces;
	classifier.detectMultiScale(src, faces);

	for (Rect rc : faces) rectangle(src, rc, Scalar(255, 0, 255), 2);

	imshow("src", src);

	waitKey();
	destroyAllWindows();
}

void detect_eyes()
{
	Mat src = imread("kids.png");

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	CascadeClassifier face_classifier("haarcascade_frontalface_default.xml");
	CascadeClassifier eye_classifier("haarcascade_eye.xml");

	if (face_classifier.empty() || eye_classifier.empty()) {
		cerr << "XML load failed!" << endl;
		return;
	}

	vector<Rect> faces;
	face_classifier.detectMultiScale(src, faces);

	for (Rect face : faces) {
		rectangle(src, face, Scalar(255, 0, 255), 2);

		Mat faceROI = src(face);
		vector<Rect> eyes;
		eye_classifier.detectMultiScale(faceROI, eyes);

		for (Rect eye : eyes) {
			Point center(eye.x + eye.width / 2, eye.y + eye.height / 2);
			circle(faceROI, center, eye.width / 2, Scalar(255, 0, 0), 2, LINE_AA);
		}
	}

	imshow("src", src);

	waitKey();
	destroyAllWindows();
}