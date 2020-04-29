#pragma once

#include <string>
#include "interval.hh"

void check(const std::string& testname, const interval& exp);

void check(const std::string& testname, const interval& exp, const interval& res);

void check(const std::string& testname, bool exp, bool res);
