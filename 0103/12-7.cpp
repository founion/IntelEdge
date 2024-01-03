#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ifstream fin("c:\\windows\\system.ini", ios::in | ios::binary);
	if (!fin) {
		cout << "���� ����";
		return 0;
	}

	ofstream fout("c:\\temp\\system.txt", ios::out | ios::binary);
	if (!fout) {
		cout << "���� ����";
		return 0;
	}

	fin.seekg(0, ios::end);
	int fileSize = fin.tellg();

	for (int i = 0; i < fileSize; i++) {
		fin.seekg(fileSize - i - 1, ios::beg);
		int ch = fin.get();
		fout.put(ch);
	}
	cout << "���� �Ϸ�" << endl;

	fin.close();
	fout.close();
}