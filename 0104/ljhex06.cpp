#include <iostream>

using namespace std;

int get() throw(char*) {
	int n;
	cout << "1~9 ������ ���� �Է� >> ";
	cin >> n;
	if (n >= 1 && n <= 9) return n;
	else throw "input fault";
}

int main() {
	int n, m;
	while (true) {
		try {
			n = get();
			m = get();
			cout << n << " x " << m << " = " << n * m << endl;
		}
		catch (const char* s) {
			cout << s << " ���� �߻�, ����� �� ����" << endl;
		}
	}
}