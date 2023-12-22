#include "Exp.h"

Exp::Exp()
{
	base = 1;
	power = 1;
}

Exp::Exp(int a)
{
	base = a;
	power = 1;
}

Exp::Exp(int b, int c)
{
	base = b;
	power = c;
}

int Exp::getValue()
{
	int i;
	for (i = 0; i < power; i++) {
		count *= base;
	}
	return count;
}

int Exp::getBase()
{
	return base;
}

int Exp::getExp()
{
	return power;
}

bool Exp::equals(Exp b)
{
	if (count == b.getBase()) return true;
	else return false;
}
