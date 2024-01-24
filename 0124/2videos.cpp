#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void video();

int main(void)
{
	video();  // video 함수 실행

	return 0;
}

void video()
{
	VideoCapture cap(0);  // VideoCapture 클래스를 사용하여 카메라를 오픈

	if (!cap.isOpened()) {  // 카메라 오픈에 실패 시
		cerr << "Camera open failed!" << endl;
		return;
	}

	Mat frame1, frame2, frame3;  // 3개의 화면을 띄울것이므로 Mat 클래스 객체 3개 생성
	while (true) {
		cap >> frame1 >> frame2 >> frame3;  // frame 객체를 cap에 입력

		if (frame1.empty() || frame2.empty() || frame3.empty()) break;  // 입력 실패 시
		
		cvtColor(frame1, frame2, COLOR_BGR2GRAY);  // frame2는 frame1 영상을 그레이스케일로 변환
		threshold(frame2, frame3, 0, 255, THRESH_BINARY | THRESH_OTSU);  // frame3는 frame2를 이진화(otsu방식을 사용, 자동으로 임계값 설정하도록 하였음)

		imshow("frame1", frame1);  // frame1 : 일반 영상
		imshow("frame2", frame2);  // frame2 : 그레이스케일로 변환한 영상
		imshow("frame3", frame3);  // frame3 : 그레이스케일 영상을 이진화한 영상

		if (waitKey(10) == 27) break;  // esc 누르면 종료
	}

	destroyAllWindows();
}