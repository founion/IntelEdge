#include <iostream>

using namespace std;

class Shape
{
public:
	virtual void draw(){ }
};

class Circle : public Shape
{
protected:
	virtual void draw() { cout << "Circle�� �׸���." << endl; }
};

class Rect : public Shape
{
protected:
	virtual void draw() { cout << "Rectangle�� �׸���." << endl; }
};

class Line : public Shape
{
protected:
	virtual void draw() { cout << "Line�� �׸���." << endl; }
};

void paint(Shape* p) {
	p->draw();
}

int main() {
	paint(new Circle());
	paint(new Rect());
	paint(new Line());
}