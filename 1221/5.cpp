#include <iostream>
using namespace std;

int main() {
	cout << "���ڵ��� �Է��϶�(100�� �̸�).";

	char c[100];
	cin.getline(c, 100, '\n');

	int count = 0;
	for (int i = 0; i < 100; i++) {
		if (c[i] == 'x') {
			count++;
		}
	}

	cout << "x�� ������ " << count << endl;
}