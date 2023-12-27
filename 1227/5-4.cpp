#include <iostream>

using namespace std;

bool bigger(int a, int b, int& big) {
	if (a == b) return true;
	
	big = a;
	if (big < b) big = b;
	return false;
}

int main() {
	cout << "두 정수를 입력하세요>> ";
	int n1, n2;
	cin >> n1 >> n2;

	int big = 0;
	if (bigger(n1, n2, big)) cout << "두 정수의 크기가 같습니다." << endl;
	else cout << "두 정수" << n1 << ',' << n2 << " 중 큰 수는 " << big << endl;
}