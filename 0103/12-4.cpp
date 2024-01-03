#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ifstream fin("c:\\windows\\system.ini");
	if (!fin) {
		cout << "열기 오류";
		return 0;
	}

	ofstream fout("c:\\temp\\system.txt");
	if (!fout) {
		cout << "열기 오류";
		return 0;
	}

	int c;
	while ((c = fin.get()) != EOF) {
		fout.put(c);
	}

	fin.close();
	fout.close();
}