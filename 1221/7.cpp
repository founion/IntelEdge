#include <iostream>
#include <cstring>
using namespace std;

int main() {
	cout << "�����ϰ������ yes�� �Է��ϼ���>>";
	char c[100];
	cin.getline(c, 100, '\n');

	while (strcmp(c, "yes") != 0) {
		cout << "�����ϰ������ yes�� �Է��ϼ���>>";
		cin.getline(c, 100, '\n');
	}
	cout << "�����մϴ�...";
}