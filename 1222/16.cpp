#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

int main() {
	cout << "영문 텍스트를 입력하세요. 히스토그램을 그립니다." << "\n" << "텍스트의 끝은 ; 입니다. 10000개까지 가능합니다." << endl;
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
	cout << '\n' << "총 알파벳 수" << count << endl;
	
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