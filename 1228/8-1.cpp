#include <iostream>
#include <string>

using namespace std;

class Circle
{
	int radius;
public:
	Circle(int radius = 0) { this->radius = radius; }
	int getRadius() { return radius; }
	void setRadius(int radius) { this->radius = radius; }
	double getArea() { return 3.14 * radius * radius; }
};

class NamedCircle : public Circle
{
	string s;
public:
	NamedCircle(int a, string s) : Circle(a) { this->s = s; }
	void show() { cout << "�������� " << getRadius() << "�� " << s << endl; }
};

int main() {
	NamedCircle waffle(3, "waffle");
	waffle.show();
}