#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval.hh"
#include "interval_algebra.hh"

//------------------------------------------------------------------------------------------
// Interval Floor
// interval Floor(const interval& x) const;
// void testFloor() const;

interval interval_algebra::Floor(const interval& x) const
{
    return {floor(x.lo()), floor(x.hi())};
}

void interval_algebra::testFloor() const
{
    check("test algebra Floor", Floor(interval(-3.1, 5.9)), interval(-4, 5));
}
