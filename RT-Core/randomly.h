#ifndef RANDOMLY_H
#define RANDOMLY_H

#include <random>

class XorShiftRandomEngine{

    uint_fast64_t s[2]{123456789, 362436069};
public:
    constexpr static uint_fast64_t max(){
        return UINT_FAST64_MAX;
    }
    constexpr static uint_fast64_t min(){
        return 0;
    }

    XorShiftRandomEngine(){
        s[0] = 123456789;
        s[1] = 362436069;
    }
    XorShiftRandomEngine(std::random_device &rd){
        std::uniform_int_distribution<uint_fast64_t> dist(min(), max());
        s[0] = dist(rd);
        s[1] = dist(rd);
    }

    //xorshift+ right from wiki
    uint_fast64_t operator()(){
        uint_fast64_t x = s[0];
        uint_fast64_t const y = s[1];
        s[0] = y;
        x ^= x << 23; // a
        s[1] = x ^ y ^ (x >> 17) ^ (y >> 26); // b, c
        return s[1] + y;
    }
};

class Randomly
{
protected:
    XorShiftRandomEngine mt;
    std::uniform_real_distribution<float> fDist;
    std::uniform_real_distribution<double> dDist;
public:
    Randomly() : fDist(0,1), dDist(0,1) {
        std::random_device rd;
        mt = XorShiftRandomEngine(rd);
    }
};

#endif // RANDOMLY_H
