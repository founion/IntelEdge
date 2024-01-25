#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void blurring();                                                     // �Է¿��� �� Ʈ���� ��� �Լ�.
void on_sigma(int pos, void* userdata);                              // Ʈ���� ���濡 ���� ����þ� ���� �� ����� ����ũ ���͸� ���� �Լ�.

int main(void)
{
	blurring();                                                      // blurring �Լ� ����
	
	return 0;
}

void blurring()
{
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);                  // rose.bmp ������ GRAYSCALE�� �ҷ�����.
	                                                                 // �÷� ������ �ҷ������� �Ѵٸ� IMREAD_COLOR ���.
	if (src.empty()) {                                               // ���� �ҷ����� ������ ��� ���α׷� ����.
		cerr << "Image load failed!" << endl;
		return;
	}

	imshow("src", src);                                              // ���͸� ���� �� ���� ���� ���.

	namedWindow("dst");                                              // dst��� �̸��� â ����.
	createTrackbar("Gaussian", "dst", 0, 8, on_sigma, (void*)&src);  // Ʈ���� ����, 0���� 8���������� ���͸��� ����Ǵ� ���� 1���� 8������.
	setTrackbarPos("Gaussian", "dst", 0);                            // ó�� Ʈ������ ��ġ�� 0���� �����ϵ��� ����.
	
	waitKey();	                                                     // Ű���� �Է½� ���α׷� ����.
	return;
}

void on_sigma(int pos, void* userdata)
{
	Mat src = *(Mat*)userdata;                                       // ���͸��� ������ ���� ��������.
	
	int sigma = pos;                                                 // Ʈ���� ��ġ�� ���� sigma �� ����.

	Mat blurred;                                                     // ����þ� ���� ������ Mat ��ü ����.
	GaussianBlur(src, blurred, Size(), (double)sigma);               // sigma ���� ���� ����þ� ���� ����.

	float alpha = 1.f;                                               // ����� ����ũ ������ alpha ���� 1.0���� ����.
	Mat dst;                                                         // ����� ����ũ ���͸� ������ Mat ��ü ����.
	dst = (1 + alpha) * src - alpha * blurred;                       // ����þ� ���͸� ������ ���� ����� ����ũ ���� ����.

	String desc = format("sigma: %d", sigma);                        // ���� ����� ���� sigma ���� ����ϱ� ���� String ��ü ���� �� format�Լ� ���.
	putText(dst, desc, Point(10, 30), 
		FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);         // ���� ����� ���� white �۾� �ۼ�.

	imshow("dst", dst);                                              // ���������� ����þ� �� ����� ����ũ ���� ����� ���� ���.

	cout << "sigma: " << sigma << endl;                              // cmd â���� Ʈ���� ��ġ�� ���� sigma �� ���.
}