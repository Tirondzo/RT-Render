#ifndef COLOR_H
#define COLOR_H

#include <Eigen/Core>
#include <Eigen/Dense>

using namespace Eigen;
class Color : public Matrix<int,4,1>
{
    typedef Eigen::Matrix<int,4,1> base_type;
    typedef int base_type_val;
public:
    static const Color RED;
    static const Color GREEN;
    static const Color BLUE;
    static const Color WHITE;

    Color(base_type_val r=255,
          base_type_val g=255,
          base_type_val b=255,
          base_type_val a=255) : base_type(r,g,b,a) { }

    template<typename OtherDerived>
    Color(const Eigen::MatrixBase<OtherDerived>& other)
        : base_type(other) { }

    template<typename OtherDerived>
    Color& operator=(const Eigen::MatrixBase<OtherDerived>& other)
    {
        this->base_type::operator=(other);
        return *this;
    }

    base_type_val getR() const { return (*this)[0]; }
    Color& setR(base_type_val value) { (*this)[0] = value; return *this; }
    base_type_val getG() const { return (*this)[1]; }
    Color& setG(base_type_val value) { (*this)[1] = value; return *this; }
    base_type_val getB() const { return (*this)[2]; }
    Color& setB(base_type_val value) { (*this)[2] = value; return *this; }
    base_type_val getA() const { return (*this)[3]; }
    Color& setA(base_type_val value) { (*this)[3] = value; return *this; }
};

#endif // COLOR_H
