#include <iostream>

using namespace std;

class Book
{
	string title;
	string press;
	string author;
public:
	Book(string title = "", string press = "", string author = "") {
		this->title = title;
		this->press = press;
		this->author = author;
	}
	friend ostream& operator << (ostream& stream, Book b);
};

ostream& operator << (ostream& stream, Book b) {
	stream << b.title << "," << b.press << "," << b.author << endl;
	return stream;
}

int main() {
	Book book("������ �����", "�ѱ����ǻ�", "����������");
	cout << book;
}
