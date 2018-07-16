
#ifndef TF_RATIONAL_H
#define TF_RATIONAL_H

#include <cmath>

template <class numtype> class TFRational {
public:
    using denomType = long;
public:
    TFRational() : num(1), den(1) { };
    TFRational(const numtype &x) : num(x), den(1) { };
    TFRational(const numtype &n,denomType &d) : num(n), den(d) { };
    TFRational(const TFRational &x) : num(x.num), den(x.den) { };
public:
    TFRational &operator=(const numtype &x) {
        num = x;
        den = 1;
        return *this;
    }
    TFRational &operator=(const TFRational &x) {
        num = x.num;
        den = x.den;
        return *this;
    }
    double value(void) const {
        return num / den;
    }
public:
    numtype                 num;
    denomType               den;
};

typedef TFRational<double> TFFloatRational;
typedef TFRational<long> TFLongRational;

#endif //TF_RATIONAL_H

