#include <iostream>
#include <string>

using namespace std;

class Person
{
	string name;
	string tel;
public:
	Person() { this->name = ""; this->tel = ""; }
	string getName() { return name; }
	string getTel() { return tel; }
	void set(string name, string tel) { this->name = name; this->tel = tel; }
};

int main() {
	cout << "이름과 전화번호를 입력해 주세요" << endl;
	Person* pArray = new Person[3];
	string n, t;
	for (int i = 0; i < 3; i++) {
		cout << "사람 " << i + 1 << ">> ";
		cin >> n >> t;
		pArray[i].set(n, t);
	}

	cout << "모든 사람의 이름은 ";
	for (int i = 0; i < 3; i++) {
		cout << pArray[i].getName() << ' ';
	}

	cout << endl << "전화번호 검색합니다. 이름을 입력하세요>>";
	cin >> n;
	for (int i = 0; i < 3; i++) {
		if (n == pArray[i].getName()) {
			cout << "전화번호는 " << pArray[i].getTel() << endl;
		}
	}
}