#pragma once
class Exp
{
public:
	Exp();
	Exp(int a);
	Exp(int b, int c);
	int getValue();
	int getBase();
	int getExp();
	bool equals(Exp b);

private:
	int power, base;
	int count = 1;
};
