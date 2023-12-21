#include <iostream>

using namespace std;

int main() {
	cout << "너비(cm)를 입력하세요>>";

	int width;
	cin >> width;

	cout << "높이(cm)를 입력하세요>>";

	int height;
	cin >> height >> width;

	int area = width * height;
	cout << "면적은 " << area << "(cm^2) 입니다." << '\n';
}