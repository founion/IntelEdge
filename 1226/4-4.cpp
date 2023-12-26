#include <iostream>

using namespace std;

class Sample
{
	int* p;
	int size;
public:
	Sample(int n) { size = n; p = new int[n]; }
	~Sample() { }
	void read() {
		for (int i = 0; i < 10; i++) {
			cin >> p[i];
		}
	}
	void write() { 
		for (int i = 0; i < 10; i++) {
			cout << p[i] << " ";
		}
	}
	int big() {
		int max = p[0];
		for (int i = 1; i < 10; i++) {
			if (max < p[i]) max = p[i];
		}
		return max;
	}
};

int main() {
	Sample s(10);
	s.read();
	s.write();
	cout << endl << "가장 큰 수는 " << s.big() << endl;
}