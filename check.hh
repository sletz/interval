#pragma once

#include <string>

#include "interval.hh"
#include "interval_algebra.hh"

void check(const std::string& testname, const interval& exp);

void check(const std::string& testname, const interval& exp, const interval& res);

void check(const std::string& testname, bool exp, bool res);

using ufun = double (*)(double);
using bfun = double (*)(double, double);

using umth = interval (interval_algebra::*)(const interval& x) const;

interval testfun(int N, bfun f, const interval& x, const interval& y);
void     analyzemod(interval x, interval y);

void analyzeufun(int E, int M, const char* title, const interval& D, ufun f);
void analyzeumth(int E, int M, const char* title, const interval& D, ufun f, umth m);
