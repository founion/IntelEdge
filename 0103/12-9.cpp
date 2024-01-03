#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class fileLineViewer
{
	ifstream fin;
	vector<string> v;
public:
	fileLineViewer(const char* f);
	~fileLineViewer();
	void run();
};

fileLineViewer::fileLineViewer(const char* f) {
	fin.open(f);
	if (!fin) {
		cout << "열기 오류";
		exit(0);
	}

	string line;
	while (getline(fin,line)) {
		v.push_back(line);
	}
	cout << f << " 파일 읽기 완료" << endl;
}
fileLineViewer::~fileLineViewer() {
	fin.close();
}

void fileLineViewer::run() {
	cout << "라인 번호를 입력하세요. 1보다 작은 값을 입력하면 종료" << endl;
	while (true) {
		cout << ": ";
		int lineNo;
		cin >> lineNo;
		if (lineNo > (int)v.size()) continue;
		else if (lineNo < 1) {
			cout << "종료합니다.";
			break;
		}
		cout << v.at(lineNo - 1) << endl;
	}
}

int main() {
	fileLineViewer viewr("c:\\windows\\system.ini");
	viewr.run();
}