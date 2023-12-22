#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class Date
{
public:
	Date(int y, int m, int d);
	Date(string datestr);
	int getYear();
	int getMonth();
	int getDay();
	void show();
private:
	int year, month, day;
};

Date::Date(int y, int m, int d)
{
	year = y;
	month = m;
	day = d;
}

Date::Date(string datestr)
{
	stringstream ss(datestr);
	string syear, smonth, sday;

	getline(ss, syear, '/');
	getline(ss, smonth, '/');
	getline(ss, sday, '/');
	year = stoi(syear);
	month = stoi(smonth);
	day = stoi(sday);
}

int Date::getYear()
{
	return year;
}

int Date::getMonth()
{
	return month;
}

int Date::getDay()
{
	return day;
}

void Date::show()
{
	cout << year << "³â" << month << "¿ù" << day << "ÀÏ" << endl;
}

int main() {
	Date birth(2014, 3, 20);
	Date independenceDay("1945/8/15");
	independenceDay.show();
	cout << birth.getYear() << ',' << birth.getMonth() << ',' << birth.getDay() << endl;
}