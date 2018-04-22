#ifndef COLOR_H
#define COLOR_H

#include "nvector.h"

class Color : public NVector<int, 4>
{
public:
    static const Color RED;
    static const Color GREEN;
    static const Color BLUE;
    static const Color WHITE;

    Color(int r=255, int g=255, int b=255, int a = 255) : NVector<int, 4>(r,g,b,a) { }
    Color(NVector<int, 4> v) : NVector<int, 4>(v){}

    double getR() const { return data[0]; }
    Color& setR(double value) { data[0] = value; return *this; }
    double getG() const { return data[1]; }
    Color& setG(double value) { data[1] = value; return *this; }
    double getB() const { return data[2]; }
    Color& setB(double value) { data[2] = value; return *this; }
    double getA() const { return data[3]; }
    Color& setA(double value) { data[3] = value; return *this; }
};

#endif // COLOR_H
