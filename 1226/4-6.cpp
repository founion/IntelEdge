#include <iostream>
#include <string>

using namespace std;

int main() {
	string s;

	cout << "�Ʒ��� ������ �Է��ϼ���.(exit�� �Է��ϸ� �����մϴ�.)" << endl;
	while(true){
		cout << ">> ";
		getline(cin, s, '\n');
		if (s == "exit") break;

		int len = s.length();
		for (int i = len - 1; i >= 0; i--) {
			cout << s[i];
		}
		cout << endl;
	}
}