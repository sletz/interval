#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval.hh"
#include "interval_algebra.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Int
// interval Int(const interval& x) const;
// void testInt() const;

interval interval_algebra::Int(const interval& x) const
{
    if (x.isEmpty()) return {};
    int a = int(x.lo());
    int b = int(x.hi());
    return {double(a), double(b)};
}

void interval_algebra::testInt() const
{
    std::cout << "OK: Int no tests needed" << std::endl;
}
}  // namespace itv
