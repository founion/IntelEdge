#include <iostream>

using namespace std;

class Power
{
	int kick;
	int punch;
public:
	Power(int kick = 0, int punch = 0) { this->kick = kick; this->punch = punch; }
	void show() { cout << "kick = " << kick << ',' << "punch = " << punch << endl; }
	Power operator+(int op2);
};

Power Power::operator+(int op2) {
	Power tmp;
	tmp.kick = kick + op2;
	tmp.punch = punch + op2;
	return tmp;
}

int main() { 
	Power a(3, 5), b;
	a.show();
	b.show();
	b = a + 2;
	a.show();
	b.show();
}