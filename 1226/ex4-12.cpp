#include <iostream>
#include <string>

using namespace std;

int main() {
	string names[5];

	int strSize = sizeof(names) / sizeof(names[0]);

	cout << "�ټ����� �̸��� �Է��ϼ��� " << endl;
	
	for (int i = 0; i < strSize; i++) {
		cout << "�̸� >> ";
		getline(cin, names[i], '\n');
	}

	string latter = names[0];
	for (int i = 1; i < strSize; i++) {
		if (latter < names[i]) latter = names[i];
	}

	cout << "�������� ���� �ڿ� ������ ���ڿ��� " << latter << endl;
}