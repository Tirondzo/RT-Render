#ifndef NVECTOR_H
#define NVECTOR_H

#include <cstddef>
#include <cmath>
#include <typeinfo>

template <typename T, const std::size_t N>
class NVector
{
protected:
    T data[N] {};
public:
    template <typename ...Args>
    constexpr NVector(const Args&... args) : data{args...}
    {
    }

    typedef class NVector<T,N> this_type;
    typedef T value_type;
    inline static int size(void) { return N; }

    T& operator [] (const std::size_t index){
        return data[index];
    }
    const T& operator [] (const std::size_t index) const{
        return data[index];
    }

    inline virtual this_type operator + (this_type const &v) const{
        this_type new_one{};
        for(int i = 0; i < N; i++){
            new_one.data[i] = data[i] + v.data[i];
        }
        return new_one;
    }

    template<typename T2>
    this_type& operator += (NVector<T2,N> const &v){
        for(int i = 0; i < N; i++){
            operator [](i) += v.operator [](i);
        }
        return *this;
    }

    inline virtual this_type& operator - (){
        for(int i = 0; i < N; i++){
            data[i] = -data[i];
        }
        return *this;
    }
    inline virtual this_type operator - (this_type const & v) const{
        this_type new_one{};
        for(int i = 0; i < N; i++){
            new_one.data[i] = data[i] - v.data[i];
        }
        return new_one;
    }
    inline virtual this_type& operator -= (this_type const & v){
        for(int i = 0; i < N; i++){
            data[i] -= v.data[i];
        }
        return *this;
    }
    inline virtual this_type operator * (this_type const & v) const{
        this_type new_one{};
        for(int i = 0; i < N; i++){
            new_one.data[i] = data[i] * v.data[i];
        }
        return new_one;
    }
    inline virtual this_type& operator *= (this_type const & v){
        for(int i = 0; i < N; i++){
            data[i] *= v.data[i];
        }
        return *this;
    }

    inline virtual this_type operator / (this_type const & v) const{
        this_type new_one{};
        for(int i = 0; i < N; i++){
            new_one.data[i] = data[i] / v.data[i];
        }
        return new_one;
    }
    inline virtual this_type& operator /= (this_type const & v){
        for(int i = 0; i < N; i++){
            data[i] /= v.data[i];
        }
        return *this;
    }

    template <typename Scalar,typename std::enable_if<std::is_scalar<Scalar>::value>::type* = nullptr>
    inline this_type operator* (Scalar const &s) const{
        this_type new_one{};
        for(int i = 0; i < N; i++){
            new_one.data[i] = data[i] * s;
        }
        return new_one;
    }
    template <typename Scalar,typename std::enable_if<std::is_scalar<Scalar>::value>::type* = nullptr>
    inline this_type& operator *= (Scalar const &s){
        static_assert(std::is_scalar<Scalar>::value, "Only scalar types");
        for(int i = 0; i < N; i++){
            data[i] *= s;
        }
        return *this;
    }

    template <typename Scalar>
    inline this_type operator / (Scalar const &s) const{
        this_type new_one{};
        for(int i = 0; i < N; i++){
            new_one.data[i] = data[i] / s;
        }
        return new_one;
    }
    template <typename Scalar>
    inline this_type& operator /= (Scalar const &s){
        for(int i = 0; i < N; i++){
            data[i] /= s;
        }
        return *this;
    }


    inline virtual T dot(const this_type &v){
        T res{};
        for(int i = 0; i < N; i++){
            res += data[i] * v.data[i];
        }
        return res;
    }

    static inline T dot(const this_type &a, const this_type &b){
        T res{};
        for(int i = 0; i < N; i++){
            res += a.data[i] * b.data[i];
        }
        return res;
    }

    static inline NVector<T,3> cross(const NVector<T,3>& a, const NVector<T,3>& b)
    {
        return NVector<T,3>(a.data[1] * b.data[2] - b.data[1] * a.data[2],
                        a.data[2] * b.data[0] - b.data[2] * a.data[0],
                        a.data[0] * b.data[1] - b.data[0] * a.data[1]);
    }

    double invsqrtQuake( double number ) const
  {
      double y = number;
      double x2 = y * 0.5;
      std::int64_t i = *(std::int64_t *) &y;
      // The magic number is for doubles is from https://cs.uwaterloo.ca/~m32rober/rsqrt.pdf
      i = 0x5fe6eb50c7b537a9 - (i >> 1);
      y = *(double *) &i;
      y = y * (1.5 - (x2 * y * y));   // 1st iteration
      //      y  = y * ( 1.5 - ( x2 * y * y ) );   // 2nd iteration, this can be removed
      return y;
  }

    virtual inline this_type normalize() const{
        T len{};
        this_type new_one(*this);
        for(int i = 0; i < N; i++){
            len += data[i] * data[i];
        }
        return new_one*invsqrtQuake(len);
    }

    virtual inline T length() const{
        return sqrt(slength());
    }

    virtual inline T slength() const{
        T len{};
        for(int i = 0; i < N; i++){
            len += data[i] * data[i];
        }
        return len;
    }
};


#endif // NVECTOR_H
