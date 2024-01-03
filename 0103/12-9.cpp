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
		cout << "���� ����";
		exit(0);
	}

	string line;
	while (getline(fin,line)) {
		v.push_back(line);
	}
	cout << f << " ���� �б� �Ϸ�" << endl;
}
fileLineViewer::~fileLineViewer() {
	fin.close();
}

void fileLineViewer::run() {
	cout << "���� ��ȣ�� �Է��ϼ���. 1���� ���� ���� �Է��ϸ� ����" << endl;
	while (true) {
		cout << ": ";
		int lineNo;
		cin >> lineNo;
		if (lineNo > (int)v.size()) continue;
		else if (lineNo < 1) {
			cout << "�����մϴ�.";
			break;
		}
		cout << v.at(lineNo - 1) << endl;
	}
}

int main() {
	fileLineViewer viewr("c:\\windows\\system.ini");
	viewr.run();
}