#include <iostream>

using namespace std;

int main() {
	int f, n;

	cout << "***** �¸��忡 ���� ���� ȯ���մϴ�.  *****" << endl;
	while (1) {		
		cout << "«��:1, ¥��:2, ������:3, ����:4>>";
		cin >> f;
		if (f == 1 || f == 2 || f == 3) {
			cout << "���κ�?";
			cin >> n;
		}
		if (f == 1) {
			cout << "«�� " << n << "�κ� ���Խ��ϴ�." << endl;
		}
		else if (f == 2) {
			cout << "¥�� " << n << "�κ� ���Խ��ϴ�." << endl;
		}
		else if (f == 3) {
			cout << "������ " << n << "�κ� ���Խ��ϴ�." << endl;
		}
		else if (f == 4) {
			cout << "���� ������ �������ϴ�." << endl;
			break;
		}
		else {
			cout << "�ٽ� �ֹ��ϼ���!!" << endl;
		}
	}
}