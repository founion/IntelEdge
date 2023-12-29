#include <iostream>

using namespace std;

class Square
{
public:
	Square(int width, int height) { this->width = width; this->height = height; }
	int getArea() { return width * height; }
	friend int addSquare(Square a, Square b);
private:
	int width, height;
};

int addSquare(Square a, Square b) {
	return a.getArea() + b.getArea();
}

int main() {
	Square a(5, 3), b(4, 4);

	cout << "두 사각형 넓이의 합 : " << addSquare(a,b) << endl;
}