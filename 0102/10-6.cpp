#include <iostream>

using namespace std;

template <class T>
T* remove(T src[], int sizeSrc, T minus[], int sizeMinus, int& retSize) {
	T* p = new T[sizeSrc];
	int k = 0;
	for (int i = 0; i < sizeSrc; i++) {
		int j;
		for (j = 0; j < sizeMinus; j++) {
			if (src[i] == minus[j]) break;
		}
		if (j == sizeMinus) {
			p[k] = src[i];
			k++;
		}
	}
	retSize = k;
	if (k == 0) {
		delete[] p;
		return NULL;
	}
	T* q = p;
	if (sizeSrc != sizeMinus) {
		q = new T[k];
		for (int i = 0; i < k; i++) q[i] = p[i];
		delete[] p;
	}
	return q;
}

int main() {
	int x[] = { 1,2,3,4 };
	int y[] = { -3,5,10,1,2,3 };
	int retSize;

	int* p = remove(x, 4, y, 6, retSize);
	if (retSize == 0) {
		cout << "모두 제거되어 리턴하는 값이 없습니다." << endl;
		return 0;
	}
	else {
		for (int i = 0; i < retSize; i++) cout << p[i] << ' ';
		cout << endl;

		delete[] p;
	}
}