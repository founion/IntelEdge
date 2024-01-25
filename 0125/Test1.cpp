#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void blurring();                                                     // 입력영상 및 트랙바 출력 함수.
void on_sigma(int pos, void* userdata);                              // 트랙바 변경에 따른 가우시안 필터 및 언샤프 마스크 필터링 적용 함수.

int main(void)
{
	blurring();                                                      // blurring 함수 실행
	
	return 0;
}

void blurring()
{
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);                  // rose.bmp 영상을 GRAYSCALE로 불러오기.
	                                                                 // 컬러 영상을 불러오고자 한다면 IMREAD_COLOR 사용.
	if (src.empty()) {                                               // 영상 불러오기 실패할 경우 프로그램 종료.
		cerr << "Image load failed!" << endl;
		return;
	}

	imshow("src", src);                                              // 필터링 적용 전 원본 영상 출력.

	namedWindow("dst");                                              // dst라는 이름의 창 띄우기.
	createTrackbar("Gaussian", "dst", 0, 8, on_sigma, (void*)&src);  // 트랙바 설정, 0부터 8까지이지만 필터링이 적용되는 것은 1부터 8까지임.
	setTrackbarPos("Gaussian", "dst", 0);                            // 처음 트랙바의 위치가 0에서 시작하도록 설정.
	
	waitKey();	                                                     // 키보드 입력시 프로그램 종료.
	return;
}

void on_sigma(int pos, void* userdata)
{
	Mat src = *(Mat*)userdata;                                       // 필터링을 적용할 영상 가져오기.
	
	int sigma = pos;                                                 // 트랙바 위치에 따른 sigma 값 설정.

	Mat blurred;                                                     // 가우시안 필터 적용할 Mat 객체 선언.
	GaussianBlur(src, blurred, Size(), (double)sigma);               // sigma 값에 따라 가우시안 필터 적용.

	float alpha = 1.f;                                               // 언샤프 마스크 필터의 alpha 값을 1.0으로 설정.
	Mat dst;                                                         // 언샤프 마스크 필터를 적용할 Mat 객체 선언.
	dst = (1 + alpha) * src - alpha * blurred;                       // 가우시안 필터를 적용한 영상에 언샤프 마스크 필터 적용.

	String desc = format("sigma: %d", sigma);                        // 필터 적용된 영상에 sigma 값을 출력하기 위한 String 객체 선언 및 format함수 사용.
	putText(dst, desc, Point(10, 30), 
		FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);         // 필터 적용된 영상에 white 글씨 작성.

	imshow("dst", dst);                                              // 최종적으로 가우시안 및 언샤프 마스크 필터 적용된 영상 출력.

	cout << "sigma: " << sigma << endl;                              // cmd 창에는 트랙바 위치에 따른 sigma 값 출력.
}