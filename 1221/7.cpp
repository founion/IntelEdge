#include <iostream>
#include <cstring>
using namespace std;

int main() {
	cout << "종료하고싶으면 yes를 입력하세요>>";
	char c[100];
	cin.getline(c, 100, '\n');

	while (strcmp(c, "yes") != 0) {
		cout << "종료하고싶으면 yes를 입력하세요>>";
		cin.getline(c, 100, '\n');
	}
	cout << "종료합니다...";
}