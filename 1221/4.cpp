#include <iostream>
using namespace std;

int main() {
	cout << "5 ���� �Ǽ��� �Է��϶�>>";

	float a, b, c, d, e;
	cin >> a >> b >> c >> d >> e;

	float max;
	max = a;
	if (max < b) {
		max = b;
	}
	else if (max < c) {
		max = c;
	}
	else if (max < d) {
		max = d;
	}
	else if (max < e) {
		max = e;
	}

	cout << "���� ū �� =" << max << endl;
}