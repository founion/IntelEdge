#include <iostream>

using namespace std;

class Account
{
public:
	Account(string str, int i, int b);
	string getOwner();     // ������
	int inquiry();       // �ܾ�
	int deposit(int d);  // ����
	int withdraw(int w); // ���
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
	cout << a.getOwner() << "�� �ܾ���" << a.inquiry() << endl;
	int money = a.withdraw(20000);
	cout << a.getOwner() << "�� �ܾ���" << a.inquiry() << endl;
}