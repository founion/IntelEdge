#include <iostream>
#include <string>

using namespace std;

int main() {
	string text;
	
	cout << "���ڿ� �Է�>> ";
	getline(cin, text, '\n');

	int count = 0;
	int startIndex = 0;
	while (true) {
		int fIndex = text.find('a', startIndex);
		if (fIndex == -1) break;	
		startIndex = fIndex + 1;
		if (startIndex > fIndex) count++;
	}

	cout << "���� a�� " << count << "�� �ֽ��ϴ�." << endl;
}