#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

int main() {
	cout << "���� �ؽ�Ʈ�� �Է��ϼ���. ������׷��� �׸��ϴ�." << "\n" << "�ؽ�Ʈ�� ���� ; �Դϴ�. 10000������ �����մϴ�." << endl;
	char c[10000];
	cin.getline(c, 10000, ';');
	
	int i;
	char j;
	int count = 0;
	for (i = 0; i < strlen(c); i++) {
		c[i] = tolower(c[i]);
		if (isalpha(c[i]) == 2) {
			count++;
		}
	}
	cout << '\n' << "�� ���ĺ� ��" << count << endl;
	
	int counta;

	for(j=97;j<=122;j++){
		counta = 0;
		for (i = 0; i < strlen(c); i++) {
			if (c[i] == j) {
				counta++;
			}
		}
		char ch = 'a';
		cout << j << "(" << counta << ")" << " : ";
		for (i = 0; i < counta; i++) {
			cout << "*";
		}
		cout << "\n";
	}
}