#include <iostream>
#include <cstring>
using namespace std;

int main() {
	cout << "�̸���?";
	char name[100];
	cin.getline(name, 100, '\n');

	cout << "�ּҴ�?";
	char add[100];
	cin.getline(add, 100, '\n');

	cout << "���̴�?";
	char old[100];
	cin.getline(old, 100, '\n');

	cout << name << "," << add << "," << old << "��" << endl;
}