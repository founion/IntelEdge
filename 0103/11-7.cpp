#include <iostream>
#include <cctype>

using namespace std;

int main() {
	for (int i = 0; i < 4; i++) {
		cout << "dec" << '\t' << "hexa" << '\t' << "char" << '\t';
	}
	cout << endl;
	for (int i = 0; i < 4; i++) {
		cout << "---" << '\t' << "----" << '\t' << "----" << '\t';
	}
	cout << endl;

	cout.width(3);
	cout << left;
	for (int i = 0; i < 128; i++) {
		cout << dec << i << '\t' << hex << i << '\t' << (isprint(i) ? (char)i : '.') << '\t';
		if (i % 4 == 3) cout << endl;
	}

}