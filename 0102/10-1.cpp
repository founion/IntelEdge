#include <iostream>

using namespace std;

template <class T>
T biggest(T data[], int n) {
	T big;
	big = data[0];
	for (int i = 0; i < n; i++) {
		if (big < data[i + 1]) big = data[i + 1];
	}
	return big;
}

int main() {
	int x[] = { 1,10,100,5,4 };
	cout << biggest(x, 5) << endl;
}