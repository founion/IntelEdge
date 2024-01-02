#include <iostream>

using namespace std;

int main() {
	cout << "cin.get(char&)로 <Enter> 키까지 입력 받습니다.>>";
	char ch;
	int count = 0;
	while (true) {
		cin.get(ch);
		if (ch == ' ') count++;
		else if (ch == '\n') break;
	}
	cout << "빈 칸의 개수 = " << count << endl;
}