#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval.hh"
#include "interval_algebra.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Pow
// interval Pow(const interval& x, const interval& y) const;
// void testPow() const;

interval interval_algebra::Pow(const interval& x, const interval& y) const
{
    if (x.lo() > 0) {
        // Simple case
        return Exp(Mul(y, Log(x)));

    } else {
        return {};
    }
}

static double myPow(double x, double y)
{
    return pow(x, y);
}

void interval_algebra::testPow() const
{
    analyzeBinaryMethod(10, 2000, "Pow", interval(1, 1000), interval(-10, 10), myPow, &interval_algebra::Pow);
    analyzeBinaryMethod(10, 2000, "Pow", interval(0.001, 1), interval(-10, 10), myPow, &interval_algebra::Pow);
    analyzeBinaryMethod(10, 2000, "Pow", interval(0.001, 10), interval(-20, 20), myPow, &interval_algebra::Pow);
}
}  // namespace itv
