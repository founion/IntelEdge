#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ifstream fin("c:\\windows\\system.ini", ios::in | ios::binary);
	if (!fin) {
		cout << "열기 오류";
		return 0;
	}

}