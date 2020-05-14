#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval.hh"
#include "interval_algebra.hh"

//------------------------------------------------------------------------------------------
// Interval division

interval interval_algebra::Div(const interval& x, const interval& y) const
{
    return Mul(x, Inv(y));
}

void interval_algebra::testDiv() const
{
    check("test algebra Div", Div(interval(-2, 3), interval(1, 10)), interval(-2, 3));
    check("test algebra Div", Div(interval(-2, 3), interval(-1, 10)), interval(-HUGE_VAL, +HUGE_VAL));
    check("test algebra Div", Div(interval(-2, 3), interval(-0.1, -0.01)), interval(-300, 200));
    check("test algebra Div", Div(interval(0), interval(0)), interval(0));
    check("test algebra Div", Div(interval(0, 1), interval(0, 1)), interval(0, +HUGE_VAL));
}
