#include <iostream>

using namespace std;

class Circle
{
	int radius;
public:
	Circle(int r) { radius = r; }
	int getRaidus() { return radius; }
	void setRadius(int r) { radius = r; }
	void show() { cout << "반지름이 " << radius << "인 원" << endl; }
};

void increase(Circle& a, Circle& b) {
	int r = a.getRaidus() + b.getRaidus();
	a.setRadius(r);
}

int main() {
	Circle x(10), y(5);
	increase(x, y);
	x.show();
}