#include <iostream>
#include <string>

using namespace std;

int main() {
	cout << "에스프레소 2000원, 아메리카노 2300원, 카푸치노 2500원입니다." << endl;

	int n;
	int sum = 0;
	string str;

	while (1) {
		cout << "주문>>";
		cin >> str >> n;

		if (str == "에스프레소") {
			int p1 = n * 2000;
			cout << p1 << "원입니다. 맛있게 드세요" << endl;
			sum += p1;
		}
		else if (str == "아메리카노") {
			int p2 = n * 2300;
			cout <<p2 << "원입니다. 맛있게 드세요" << endl;
			sum += p2;
		}
		else if (str == "카푸치노") {
			int p3 = n * 2500;
			cout << p3 << "원입니다. 맛있게 드세요" << endl;
			sum += p3;
		}
		
		if (sum >= 20000) {
			cout << "오늘 " << sum << "원을 판매하여 카페를 닫습니다. 내일봐요~~" << endl;
			break;
		}
	}
}