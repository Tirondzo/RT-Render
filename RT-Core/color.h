#ifndef COLOR_H
#define COLOR_H


class Color
{
public:
    static const Color RED;
    static const Color GREEN;
    static const Color BLUE;
    static const Color WHITE;

    Color(int r, int g, int b, int a = 255);

    Color operator * (double s);
    Color & operator *= (const double s);

    Color operator * (const Color &c);
    Color & operator *= (const Color &c);

    Color operator + (const Color &c);
    Color & operator += (const Color &c);

    Color operator / (double s);
    Color & operator /= (const double s);

    int getR() const;
    Color& setR(int value);
    int getG() const;
    Color& setG(int value);
    int getB() const;
    Color& setB(int value);
    int getA() const;
    Color& setA(int value);
};

#endif // COLOR_H
