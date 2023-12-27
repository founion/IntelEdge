#include <iostream>

using namespace std;

class Circle
{
public:
	Circle() { radius = 1; }
	Circle(const Circle& c) { this->radius = c.radius; cout << "���� ������ ���� radius = " << radius << endl; }
	Circle(int radius) { this->radius = radius; }
	double getArea() { return 3.14 * radius * radius; }
private:
	int radius;
};

int main() {
	Circle src(30);
	Circle dest(src);

	cout << "������ ���� = " << src.getArea() << endl;
	cout << "�纻�� ���� = " << dest.getArea() << endl;
}