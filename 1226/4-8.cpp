#include <iostream>

using namespace std;

class Circle
{
	int radius;
public:
	Circle() { radius = 1; }
	~Circle() { };
	void setRadius(int radius) { this->radius = radius; }
	double getArea() { return 3.14 * radius * radius; }
};

int main() {
	cout << "원의 개수 >> ";
	int n, radius;
	cin >> n;
	if (n <= 0) return 0;
	
	Circle* pArray = new Circle[n];
	for (int i = 0; i < n; i++) {
		cout << "원 " << i + 1 << "의 반지름 >> ";
		cin >> radius;
		pArray[i].setRadius(radius);
	}

	int count = 0;
	Circle* p = pArray;
	for (int i = 0; i < n; i++) {
		if (p->getArea() > 100) count++;
		p++;
	}

	cout << "면적이 100보다 큰 원은 " << count << "개 입니다." << endl;
}