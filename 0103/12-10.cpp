#include <iostream>
#include <fstream>

using namespace std;

class fileCompare
{
	ifstream src;
	ifstream dest;
public:
	fileCompare(const char* fsrc, const char* fdest);
	bool compare();
};

fileCompare::fileCompare(const char* fsrc, const char* fdest) {
	src.open(fsrc, ios::in | ios::binary);
	if (!fsrc) {
		cout << fsrc << "���� ����";
		exit(0);
	}
	dest.open(fdest, ios::in | ios::binary);
	if (!fdest) {
		cout << fdest << "���� ����";
		exit(0);
	}
}

bool fileCompare::compare() {
	int s;
	while ((s = src.get()) != EOF) {
		int t = dest.get();

		if (t == EOF) return false;
		else if (s != t) return false;
	}

	int t = dest.get();
	if (t != EOF) return false;

	return true;
}

int main() {
	cout << "���ϴ� �� ������ " << "mountain.jpg" << "��" << "valley.jpg" << "�Դϴ�." << endl;
	fileCompare comp("mountain.jpg", "valley.jpg");
	if (comp.compare()) cout << "�� ������ �����ϴ�." << endl;
	else cout << "�� ������ ���� �ʽ��ϴ�." << endl;
}