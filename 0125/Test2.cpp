#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;
using namespace cv::dnn;

const String model = "opencv_face_detector_uint8.pb";                                  // 텐서플로에서 훈련된 모델 파일과 구성 파일을 사용.
const String config = "opencv_face_detector.pbtxt";

int main(void)
{
	VideoCapture cap(0);                                                               // 카메라 장치를 열어서 cap에 저장.

	if (!cap.isOpened()) {                                                             // 카메라 열기 실패하는 경우 프로그램 종료.
		cerr << "Camera open failed!" << endl;
		return -1;
	}

	Net net = readNet(model, config);                                                  // 모델 파일과 구성 파일을 이용하여 Net 객체 생성.

	if (net.empty()) {                                                                 // Net 객체 생성 실패하는 경우 프로그램 종료.
		cerr << "Net open failed!" << endl;
		return -1;
	}

	Mat frame1, frame2;                                                                // 카메라의 매 frame을 저장할 Mat 객체 생성.
	while (true) {
		cap >> frame1 >> frame2;                                                       // 카메라의 매 frame을 저장.

		if (frame1.empty() || frame2.empty()) break;                                   // frame을 제대로 받아 오지 못하면 종료.

		Mat blob = blobFromImage(frame1, 1, Size(300, 300), Scalar(104, 177, 123));    // frame 영상을 이용하여 
		net.setInput(blob);                                                            // 네트워크 입력 블롭을 설정하고,
		Mat res = net.forward();                                                       // 네트워크 실행 결과를 res 행렬에 저장.

		Mat detect(res.size[2], res.size[3], CV_32FC1, res.ptr<float>());              // 4차원의 res 행렬을 2차원 행렬 detect로 변환.

		for (int i = 0; i < detect.rows; i++) {
			float confidence = detect.at<float>(i, 2);
			if (confidence < 0.5) break;                                               // 신뢰도 값이 0.5보다 작으면 무시.

			int x1 = cvRound(detect.at<float>(i, 3) * frame1.cols);                    // 얼굴 검출 사각형 영역의 
			int y1 = cvRound(detect.at<float>(i, 4) * frame1.rows);                    // 좌측 상단 좌표 (x1, y1)과
			int x2 = cvRound(detect.at<float>(i, 5) * frame1.cols);                    // 우측 하단 좌표 (x2, y2)를
			int y2 = cvRound(detect.at<float>(i, 6) * frame1.rows);                    // 계산한다.

			rectangle(frame1, Rect(Point(x1, y1), Point(x2, y2)), Scalar(0, 255, 0));  // frame 영상에서 얼굴 검출 영역에 녹색 사각형 그리기.

			String label = format("Face: %4.3f", confidence);                          // 얼굴 신뢰도 출력.
			putText(frame1, label, Point(x1, y1 - 1), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0, 255, 0));


			imshow("frame1", frame1);                                                  // 얼굴 검출 영상 출력.

			Mat face;
			face = frame2(Rect(Point(x1, y1), Point(x2, y2))).clone();                 // 감지된 얼굴 영역의 영상을 face 객체에 깊은 복사.

			Mat gray;
			cvtColor(face, gray, COLOR_BGR2GRAY);                                      // face 영상의 모폴로지를 위해 그레이스케일로 변환.

			Mat bin;
			threshold(gray, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);                 // 그레이스케일의 영상을 이진화, OTSU 알고리즘 사용.

			Mat dst;
			morphologyEx(bin, dst, MORPH_OPEN, Mat());                                 // 이진화된 bin영상에 3x3 정방형 구조 요소를 이용하여 열기 연산을 수행하고 dst에 저장.

			imshow("frame2", dst);                                                     // 모폴로지 열기 연산을 수행한 영상 출력.
		}

		if (waitKey(1) == 27) break;                                                   // esc를 누르면 종료.
	}

	return 0;
}
