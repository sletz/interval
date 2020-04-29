#include <iostream>
#include <sstream>
#include <string>
#include "check.hh"
#include "interval.hh"
#include "interval_algebra.hh"

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
    A.testAll();
}