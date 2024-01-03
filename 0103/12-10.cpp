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
		cout << fsrc << "열기 오류";
		exit(0);
	}
	dest.open(fdest, ios::in | ios::binary);
	if (!fdest) {
		cout << fdest << "열기 오류";
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
	cout << "비교하는 두 파일은 " << "mountain.jpg" << "와" << "valley.jpg" << "입니다." << endl;
	fileCompare comp("mountain.jpg", "valley.jpg");
	if (comp.compare()) cout << "두 파일은 같습니다." << endl;
	else cout << "두 파일은 같지 않습니다." << endl;
}