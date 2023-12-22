#include <iostream>

using namespace std;

class CoffeeMachine
{
public:
	CoffeeMachine(int c, int w, int s);
	int drinkEspresso();
	int drinkAmericano();
	int drinkSugarCoffee();
	int fill();
	void show();
private:
	int coffee, water, sugar;
};

CoffeeMachine::CoffeeMachine(int c, int w, int s)
{
	coffee = c;
	water = w;
	sugar = s;
}

int CoffeeMachine::drinkEspresso()
{
	coffee -= 1;
	water -= 1;
	return coffee, water, sugar;
}

int CoffeeMachine::drinkAmericano()
{
	coffee -= 1;
	water -= 2;
	return coffee, water, sugar;
}

int CoffeeMachine::drinkSugarCoffee()
{
	coffee -= 1;
	water -= 2;
	sugar -= 1;
	return coffee, water, sugar;
}

int CoffeeMachine::fill()
{
	coffee = 10;
	water = 10;
	sugar = 10;
	return coffee, water, sugar;
}

void CoffeeMachine::show()
{
	cout << "커피 머신 상태, 커피:" << coffee << "\t물:" << water << "\t설탕:" << sugar << endl;
}

int main() {
	CoffeeMachine java(5, 10, 3);
	java.drinkEspresso();
	java.show();
	java.drinkAmericano();
	java.show();
	java.drinkSugarCoffee();
	java.show();
	java.fill();
	java.show();
}