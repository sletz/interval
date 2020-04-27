#include <iostream>
#include <sstream>
#include <string>
#include "interval.hh"
#include "interval_algebra.hh"

void check(const std::string& testname, const interval& exp)
{
    std::stringstream ss;
    ss << exp;
    if (ss.str().compare(testname) == 0) {
        std::cout << testname << ": OK" << std::endl;
    } else {
        std::cout << testname << ": FAILED. We got " << ss.str() << " instead of " << testname << std::endl;
    }
}

void check(const std::string& testname, const interval& exp, const interval& res)
{
    if (exp == res) {
        std::cout << testname << " " << exp << ": OK" << std::endl;
    } else {
        std::cout << testname << ": FAILED. We got " << exp << " instead of " << res << std::endl;
    }
}

void check(const std::string& testname, bool exp, bool res)
{
    if (exp == res) {
        std::cout << testname << ": OK" << std::endl;
    } else {
        std::cout << testname << ": FAILED. We got " << exp << " instead of " << res << std::endl;
    }
}

int main()
{
    // test interval representation
    check("interval()", interval());
    check("interval(0,100)", interval(100.0, 0.0));
    check("interval(0)", interval(0, 0));
    check("interval(-10,0)", interval(0, -10));

    // test union intersection

    check("test2", intersection(interval(0, 100), interval(-10, 0)), interval(0));
    check("test3", intersection(interval(10, 100), interval(-10, 0)), interval());
    check("test4", reunion(interval(0, 100), interval(-100, 50)), interval(-100, 100));
    check("test5", reunion(interval(0, 100), interval(10, 500)), interval(0, 500));

    // test predicates
    interval a(1, 100), b(10, 20), c(-10, 0), n;

    std::cout << a << " == " << b << " = " << (a == b) << std::endl;
    std::cout << a << " <= " << b << " = " << (a <= b) << std::endl;
    std::cout << a << " < " << b << " = " << (a < b) << std::endl;

    std::cout << std::endl;

    std::cout << a << " != " << b << " = " << (a != b) << std::endl;
    std::cout << a << " > " << b << " = " << (a > b) << std::endl;
    std::cout << a << " >= " << b << " = " << (a >= b) << std::endl;

    std::cout << std::endl;

    std::cout << a << " == " << a << " = " << (a == a) << std::endl;
    std::cout << a << " <= " << a << " = " << (a <= a) << std::endl;
    std::cout << a << " < " << a << " = " << (a < a) << std::endl;

    std::cout << std::endl;

    std::cout << a << " != " << a << " = " << (a != a) << std::endl;
    std::cout << a << " > " << a << " = " << (a > a) << std::endl;
    std::cout << a << " >= " << a << " = " << (a >= a) << std::endl;

    std::cout << std::endl;

    std::cout << a << " != " << n << " = " << (a != n) << std::endl;
    std::cout << a << " > " << n << " = " << (a > n) << std::endl;
    std::cout << a << " >= " << n << " = " << (a >= n) << std::endl;

    std::cout << std::endl;

    std::cout << "must be true " << (reunion(a, n) == a) << std::endl;
    std::cout << "must be true " << (intersection(a, n) == n) << std::endl;

    std::cout << std::endl;

    interval_algebra A;
    check("test algebra add", A.add(interval(0, 100), interval(10, 500)), interval(10, 600));
    check("test algebra sub", A.sub(interval(0, 100), interval(10, 500)), interval(-500, 90));
    check("test algebra mul", A.mul(interval(-2, 3), interval(5, 10)), interval(-20, 30));
    check("test algebra mul", A.mul(interval(-2, 3), interval(-50, 10)), interval(-150, 100));
    check("test algebra inv", A.inv(interval(-20, -3)), interval(-1. / 3., -1. / 20.));
    check("test algebra inv", A.inv(interval(-20, 3)), interval(-INFINITY, +INFINITY));
    check("test algebra div", A.div(interval(-2, 3), interval(1, 10)), interval(-2, 3));
    check("test algebra div", A.div(interval(-2, 3), interval(-1, 10)), interval(-INFINITY, +INFINITY));
}