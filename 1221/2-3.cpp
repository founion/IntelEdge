#include <iostream>

using namespace std;

int main() {
	cout << "�ʺ�(cm)�� �Է��ϼ���>>";

	int width;
	cin >> width;

	cout << "����(cm)�� �Է��ϼ���>>";

	int height;
	cin >> height >> width;

	int area = width * height;
	cout << "������ " << area << "(cm^2) �Դϴ�." << '\n';
}