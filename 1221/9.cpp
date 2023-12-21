#include <iostream>
#include <cstring>
using namespace std;

int main() {
	cout << "이름은?";
	char name[100];
	cin.getline(name, 100, '\n');

	cout << "주소는?";
	char add[100];
	cin.getline(add, 100, '\n');

	cout << "나이는?";
	char old[100];
	cin.getline(old, 100, '\n');

	cout << name << "," << add << "," << old << "세" << endl;
}