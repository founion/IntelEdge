#include <iostream>
#include <string>

using namespace std;

int main() {
	cout << "���������� 2000��, �Ƹ޸�ī�� 2300��, īǪġ�� 2500���Դϴ�." << endl;

	int n;
	int sum = 0;
	string str;

	while (1) {
		cout << "�ֹ�>>";
		cin >> str >> n;

		if (str == "����������") {
			int p1 = n * 2000;
			cout << p1 << "���Դϴ�. ���ְ� �弼��" << endl;
			sum += p1;
		}
		else if (str == "�Ƹ޸�ī��") {
			int p2 = n * 2300;
			cout <<p2 << "���Դϴ�. ���ְ� �弼��" << endl;
			sum += p2;
		}
		else if (str == "īǪġ��") {
			int p3 = n * 2500;
			cout << p3 << "���Դϴ�. ���ְ� �弼��" << endl;
			sum += p3;
		}
		
		if (sum >= 20000) {
			cout << "���� " << sum << "���� �Ǹ��Ͽ� ī�並 �ݽ��ϴ�. ���Ϻ���~~" << endl;
			break;
		}
	}
}