#include <iostream>

using namespace std;

class Account
{
public:
	Account(string str, int i, int b);
	string getOwner();     // 예금주
	int inquiry();       // 잔액
	int deposit(int d);  // 저금
	int withdraw(int w); // 출금
private:
	string name;
	int id, balance, dp = 0, wd = 0;
};

Account::Account(string str, int i, int b)
{
	name = str;
	id = i;
	balance = b;
}

string Account::getOwner()
{
	return name;
}

int Account::inquiry()
{
	return balance+dp-wd;
}

int Account::deposit(int d)
{
	dp += d;
	return dp;
}

int Account::withdraw(int w)
{
	wd += w;
	return wd;
}

int main() {
	Account a("kitae", 1, 5000);
	a.deposit(50000);
	cout << a.getOwner() << "의 잔액은" << a.inquiry() << endl;
	int money = a.withdraw(20000);
	cout << a.getOwner() << "의 잔액은" << a.inquiry() << endl;
}