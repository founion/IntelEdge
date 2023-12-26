#include <iostream>
#include <string>

using namespace std;

int main() {
	string names[5];

	int strSize = sizeof(names) / sizeof(names[0]);

	cout << "다섯명의 이름을 입력하세요 " << endl;
	
	for (int i = 0; i < strSize; i++) {
		cout << "이름 >> ";
		getline(cin, names[i], '\n');
	}

	string latter = names[0];
	for (int i = 1; i < strSize; i++) {
		if (latter < names[i]) latter = names[i];
	}

	cout << "사전에서 가장 뒤에 나오는 문자열은 " << latter << endl;
}