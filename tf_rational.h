
#ifndef TF_RATIONAL_H
#define TF_RATIONAL_H

#include <cmath>

template <class numtype,class denomtype=long> class TFRational {
public:
    using numType = numtype;
    using denomType = denomtype;
public:
    TFRational() : num(1), den(1) { };
    TFRational(const numType &x) : num(x), den(1) { };
    TFRational(const numType &n,const denomType &d) : num(n), den(d) { };
    TFRational(const TFRational &x) : num(x.num), den(x.den) { };
public:
    TFRational &operator=(const numType &x) {
        num = x;
        den = 1;
        return *this;
    }
    TFRational &operator=(const TFRational &x) {
        num = x.num;
        den = x.den;
        return *this;
    }
    long double value(void) const {
        return (long double)num / den;
    }
public:
    numType                 num;
    denomType               den;
};

typedef TFRational<unsigned long,unsigned long> TFULongRational;
typedef TFRational<double,long> TFFloatRational; /* <- reminder: x86 FILD m64int */
typedef TFRational<long,long> TFLongRational;

#endif //TF_RATIONAL_H

