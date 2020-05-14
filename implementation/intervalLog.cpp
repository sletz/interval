#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval.hh"
#include "interval_algebra.hh"

//------------------------------------------------------------------------------------------
// Interval Log
// interval Log(const interval& x) const;
// void testLog() const;

interval interval_algebra::Log(const interval& x) const
{
    if (x.isEmpty()) {
        return {};
    } else {
        interval i = intersection(interval(0, HUGE_VAL), x);
        return {log(i.lo()), log(i.hi())};
    }
}

void interval_algebra::testLog() const
{
    check("test algebra Log", Log(interval(1, 10)), interval(log(1), log(10)));
    check("test algebra Log", Log(interval(0, 10)), interval(log(0), log(10)));
    check("test algebra Log", Log(interval(-10, 10)), interval(log(0), log(10)));
}
