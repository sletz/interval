#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval.hh"
#include "interval_algebra.hh"

//------------------------------------------------------------------------------------------
// Interval Sinh
// interval Sinh(const interval& x) const;
// void testSinh() const;

interval interval_algebra::Sinh(const interval& x) const
{
    if (x.isEmpty()) {
        return x;
    } else {
        return {sinh(x.lo()), sinh(x.hi())};
    }
}

void interval_algebra::testSinh() const
{
    analyzeumth(10, 1000, "sinh", interval(-10, 10), sinh, &interval_algebra::Sinh);
}
