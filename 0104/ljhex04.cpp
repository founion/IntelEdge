#include <iostream>

using namespace std;

class BankAccount
{
	string name;
	int id, balance, dp = 0, wd = 0;
public:
	BankAccount(string name, int id, int balance) { 
		this->name = name; this->id = id; this->balance = balance;
		cout << "ÀºÇà °èÁÂ ¿­±â" << endl;
	}
	~BankAccount() { cout << "ÀºÇà °èÁÂ ´Ý±â" << endl; }
	string getOwner() { return name; }
	void setOwner() { this->name = name; }
	int inquiry() { return balance + dp - wd; }
	int deposit(int d) {
		dp += d;
		return dp;
	}
	int withdraw(int w) {
		wd += w;
		return wd;
	}
};

int main() {
	BankAccount a("kitae", 1, 5000);
	a.deposit(50000);
	cout << a.getOwner() << "ÀÇ ÀÜ¾×Àº " << a.inquiry() << "¿ø" << endl;
	a.withdraw(20000);
	cout << a.getOwner() << "ÀÇ ÀÜ¾×Àº " << a.inquiry() << "¿ø" << endl;
}
