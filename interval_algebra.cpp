#include "interval_algebra.hh"

static double specialmult(double a, double b)
{
    // we want inf*0 to be 0
    return ((a == 0.0) || (b == 0.0)) ? 0.0 : a * b;
}

static double min4(double a, double b, double c, double d)
{
    return std::min(std::min(a, b), std::min(c, d));
}

static double max4(double a, double b, double c, double d)
{
    return std::max(std::max(a, b), std::max(c, d));
}

//==========================================================================================
//
// interval operations
//
//==========================================================================================

interval interval_algebra::add(const interval& x, const interval& y) const
{
    return {x.lo() + y.lo(), x.hi() + y.hi()};
}

interval interval_algebra::sub(const interval& x, const interval& y) const
{
    return {x.lo() - y.hi(), x.hi() - y.lo()};
}

interval interval_algebra::mul(const interval& x, const interval& y) const
{
    if (x.empty() || y.empty()) {
        return {};
    } else {
        double a = specialmult(x.lo(), y.lo());
        double b = specialmult(x.lo(), y.hi());
        double c = specialmult(x.hi(), y.lo());
        double d = specialmult(x.hi(), y.hi());
        return interval(min4(a, b, c, d), max4(a, b, c, d));
    }
}

interval interval_algebra::inv(const interval& x) const
{
    if ((x.lo() >= 0) || (x.hi() <= 0)) {
        return {1 / x.hi(), 1 / x.lo()};
    } else {
        return {-INFINITY, +INFINITY};
    }
}

interval interval_algebra::div(const interval& x, const interval& y) const
{
    return mul(x, inv(y));
}
