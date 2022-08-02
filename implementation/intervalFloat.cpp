#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval.hh"
#include "interval_algebra.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Float
// interval Float(const interval& x) const;
// void testFloat() const;

interval interval_algebra::Float(const interval& x) const
{
    return x;
}

void interval_algebra::testFloat() const
{
}
}  // namespace itv
