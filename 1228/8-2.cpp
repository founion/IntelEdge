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
	string name;
public:
	NamedCircle(int radius = 0, string name = "") : Circle(radius) { this->name = name; }
	void set(int radius, string name) { setRadius(radius); this->name = name; }
	string getName() { return name; }
};

string biggest(NamedCircle p[], int n) {
	if (n <= 0) return "오류";
	
	int big = 0;
	for (int i = 1; i < 5; i++) {
		if (p[big].getRadius() < p[i].getRadius()) big = i;
	}
	return p[big].getName();
}

int main() {
	NamedCircle pizza[5];
	cout << "5 개의 정수 반지름과 원의 이름을 입력하세요" << endl;
	int n;
	string s;
	for (int i = 0; i < 5; i++) {
		cout << i + 1 << ">> ";
		cin >> n;
		getline(cin, s, '\n');
	
		pizza[i].set(n, s);
	}
	

	cout << "가장 면적이 큰 피자는 " << biggest(pizza, 5) << "입니다." << endl;
}