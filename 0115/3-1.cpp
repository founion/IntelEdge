#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void PointOp();
void SizeOp();
void RectOp();
void RotatedRectOp();
void RangeOp();
void StringOp();

int main()
{
	cout << "Point" << endl;
	PointOp();
	cout << "Size" << endl;
	SizeOp();
	cout << "Rect" << endl;
	RectOp();
	cout << "RotatedRect" << endl;
	RotatedRectOp();
	cout << "Range" << endl;
	RangeOp();
	cout << "String" << endl;
	StringOp();

	return 0;
}

void PointOp()
{
	Point pt1;
	pt1.x = 5; pt1.y = 10;
	Point pt2(10, 30);

	Point pt3 = pt1 + pt2;
	Point pt4 = pt1 * 2;
	int d1 = pt1.dot(pt2);
	bool b1 = (pt1 == pt2);

	cout << "pt1: " << pt1 << endl;
	cout << "pt2: " << pt2 << endl;
	cout << "pt3: " << pt3 << endl;
	cout << "pt4: " << pt4 << endl;
	cout << "d1: " << d1 << endl;
	cout << "b1: " << b1 << endl;
	cout << endl;
}

void SizeOp()
{
	Size sz1, sz2(10, 20);
	sz1.width = 5, sz1.height = 10;

	Size sz3 = sz1 + sz2;
	Size sz4 = sz1 * 2;
	int area1 = sz4.area();

	cout << "sz1: " << sz1 << endl;
	cout << "sz2: " << sz2 << endl;
	cout << "sz3: " << sz3 << endl;
	cout << "sz4: " << sz4 << endl;
	cout << "area1: " << area1 << endl;
	cout << endl;
}

void RectOp()
{
	Rect rc1;
	Rect rc2(10, 10, 60, 40);

	Rect rc3 = rc1 + Size(50, 40);
	Rect rc4 = rc2 + Point(10, 10);

	Rect rc5 = rc3 & rc4;
	Rect rc6 = rc3 | rc4;

	cout << "rc1: " << rc1 << endl;
	cout << "rc2: " << rc2 << endl;
	cout << "rc3: " << rc3 << endl;
	cout << "rc4: " << rc4 << endl;
	cout << "rc5: " << rc5 << endl;
	cout << "rc6: " << rc6 << endl;
	cout << endl;
}

void RotatedRectOp()
{
	RotatedRect rr1(Point2f(40, 30), Size2f(40, 20), 30.f);

	Point2f pts[4];
	rr1.points(pts);

	Rect br = rr1.boundingRect();
	for (int i = 0; i < 4; i++) cout << "pts[" << i << "]: " << pts[i] << endl;
	cout << "br: " << br << endl;
	cout << endl;
}

void RangeOp()
{
	Range r1(0, 10);
	cout << "r1: " << r1 << endl;
	cout << endl;
}

void StringOp()
{
	String str1 = "Hello";
	String str2 = "world";
	String str3 = str1 + " " + str2;

	bool ret = (str2 == "WORLD");

	cout << "str1: " << str1 << endl;
	cout << "str2: " << str2 << endl;
	cout << "str3: " << str3 << endl;
	cout << "ret: " << ret << endl;

	Mat imgs[3];
	for (int i = 0; i < 3; i++) {
		String filename = format("test%02d.bmp", i + 1);
		imgs[i] = imread(filename);
		cout << "imgs[" << i + 1 << "]: " << filename << endl;
	}
}