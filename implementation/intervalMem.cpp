#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval.hh"
#include "interval_algebra.hh"

//------------------------------------------------------------------------------------------
// Interval Mem
// interval Mem(const interval& x) const;
// void testMem() const;

interval interval_algebra::Mem(const interval& x) const
{
    return {};
}

void interval_algebra::testMem() const
{
}
