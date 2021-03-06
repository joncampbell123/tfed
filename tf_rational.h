
#ifndef TF_RATIONAL_H
#define TF_RATIONAL_H

#include <cmath>
#include <iostream>

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
    void reduce(void);
    numType gcd(numType a,denomType b);
    long double value(void) const {
        return (long double)num / den;
    }
public:
    numType                 num;
    denomType               den;
};

template <class numtype,class denomtype=long> std::ostream& operator<<(std::ostream& os,TFRational<numtype,denomtype> &r) {
    return os << r.num << ":" << r.den;
}

typedef TFRational<unsigned long,unsigned long> TFULongRational;
typedef TFRational<long double,long> TFFloatRational; /* <- reminder: x86 FILD m64int */
typedef TFRational<long,long> TFLongRational;

template <> void TFULongRational::reduce(void);

#endif //TF_RATIONAL_H

