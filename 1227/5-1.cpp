#include <iostream>

using namespace std;

class Circle
{
public:
	Circle() { radius = 1; }
	Circle(int radius) { this->radius = radius; }
	double getArea() { return 3.14 * radius * radius; }
private:
	int radius;
};

void swap(Circle& a, Circle& b) {
	Circle tmp;
	tmp = a;
	a = b;
	b = tmp;
}

int main() {
	Circle a(1);
	Circle b(2);
	cout << "원 a의 면적 = " << a.getArea() << endl;
	cout << "원 b의 면적 = " << b.getArea() << endl;

	swap(a, b);
	cout << "원 a의 면적 = " << a.getArea() << endl;
	cout << "원 b의 면적 = " << b.getArea() << endl;
}