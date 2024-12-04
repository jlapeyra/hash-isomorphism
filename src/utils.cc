#ifndef UTILS_CC
#define UTILS_CC

#include <iostream>
#include <set>
#include <vector>
#include <chrono>


typedef unsigned int uint;
typedef unsigned long long ulong;

/*class Printable {
    public: virtual std::ostream &print(std::ostream &os=std::cout) const = 0;
};

std::ostream &operator<<(std::ostream &os, const Printable& obj) {
    return obj.print(os);
}*/

template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
    os << "[";
    std::string sep = "";
    for (T x : v) {
        os << sep << x;
        sep = ", ";
    }
    os << "]";
    return os;
}

template <class T>
std::ostream &operator<<(std::ostream &os, const std::set<T> &v) {
    os << "{";
    std::string sep = "";
    for (T x : v) {
        os << sep << x;
        sep = ", ";
    }
    os << "}";
    return os;
}

template <
    class result_t   = std::chrono::milliseconds,
    class clock_t    = std::chrono::steady_clock,
    class duration_t = std::chrono::milliseconds
>
auto since(std::chrono::time_point<clock_t, duration_t> const& start)
{
    return std::chrono::duration_cast<result_t>(clock_t::now() - start);
}

//Mersenne primes
const ulong MERSENNE_19 = (2ULL << 19) - 1;
const ulong MERSENNE_31 = (2ULL << 31) - 1;
const ulong MERSENNE_61 = (2ULL << 61) - 1;

const ulong INF = ULLONG_MAX;


bool multOverflow(ulong a, ulong b) {
    //if (a == INF || b == INF) return true;
    if (b != 0 && a > INF / b) return true;
    if (a != 0 && b > INF / a) return true;
    return false;
}

ulong factorial(uint n) {
    ulong result = 1;
    for (ulong i = 1; i <= n; i++) {
        if (multOverflow(result, i)) return INF;
        else result *= i;
    }
    return result;
}




#endif