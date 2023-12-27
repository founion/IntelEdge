#include <iostream>

using namespace std;

class ArrayUtillity2
{
public:
	static int* concat(int s1[], int s2[], int size);
	static int* remove(int s1[], int s2[], int size, int& retSize);
};

int* ArrayUtillity2::concat(int s1[], int s2[], int size) {
	int* p = new int[size * 2];
	if (!p) return NULL;
	for (int i = 0; i < size; i++) p[i] = s1[i];
	for (int i = 5; i < size * 2; i++) p[i] = s2[i - size];
	return p;
}

int* ArrayUtillity2::remove(int s1[], int s2[], int size, int& retSize) {
	int* p = new int[size * 2];
	if (!p) {
		retSize = 0;
		return NULL;
	}

	int k = 0;
	for (int i = 0; i < size; i++) {
		int j = 0;
		for (int j = 0; j < size; j++) {
			if (s1[i] == s2[j]) break;
		}
		if (j == size) {
			p[k] = s1[i];
			k++;
		}
		
	}
	retSize = k;
	if (k == 0) return NULL;

	int* q = new int[retSize];
	if (!q) {
		retSize = 0;
		return NULL;
	}
	for (int i = 0; i < retSize; i++) q[i] = p[i];

	delete[] p;
	return q;
}

int main() {
	cout << "정수를 5개 입력하라. 배열 x에 삽입한다>>";
	int nx[5];
	for (int i = 0; i < 5; i++) cin >> nx[i];
	cout << "정수 5개를 입력하라. 배열 y에 삽입한다>>";
	int ny[5];
	for (int i = 0; i < 5; i++) cin >> ny[i];

	int* p = ArrayUtillity2::concat(nx, ny, 5);
	cout << "합친 정수 배열을 출력한다" << endl;
	for (int i = 0; i < 10; i++) cout << p[i] << ' ';
	cout << endl;

	int retSize;
	int* q = ArrayUtillity2::remove(nx, ny, 5, retSize);
	cout << "배열 x[]에서 y[]를 뺀 결과를 출력한다. 개수는 " << retSize << endl;
	for (int i = 0; i < retSize; i++) cout << q[i] << ' ';
	
}