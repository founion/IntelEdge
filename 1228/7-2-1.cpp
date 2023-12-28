#include <iostream>

using namespace std;

class Book
{
	string title;
	int price, pages;
public:
	Book(string title = "", int price = 0, int pages = 0) { this->title = title; this->price = price; this->pages = pages; }
	void show() { cout << title << ' ' << price << "�� " << pages << " ������" << endl; }
	string getTitle() { return title; }
	bool operator==(int p);
	bool operator==(string name);
	bool operator==(Book b2);
};

bool Book::operator==(int p) {
	if (price == p) return true;
	else return false;
}

bool Book::operator==(string name) {
	if (title == name) return true;
	else return false;
}

bool Book::operator==(Book b2) {
	if (title == b2.title && price == b2.price && pages == b2.pages) return true;
	else return false;
}

int main() {
	Book a("��ǰ C++", 30000, 500), b("��ǰ C++", 30000, 500);
	if (a == 30000) cout << "���� 30000��" << endl;
	if (a == "��ǰ C++") cout << "��ǰ C++ �Դϴ�." << endl;
	if (a == b) cout << "�� å�� ���� å�Դϴ�." << endl;
	else cout << "�� å�� �ٸ� å�Դϴ�." << endl;
}