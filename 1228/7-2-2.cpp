#include <iostream>

using namespace std;

class Book
{
	string title;
	int price, pages;
public:
	Book(string title = "", int price = 0, int pages = 0) { this->title = title; this->price = price; this->pages = pages; }
	void show() { cout << title << ' ' << price << "원 " << pages << " 페이지" << endl; }
	string getTitle() { return title; }
	friend bool operator==(Book b1, int p);
	friend bool operator==(Book b1, string name);
	friend bool operator==(Book b1, Book b2);
};

bool operator==(Book b1, int p) {
	if (b1.price == p) return true;
	else return false;
}

bool operator==(Book b1, string name) {
	if (b1.title == name) return true;
	else return false;
}

bool operator==(Book b1, Book b2) {
	if (b1.title == b2.title && b1.price == b2.price && b1.pages == b2.pages) return true;
	else return false;
}

int main() {
	Book a("명품 C++", 30000, 500), b("고품 C++", 30000, 500);
	if (a == 30000) cout << "정가 30000원" << endl;
	if (a == "명품 C++") cout << "명품 C++ 입니다." << endl;
	if (a == b) cout << "두 책이 같은 책입니다." << endl;
	else cout << "두 책은 다른 책입니다." << endl;
}