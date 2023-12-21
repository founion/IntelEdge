#include <iostream>
using namespace std;

int main() {
	cout << "5 개의 실수를 입력하라>>";

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

	cout << "제일 큰 수 =" << max << endl;
}