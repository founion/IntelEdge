#include <iostream>

using namespace std;

class Circle
{
	int radius;
public:
	Circle() { radius = 1; cout << "积己磊 角青 radius = " << radius << endl; }
	Circle(int r) { radius = r; cout << "积己磊 角青 radius = " << radius << endl; }
	~Circle() { cout << "家戈磊 角青 radius = " << radius << endl; }
	void setRadius(int r) { radius = r; }
	double getArea() { return 3.14 * radius * radius; }
};

int main() {
	Circle* pArray = new Circle [3];

	pArray[0].setRadius(10);
	pArray[1].setRadius(20);
	pArray[2].setRadius(30);

	int numArray = sizeof(pArray) / sizeof(Circle);

	for (int i = 0; i <= numArray; i++) {
		cout << pArray[i].getArea() << endl;
	}

	Circle* p = pArray;
	for (int i = 0; i <= numArray; i++) {
		cout << p->getArea() << endl;
		p++;
	}

	delete[] pArray;
}
