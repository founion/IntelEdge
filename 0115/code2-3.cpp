#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	cout << "Hello OpenCV " << CV_VERSION << endl;

	Mat img;
	img = imread("lenna.bmp");

	/*if (img.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}*/

	//namedWindow("OpenCV_image");
	//imshow("OpenCV_image", img);

	Mat copy1, copy2;
	copy1 = imwrite("lambda1.jpg", img);
	copy1 = imread("lambda1.jpg");

	if (copy1.empty()) {
		cerr << "Image load failed" << endl;
		return -2;
	}

	copy2 = imwrite("lambda2.png", img);
	copy2 = imread("lambda2.png");

	if (copy2.empty()) {
		cerr << "Image load failed" << endl;
		return -2;
	}

	namedWindow("lambda1_image");
	imshow("lambda1_image", copy1);
	namedWindow("lambda2_image");
	imshow("lambda2_image", copy2);

	waitKey();

	return 0;
}