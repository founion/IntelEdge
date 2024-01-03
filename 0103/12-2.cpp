#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ifstream fin("c:\\windows\\system.ini");
	if (!fin) {
		cout << "열기 오류";
		return 0;
	}

	int line = 0;
	char buf[100];
	while (fin.getline(buf, 100)) {
		line++;
		cout << line << " : " << buf << endl;
	}
	
	fin.close();
}