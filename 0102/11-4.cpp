#include <iostream>

using namespace std;

int main() {
	char ch;
	cout << "'영어문장;한글문장'을 입력하세요(ctrl z를 누르면 종료)>>" << endl;
	while ((ch = cin.get()) != EOF) {
		if (ch == ';') {
			cout.put('\n');
			cin.ignore(100, '\n');
		}
		else cout.put(ch);
	}
}