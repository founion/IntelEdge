#include <iostream>

using namespace std;

int main() {
	cout << "���� 5�� �Է�>>";
	double* p = new double[5];
	if (!p) {
		cout << "�޸𸮸� �Ҵ��� �� �����ϴ�.";
		return 0;
	}

	int size = sizeof(int[5]) / sizeof(int);
	for (int i = 0; i < size; i++) {
		cin >> p[i];
	}

	double sum = 0;
	for (int i = 0; i < size; i++) sum += p[i];
	cout << "��� " << sum / (double)size << endl;

	delete p;
}