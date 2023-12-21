#include <iostream>
#include <cstring>
using namespace std;

int main() {
	cout << "5 명의 이름을 ';'으로 구분하여 입력하세요\n>>";
	char a[100], b[100], c[100], d[100], e[100];
	cin.getline(a, 100, ';');
	cin.getline(b, 100, ';');
	cin.getline(c, 100, ';');
	cin.getline(d, 100, ';');
	cin.getline(e, 100, ';');

	cout << "1 : " << a << endl;
	cout << "2 : " << b << endl;
	cout << "3 : " << c << endl;
	cout << "4 : " << d << endl;
	cout << "5 : " << e << endl;
	
	int max;
	char maxstr[20];
	max = strlen(a);
	strcpy_s(maxstr, a);

	if (max < strlen(b)) {
		max = strlen(b);
		strcpy_s(maxstr, b);
	}
	else if (max < strlen(c)) {
		max = strlen(c);
		strcpy_s(maxstr, c);
	}
	else if (max < strlen(d)) {
		max = strlen(d);
		strcpy_s(maxstr, d);
	}
	else if (max < strlen(e)) {
		max = strlen(e);
		strcpy_s(maxstr, e);
	}

	cout << "가장 긴 이름은 " << maxstr << endl;
}