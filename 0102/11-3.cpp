#include <iostream>

using namespace std;

int main() {
	char ch;
	cout << "'�����;�ѱ۹���'�� �Է��ϼ���(ctrl z�� ������ ����)>>" << endl;
	cin.ignore(100, ';');
	while ((ch = cin.get()) != EOF) {
		cout.put(ch);
		if (ch == '\n') cin.ignore(100, ';');
	}
}