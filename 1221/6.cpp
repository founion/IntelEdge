#include <iostream>
#include <cstring>
using namespace std;

int main() {
	cout << "�� ��ȣ�� �Է��ϼ���>>";
	char c1[11];
	cin >> c1;

	cout << "�� ��ȣ�� �ٽ� �� �� �Է��ϼ���>>";
	char c2[11];
	cin >> c2;

	if (strcmp(c1, c2) == 0) {
		cout << "�����ϴ�.";
	}
	else {
		cout << "���� �ʽ��ϴ�.";
	}
}
