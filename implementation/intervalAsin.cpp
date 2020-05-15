#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval.hh"
#include "interval_algebra.hh"

//------------------------------------------------------------------------------------------
// Interval Asin
// interval Asin(const interval& x) const;
// void testAsin() const;

static interval domain(-1, 1);

interval interval_algebra::Asin(const interval& x) const
{
    interval i = intersection(domain, x);
    if (i.isEmpty()) return i;
    return {asin(i.lo()), asin(i.hi())};
}

void interval_algebra::testAsin() const
{
    analyzeumth(10, 1000, "asin", interval(-2, 2), asin, &interval_algebra::Asin);
}
