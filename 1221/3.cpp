#include <iostream>
using namespace std;

int main() {
	cout << "두 수를 입력하라>>";
	
	int a, b;
	cin >> a >> b;
	
	int large;
	if (a > b) {
		large = a;
	}
	else if (a < b) {
		large = b;
	}
	cout << "큰 수 = " << large << endl;
}