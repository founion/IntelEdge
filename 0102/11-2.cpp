#include <iostream>

using namespace std;

int main() {
	cout << "cin.get(char&)�� <Enter> Ű���� �Է� �޽��ϴ�.>>";
	char ch;
	int count = 0;
	while (true) {
		cin.get(ch);
		if (ch == ' ') count++;
		else if (ch == '\n') break;
	}
	cout << "�� ĭ�� ���� = " << count << endl;
}