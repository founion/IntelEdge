#include <iostream>

using namespace std;

class Person
{
	int id;
	double weight;
	string name;
public:
	Person() { id = 1; weight = 20.5; name = "Grace"; }
	Person(int a, string s) { id = a; weight = 20.5; name = s; }
	Person(int a, string s, double b) { id = a; weight = b; name = s; }
	void show() { cout << id << ' ' << weight << ' ' << name << endl; }
};

int main() {
	Person grace, ashley(2, "Ashley"), helen(3, "helen", 32.5);
	grace.show();
	ashley.show();
	helen.show();
}