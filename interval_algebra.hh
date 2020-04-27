#pragma once

#include "interval.hh"

class interval_algebra {
   public:
    interval add(const interval& x, const interval& y) const;
    interval sub(const interval& x, const interval& y) const;
    interval mul(const interval& x, const interval& y) const;
    interval div(const interval& x, const interval& y) const;
    interval inv(const interval& x) const;
};