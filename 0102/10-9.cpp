#include <iostream>
#include <vector>

using namespace std;

int main() {
	vector<int> v;
	int n;
	while(true){
		cout << "정수를 입력하세요(0을 입력하면 종료)>>";
		cin >> n;
		int sum = 0;
		if (n == 0) return 0;
		
		v.push_back(n);
		for (int i = 0; i < v.size(); i++) {
			cout << v[i] << ' ';
			sum += v[i];
		}
		cout << endl << "평균 = " << (double)sum / v.size() << endl;	
	}
}