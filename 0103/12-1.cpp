#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ifstream fin("c:\\temp\\test.txt");
	if (!fin) {
		cout << "파일을 열 수 없다.";
		return 0;
	}

	int ch;
	while ((ch = fin.get()) != EOF) {
		cout.put(ch);
	}

	fin.close();
}