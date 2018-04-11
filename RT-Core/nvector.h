#ifndef NVECTOR_H
#define NVECTOR_H

#include <cstddef>

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
    inline static int size(void) { return len; }

    inline T& operator [] (std::size_t index){
        return data[index];
    }

    inline virtual this_type operator + (this_type const &v) const{
        this_type new_one;
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
        this_type new_one;
        for(int i = 0; i < N; i++){
            new_one.data[i] = data[i] + v.data[i];
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
        this_type new_one;
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
        this_type new_one;
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
    inline virtual this_type operator * (Scalar const &s) const{
        this_type new_one;
        for(int i = 0; i < N; i++){
            new_one.data[i] = data[i] * s;
        }
        return new_one;
    }
    template <typename Scalar>
    inline virtual this_type& operator *= (Scalar const &s){
        for(int i = 0; i < N; i++){
            data[i] *= s;
        }
        return *this;
    }

    template <typename Scalar>
    inline virtual this_type operator / (Scalar const &s) const{
        this_type new_one;
        for(int i = 0; i < N; i++){
            new_one.data[i] = data[i] / s;
        }
        return new_one;
    }
    template <typename Scalar>
    inline virtual this_type& operator /= (Scalar const &s){
        for(int i = 0; i < N; i++){
            data[i] /= s;
        }
        return *this;
    }


    inline virtual T dot(const this_type &v) const{
        T res{};
        for(int i = 0; i < N; i++){
            res += data[i] * v.data[i];
        }
        return res;
    }

    inline virtual T cross(const this_type &v) const;
    inline virtual T length() const;
    inline virtual this_type normalize();
};

#endif // NVECTOR_H
