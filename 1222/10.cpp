#include <iostream>
#include <string>
using namespace std;

int main() {
	cout << "���ڿ� �Է�>>";
	string str;
	cin >> str;

	int i;
	for (i = 1; i <= str.length(); i++) {
		cout << str.substr(0, i) << endl;
	}
}