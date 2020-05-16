#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval.hh"
#include "interval_algebra.hh"

//------------------------------------------------------------------------------------------
// Interval Ceil
// interval Ceil(const interval& x) const;
// void testCeil() const;

interval interval_algebra::Ceil(const interval& x) const
{
    return {ceil(x.lo()), ceil(x.hi())};
}

void interval_algebra::testCeil() const
{
    analyzeumth(10, 1000, "ceil", interval(-10, 10), ceil, &interval_algebra::Ceil);
}
