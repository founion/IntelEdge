#include <iostream>
#include <string>

using namespace std;

class LoopAdder
{
	string name;
	int x, y, sum;
	void read() {
		cout << name << ":" << endl;
		cout << "ó�� ������ �ι�° ������ ���մϴ�. �� ���� �Է��ϼ��� >> ";
		cin >> x >> y;
	}
	void write() {
		cout << x << "����" << y << "������ �� = " << sum << " �Դϴ�." << endl;
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

class WhileLoopAdder : public LoopAdder
{
protected:
	virtual int calculator() {
		int sum = 0;
		while
	}
public:
	WhileLoopAdder(string name) : LoopAdder(name) { }
};

class DowhileLoopAdder : public LoopAdder
{
public:
	DowhileLoopAdder(string name) : LoopAdder(name) { }
};

int main() {
	WhileLoopAdder whileLoop("While Loop");
	DoWhileLoopAdder dowhileLoop("Do while Loop");

	whileLoop.run();
	dowhileLoop.run();
}