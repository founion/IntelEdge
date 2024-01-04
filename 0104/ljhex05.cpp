#include <iostream>

using namespace std;

template <class T>
T biggest(T data[], int n) {
	T max;
	max = data[0];
	for (int i = 0; i < n; i++) {
		if (max < data[i + 1]) max = data[i + 1];
	}
	return max;
}

int main() {
	int x[] = { 1,10,100,5,4 };
	int xsize = sizeof(x) / sizeof(x[0]);
	cout << biggest(x, xsize) << endl;

	int y[] = { 566,846,321,798,321,134 };
	int ysize = sizeof(y) / sizeof(y[0]);
	cout << biggest(y, ysize) << endl;
}