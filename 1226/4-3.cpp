#include <iostream>
#include <string>

using namespace std;

int main() {
	string text;
	
	cout << "���ڿ� �Է�>> ";
	getline(cin, text, '\n');

	int count = 0;
	for (int i = 0; i < text.length(); i++) {
		if (text[i] == 'a') count++;
	}

	cout << "���� a�� " << count << "�� �ֽ��ϴ�." << endl;
}