#include <iostream>
#include <string>

using namespace std;

int main() {
	string cmd;
	cout << "string���� ���ڿ��� �н��ϴ�." << endl;
	while (true) {
		cout << "�����Ϸ��� exit�� �Է��ϼ��� >> ";
		getline(cin, cmd);
		if (cmd == "exit") {
			cout << "���α׷��� �����մϴ�....";
			return 0;
		}
	}
}