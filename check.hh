#pragma once

#include <string>
#include "interval.hh"

void check(const std::string& testname, const interval& exp);

void check(const std::string& testname, const interval& exp, const interval& res);

void check(const std::string& testname, bool exp, bool res);

typedef double (*fun)(double, double);

interval testfun(int N, fun f, const interval& x, const interval& y);
void     analyzemod(interval x, interval y);
