
#include <map>
#include <string>
#include <exception>

#include "tf_rational.h"

/* https://en.wikipedia.org/wiki/Binary_GCD_algorithm */
template <> unsigned long TFULongRational::gcd(unsigned long u, unsigned long v)
{
    // simple cases (termination)
    if (u == v)
        return u;

    if (u == 0)
        return v;

    if (v == 0)
        return u;

    // look for factors of 2
    if (~u & 1ul) // u is even
    {
        if (v & 1ul) // v is odd
            return gcd(u >> 1ul, v);
        else // both u and v are even
            return gcd(u >> 1ul, v >> 1ul) << 1ul;
    }

    if (~v & 1) // u is odd, v is even
        return gcd(u, v >> 1ul);

    // reduce larger argument
    if (u > v)
        return gcd((u - v) >> 1ul, v);

    return gcd((v - u) >> 1ul, u);
}

template <> void TFULongRational::reduce(void) {
    unsigned long g = gcd(num,den);

    if (num % g || den % g)
        throw std::runtime_error("gcd fail");

    num /= g;
    den /= g;
}

