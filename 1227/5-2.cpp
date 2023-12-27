#include <iostream>

using namespace std;

double half(double& tmp) {
	tmp = tmp / (double)2;
	return tmp;
}

int main() {
	double n = 20;
	half(n);
	cout << n;
}