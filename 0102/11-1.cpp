#include <iostream>

using namespace std;

int main() {
	cout << "cin.get()�� <Enter> Ű���� �Է� �޽��ϴ�.>>";
	
	int ch;
	int count = 0;
	while ((ch = cin.get()) != EOF) {
		if (ch == 'a') count++;
		else if (ch == '\n') break;
	}
	cout << "a�� ���� = " << count << endl;
}