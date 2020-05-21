#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval.hh"
#include "interval_algebra.hh"

//------------------------------------------------------------------------------------------
// Interval Ne
// interval Ne(const interval& x, const interval& y) const;
// void testNe() const;

interval interval_algebra::Ne(const interval& x, const interval& y) const
{
    if (x.isEmpty() || y.isEmpty()) {
        return {};
    } else if ((x.hi() < y.lo()) || x.lo() > y.hi()) {
        return interval{1.0};
    } else if ((x.hi() == y.lo()) || x.lo() == y.hi()) {
        return interval{0.0};
    } else {
        return {0, 1};
    }
}

void interval_algebra::testNe() const
{
    check("test algebra Ne", Ne(interval(0, 5), interval(-3, 10)), interval(0, 1));
    check("test algebra Ne", Ne(interval(0, 5), interval(8, 10)), interval(1));
    check("test algebra Ne", Ne(interval(0, 0), interval(0, 0)), interval(0));
}
