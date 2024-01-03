#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ifstream fin("c:\\windows\\system.ini", ios::in | ios::binary);
	if (!fin) {
		cout << "열기 오류";
		return 0;
	}

	ofstream fout("c:\\temp\\system.txt", ios::out | ios::binary);
	if (!fout) {
		cout << "열기 오류";
		return 0;
	}

	//파일 사이즈 구하기
	fin.seekg(0, ios::end);
	int fileSize = fin.tellg();
	fin.seekg(0, ios::beg);

	int copyUnit = fileSize / 10;
	char* buf = new char[copyUnit];

	cout << "복사 시작..." << endl;
	for (int i = 0; i < 10; i++) {
		fin.read(buf, copyUnit);
		int real = fin.gcount();
		fout.write(buf, real);
		cout << '.';
		cout << real << "B ";
		cout << (i + 1) * 10 << "%" << endl;
		
		if (real < copyUnit) break;
	}

	cout << fileSize << "B 복사 완료" << endl;

	delete[] buf;
	fin.close();
	fout.close();
}