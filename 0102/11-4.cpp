#include <iostream>

using namespace std;

int main() {
	char ch;
	cout << "'�����;�ѱ۹���'�� �Է��ϼ���(ctrl z�� ������ ����)>>" << endl;
	while ((ch = cin.get()) != EOF) {
		if (ch == ';') {
			cout.put('\n');
			cin.ignore(100, '\n');
		}
		else cout.put(ch);
	}
}