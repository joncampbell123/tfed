
/* https://en.wikipedia.org/wiki/Binary_GCD_algorithm */
template <class T=unsigned long> T gcd_u(const T u,const T v)
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
            return gcd_u(u >> 1ul, v);
        else // both u and v are even
            return gcd_u(u >> 1ul, v >> 1ul) << 1ul;
    }

    if (~v & 1) // u is odd, v is even
        return gcd_u(u, v >> 1ul);

    // reduce larger argument
    if (u > v)
        return gcd_u((u - v) >> 1ul, v);

    return gcd_u((v - u) >> 1ul, u);
}

