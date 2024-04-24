#ifndef UTILS_CC
#define UTILS_CC

#include <iostream>
#include <set>
#include <vector>
#include <chrono>


typedef unsigned int uint;
typedef unsigned long ulong;

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

#endif