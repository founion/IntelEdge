#include <iostream>

using namespace std;

template <class T1, class T2>
void mcopy(T1 src[], T2 dest[], int n) {
	for (int i = 0; i < n; i++) dest[i] = (T2)src[i];
}

int main() {
	int x[] = { 1,2,3,4,5 };
	int xsize = sizeof(x) / sizeof(x[0]);
	double d[5];
	char c[5] = { 'H','e','l','l','o' };
	int csize = sizeof(c) / sizeof(c[0]);
	char e[5];

	mcopy(x, d, xsize);
	mcopy(c, e, xsize);

	for (int i = 0; i < xsize; i++) cout << d[i] << ' ';
	cout << endl;
	for (int i = 0; i < csize; i++) cout << e[i] << ' ';
	cout << endl;
}