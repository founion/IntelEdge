#include <iostream>

using namespace std;

class Color
{
	int red, green, blue;
public:
	Color(int r = 0, int g = 0, int b = 0) { red = r; green = g; blue = b; }
	void setcolor(int r, int g, int b) { red = r; green = g; blue = b; }
	void show() { cout << red << ' ' << green << ' ' << blue << endl; }
	Color operator+(Color c2);
	bool operator==(Color c2);
};

Color Color::operator+(Color c2) {
	Color tmp;
	tmp.red = this->red + c2.red;
	tmp.green = this->green + c2.green;
	tmp.blue = this->blue + c2.blue;
	return tmp;
}

bool Color::operator==(Color c2) {
	if (this->red == c2.red && this->green == c2.green && this->blue == c2.blue) return true;
	else return false;
}

int main() {
	Color red(255, 0, 0), blue(0, 0, 255), c;
	c = red + blue;
	c.show();

	Color fuchsia(255, 0, 255);
	if (c == fuchsia) cout << "보라색 맞음";
	else cout << "보라색 아님";
}