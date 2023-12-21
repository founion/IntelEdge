#include <iostream>

using namespace std;

int main() {
	int f, n;

	cout << "***** 승리장에 오신 것을 환영합니다.  *****" << endl;
	while (1) {		
		cout << "짬뽕:1, 짜장:2, 군만두:3, 종료:4>>";
		cin >> f;
		if (f == 1 || f == 2 || f == 3) {
			cout << "몇인분?";
			cin >> n;
		}
		if (f == 1) {
			cout << "짬뽕 " << n << "인분 나왔습니다." << endl;
		}
		else if (f == 2) {
			cout << "짜장 " << n << "인분 나왔습니다." << endl;
		}
		else if (f == 3) {
			cout << "군만두 " << n << "인분 나왔습니다." << endl;
		}
		else if (f == 4) {
			cout << "오늘 영업은 끝났습니다." << endl;
			break;
		}
		else {
			cout << "다시 주문하세요!!" << endl;
		}
	}
}