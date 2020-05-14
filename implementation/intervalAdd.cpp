#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval.hh"
#include "interval_algebra.hh"

//------------------------------------------------------------------------------------------
// Interval addition

interval interval_algebra::Add(const interval& x, const interval& y) const
{
    if (x.isEmpty() || y.isEmpty()) {
        return {};
    } else {
        return {x.lo() + y.lo(), x.hi() + y.hi()};
    }
}

void interval_algebra::testAdd() const
{
    check("test algebra Add", Add(interval(0, 100), interval(10, 500)), interval(10, 600));
}
