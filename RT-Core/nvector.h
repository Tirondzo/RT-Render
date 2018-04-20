#ifndef NVECTOR_H
#define NVECTOR_H

#include <cstddef>
#include <cmath>

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

    inline T& operator [] (std::size_t index){
        return data[index];
    }

    inline virtual this_type operator + (this_type const &v) const{
        this_type new_one{};
        for(int i = 0; i < N; i++){
            new_one.data[i] = data[i] + v.data[i];
        }
        return new_one;
    }
    inline virtual this_type& operator += (this_type const &v){
        for(int i = 0; i < N; i++){
            data[i] += v.data[i];
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

    template <typename Scalar>
    inline this_type operator* (Scalar const &s) const{
        this_type new_one{};
        for(int i = 0; i < N; i++){
            new_one.data[i] = data[i] * s;
        }
        return new_one;
    }
    template <typename Scalar>
    inline this_type& operator *= (Scalar const &s){
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

    virtual inline this_type normalize() const{
        T len{};
        this_type new_one(*this);
        for(int i = 0; i < N; i++){
            len += data[i] * data[i];
        }
        return new_one/sqrt(len);
    }

    virtual inline T length() const{
        T len{};
        for(int i = 0; i < N; i++){
            len += data[i] * data[i];
        }
        return sqrt(len);
    }
};


#endif // NVECTOR_H
