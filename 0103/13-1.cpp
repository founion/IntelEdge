#include <iostream>

using namespace std;

int sum(int a, int b) {
	if (a > b) throw "�߸��� �Է�";
	else if (a < 0 || b < 0) throw "���� ó�� �ȵ�";
	
	int sum = 0;
	int length = b - a;
	for (int i = 0; i <= length; i++) sum = sum + a + i;
	return sum;
}

int main() {
	try {
		cout << sum(2, 5) << endl;
		cout << sum(-1, 5) << endl;
	}
	catch (const char* s) {
		cout << s << endl;
	}
}