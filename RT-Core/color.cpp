#include "color.h"

int r,g,b,a;

Color::Color(int r, int g, int b, int a = 255) : r(r), g(g), b(b), a(a)
{
}

int Color::getR() const { return r; }
void Color::setR(int value) { r = value; }

int Color::getG() const { return g; }
void Color::setG(int value) { g = value; }

int Color::getB() const { return b; }
void Color::setB(int value) { b = value; }

int Color::getA() const { return a; }
void Color::setA(int value) { a = value; }

