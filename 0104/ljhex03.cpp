#include <iostream>

using namespace std;

class Calculator
{
public:
	int x, y, z;
	Calculator(int x, int y, int z) { this->x = x; this->y = y; this->z = z; };
	virtual void show() { cout << "x : " << x << "," << "y : " << y << endl; }
};

class Adder : public Calculator
{
public:
	Adder(int x, int y) : Calculator(x, y, z) { this->x = x; this->y = y; this->z = 0; }
	void sum() { z = x + y; }
	virtual void show() { cout << x << " + " << y << " = " << z << endl; }
};

class Subtract : public Calculator
{
public:
	Subtract(int x, int y) : Calculator(x, y, z) { this->x = x; this->y = y; this -> z = 0; }
	void sub() { z = x - y; }
	virtual void show() { cout << x << " - " << y << " = " << z << endl; }
};

class Multiply : public Calculator
{
public:
	Multiply(int x, int y) : Calculator(x, y, z) { this->x = x; this->y = y; this->z = 0; }
	void mul() { z = x * y; }
	virtual void show(){ cout << x << " * " << y << " = " << z << endl; }
};

class Divide : public Calculator
{
public:
	Divide(int x, int y) : Calculator(x, y, z) { this->x = x; this->y = y; this->z = 0; }
	void div() {
		if (y == 0) {
			cout << "잘못된 값을 입력하였습니다." << endl;
			return;
		}
		z = x / y;
	}
	virtual void show() { cout << x << " / " << y << " = " << z << endl; }
};

int main() {
	Adder a(4,2);
	a.sum();
	a.show();

	Subtract b(524, 213);
	b.sub();
	b.show();

	Multiply c(42, 6);
	c.mul();
	c.show();

	Divide d(54, 5);
	d.div();
	d.show();
}