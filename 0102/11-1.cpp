#include <iostream>

using namespace std;

int main() {
	cout << "cin.get()로 <Enter> 키까지 입력 받습니다.>>";
	
	int ch;
	int count = 0;
	while ((ch = cin.get()) != EOF) {
		if (ch == 'a') count++;
		else if (ch == '\n') break;
	}
	cout << "a의 개수 = " << count << endl;
}