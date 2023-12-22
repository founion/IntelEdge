#include <iostream>
#include <string>

using namespace std;

int main() {	
	while(1){
		cout << "? ";
		int n1, n2;
		string str;
		cin >> n1 >> str >> n2;

		if (str == "+") {
			cout << n1 << str << n2 << "=" << n1 + n2 << endl;
		}
		else if (str == "-") {
			cout << n1 << str << n2 << "=" << n1 - n2 << endl;
		}
		else if (str == "*") {
			cout << n1 << str << n2 << "=" << n1 * n2 << endl;
		}
		else if (str == "/") {
			cout << n1 << str << n2 << "=" << n1 / n2 << endl;
		}
		else if (str == "%") {
			cout << n1 << str << n2 << "=" << n1 % n2 << endl;
		}
	}
}