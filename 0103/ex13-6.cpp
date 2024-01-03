#include <iostream>
#include <cstring>

using namespace std;

int stringToInt(const char x[]) {
	int sum = 0;
	int len = strlen(x);
	for (int i = 0; i < len; i++) {
		if (x[i] >= '0' && x[i] <= '9') sum = sum * 10 + x[i] - '0';
		else throw x;
	}
	return sum;
}

int main() {
	int n;
	try {
		n = stringToInt("123");
		cout << "\"123\" �� ���� " << n << "�� ��ȯ��" << endl;
		n = stringToInt("1A3");
		cout << "\"1A3\" �� ���� " << n << "�� ��Ⱥ��" << endl;
	}
	catch (const char* s) {
		cout << s << "ó������ ���� �߻�!!" << endl;
		return 0;
	}
}