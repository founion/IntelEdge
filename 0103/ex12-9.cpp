#include <iostream>
#include <fstream>

using namespace std;

int main() {
	const char* srcFile = "c:\\temp\\tulips.jpg";
	const char* destFile = "c:\\temp\\copytulips.jpg";

	ifstream fsrc(srcFile, ios::in | ios::binary);
	if (!fsrc) {
		cout << srcFile << " 열기 오류" << endl;
		return 0;
	}

	ofstream fdest(destFile, ios::out | ios::binary);
	if (!fdest) {
		cout << destFile << " 열기 오류" << endl;
		return 0;
	}

	char buf[1024];
	while (!fsrc.eof()) {
		fsrc.read(buf, 1024);
		int n = fsrc.gcount();
		fdest.write(buf, n);
	}
	cout << srcFile << "을 " << destFile << "으로 복사 완료" << endl;
	fsrc.close();
	fdest.close();
}