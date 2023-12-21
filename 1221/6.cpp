#include <iostream>
#include <cstring>
using namespace std;

int main() {
	cout << "새 암호를 입력하세요>>";
	char c1[11];
	cin >> c1;

	cout << "새 암호를 다시 한 번 입력하세요>>";
	char c2[11];
	cin >> c2;

	if (strcmp(c1, c2) == 0) {
		cout << "같습니다.";
	}
	else {
		cout << "같지 않습니다.";
	}
}
