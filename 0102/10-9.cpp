#include <iostream>
#include <vector>

using namespace std;

int main() {
	vector<int> v;
	int n;
	while(true){
		cout << "������ �Է��ϼ���(0�� �Է��ϸ� ����)>>";
		cin >> n;
		int sum = 0;
		if (n == 0) return 0;
		
		v.push_back(n);
		for (int i = 0; i < v.size(); i++) {
			cout << v[i] << ' ';
			sum += v[i];
		}
		cout << endl << "��� = " << (double)sum / v.size() << endl;	
	}
}