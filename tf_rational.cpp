
#include <map>
#include <string>
#include <exception>

#include "tf_rational.h"
#include "tf_gcd.h"

template <> void TFULongRational::reduce(void) {
    unsigned long g = gcd_u<unsigned long>(num,den);

    if (num % g || den % g)
        throw std::runtime_error("gcd fail");

    num /= g;
    den /= g;
}

