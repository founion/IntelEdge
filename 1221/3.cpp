#include <iostream>
using namespace std;

int main() {
	cout << "�� ���� �Է��϶�>>";
	
	int a, b;
	cin >> a >> b;
	
	int large;
	if (a > b) {
		large = a;
	}
	else if (a < b) {
		large = b;
	}
	cout << "ū �� = " << large << endl;
}