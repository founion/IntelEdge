#include <iostream>
#include <string>

using namespace std;

int main() {
	string text;
	
	cout << "문자열 입력>> ";
	getline(cin, text, '\n');

	int count = 0;
	int startIndex = 0;
	while (true) {
		int fIndex = text.find('a', startIndex);
		if (fIndex == -1) break;	
		startIndex = fIndex + 1;
		if (startIndex > fIndex) count++;
	}

	cout << "문자 a는 " << count << "개 있습니다." << endl;
}