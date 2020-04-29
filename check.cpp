#include "check.hh"
#include <iostream>
#include <sstream>
#include <string>

void check(const std::string& expected, const interval& exp)
{
    std::stringstream ss;
    ss << exp;
    if (ss.str().compare(expected) == 0) {
        std::cout << "OK: " << expected << std::endl;
    } else {
        std::cout << "ERR:  We got " << ss.str() << " instead of " << expected << std::endl;
    }
}

void check(const std::string& testname, const interval& exp, const interval& res)
{
    if (exp == res) {
        std::cout << "OK: " << testname << " " << exp << std::endl;
    } else {
        std::cout << "ERR:" << testname << " FAILED. We got " << exp << " instead of " << res << std::endl;
    }
}

void check(const std::string& testname, bool exp, bool res)
{
    if (exp == res) {
        std::cout << "OK: " << testname << std::endl;
    } else {
        std::cout << "ERR:" << testname << " FAILED. We got " << exp << " instead of " << res << std::endl;
    }
}
