#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ifstream fin("c:\\temp\\test.txt");
	if (!fin) {
		cout << "������ �� �� ����.";
		return 0;
	}

	int ch;
	while ((ch = fin.get()) != EOF) {
		cout.put(ch);
	}

	fin.close();
}