#include <iostream>
#include <string>

using namespace std;

class LoopAdder
{
	string name;
	int x, y, sum;
	void read() {
		cout << name << ":" << endl;
		cout << "처음 수에서 두번째 수까지 더합니다. 두 수를 입력하세요 >> ";
		cin >> x >> y;
	}
	void write() {
		cout << x << "에서" << y << "까지의 합 = " << sum << " 입니다." << endl;
	}
protected:
	LoopAdder(string name = "") { this->name = name; }
	int getX() { return x; }
	int getY() { return y; }
	virtual int calculator() = 0;
public:
	void run() {
		read();
		sum = calculator();
		write();
	}
};

class ForLoopAdder : public LoopAdder
{
protected:
	virtual int calculator(){
		int sum = 0;
		for (int i = getX(); i <= getY(); i++) sum += i;
		return sum;
	}
public:
	ForLoopAdder(string name) : LoopAdder(name) { }
};

int main() {
	ForLoopAdder forLoop("For Loop");
	forLoop.run();
}
