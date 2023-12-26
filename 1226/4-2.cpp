#include <iostream>

using namespace std;

int main() {
	cout << "정수 5개 입력>>";
	double* p = new double[5];
	if (!p) {
		cout << "메모리를 할당할 수 없습니다.";
		return 0;
	}

	int size = sizeof(int[5]) / sizeof(int);
	for (int i = 0; i < size; i++) {
		cin >> p[i];
	}

	double sum = 0;
	for (int i = 0; i < size; i++) sum += p[i];
	cout << "평균 " << sum / (double)size << endl;

	delete p;
}