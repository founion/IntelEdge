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
	virtual void draw() { cout << "Circle을 그린다." << endl; }
};

class Rect : public Shape
{
protected:
	virtual void draw() { cout << "Rectangle을 그린다." << endl; }
};

class Line : public Shape
{
protected:
	virtual void draw() { cout << "Line을 그린다." << endl; }
};

void paint(Shape* p) {
	p->draw();
}

int main() {
	paint(new Circle());
	paint(new Rect());
	paint(new Line());
}