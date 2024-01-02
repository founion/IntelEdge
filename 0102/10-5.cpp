#include <iostream>

using namespace std;

template <class T>
T* concat(T a[], int sizea, T b[], int sizeb) {
	T* p = new T[sizea + sizeb];
	for (int i = 0; i < sizea; i++) p[i] = a[i];
	for (int i = 0; i < sizeb; i++) p[i + sizea] = b[i];

	return p;
}

int main() {
	int x[] = { 1,2,3 };
	int y[] = { 6,7,8,9 };
	int* p = concat(x, 3, y, 4);
	int isize = (sizeof(x)+sizeof(y))/sizeof(x[0]);
	for (int i = 0; i < isize; i++) cout << p[i] << ' ';
	cout << endl;

	char a[] = { 'L','o','v','e' };
	char b[] = { 'C','+','+' };
	char* q = concat(a, 4, b, 3);
	int csize = (sizeof(a) + sizeof(b)) / sizeof(a[0]);
	for (int i = 0; i < csize; i++) cout << q[i];
	cout << endl;
}