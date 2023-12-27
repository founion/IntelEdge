#include <iostream>

using namespace std;

int add(int s[], int size, int t[]=NULL) {
	int sum = 0;
	for (int i = 0; i < size; i++) sum += s[i];
	if (t == NULL) return sum;
	for (int i = 0; i < size; i++) sum += t[i];
	return sum;
}

int main() {
	int a[] = { 1,2,3,4,5 };
	int b[] = { 6,7,8,9,10 };
	int c = add(a, 5);
	int d = add(a, 5, b);
	cout << c << endl;
	cout << d << endl;
}