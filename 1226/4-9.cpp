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
	cout << "�̸��� ��ȭ��ȣ�� �Է��� �ּ���" << endl;
	Person* pArray = new Person[3];
	string n, t;
	for (int i = 0; i < 3; i++) {
		cout << "��� " << i + 1 << ">> ";
		cin >> n >> t;
		pArray[i].set(n, t);
	}

	cout << "��� ����� �̸��� ";
	for (int i = 0; i < 3; i++) {
		cout << pArray[i].getName() << ' ';
	}

	cout << endl << "��ȭ��ȣ �˻��մϴ�. �̸��� �Է��ϼ���>>";
	cin >> n;
	for (int i = 0; i < 3; i++) {
		if (n == pArray[i].getName()) {
			cout << "��ȭ��ȣ�� " << pArray[i].getTel() << endl;
		}
	}
}