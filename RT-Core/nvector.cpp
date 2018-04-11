#include "nvector.h"

template<typename T, const std::size_t N>
inline NVector::this_type NVector::operator +(const NVector::this_type &v) const
{
    this_type new_one;
    for(int i = 0; i < N; i++){
        new_one.data[i] = data[i] + v.data[i];
    }
    return new_one;
}

template<typename T, const std::size_t N>
inline NVector::this_type &NVector::operator +=(const NVector::this_type &v)
{
    for(int i = 0; i < N; i++){
        data[i] += v.data[i];
    }
    return *this;
}
