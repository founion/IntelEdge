#include <iostream>

using namespace std;

bool bigger(int a, int b, int& big) {
	if (a == b) return true;
	
	big = a;
	if (big < b) big = b;
	return false;
}

int main() {
	cout << "�� ������ �Է��ϼ���>> ";
	int n1, n2;
	cin >> n1 >> n2;

	int big = 0;
	if (bigger(n1, n2, big)) cout << "�� ������ ũ�Ⱑ �����ϴ�." << endl;
	else cout << "�� ����" << n1 << ',' << n2 << " �� ū ���� " << big << endl;
}