#include <fstream>
#include <iostream>
#include "interval.hh"

int main()
{
    std::cout << "my first interval :" << interval(0.0, 100.0) << std::endl;
    std::cout << "my second interval:" << interval(0.0, 0.0) << std::endl;
    std::cout << "my third interval :" << interval(10.0, -10.0) << std::endl;
    std::cout << "my fourth interval:" << interval() << std::endl;

    // test union intersection
    std::cout << "intersection " << interval(0, 100) << ", " << interval(-10, 0) << " = "
              << intersection(interval(0, 100), interval(-10, 0)) << std::endl;
    std::cout << "reunion      " << interval(0, 100) << ", " << interval(-10, 0) << " = "
              << reunion(interval(0, 100), interval(-10, 0)) << std::endl;

    std::cout << "intersection " << interval(1, 100) << ", " << interval(-10, 0) << " = "
              << intersection(interval(1, 100), interval(-10, 0)) << std::endl;
    std::cout << "reunion      " << interval(1, 100) << ", " << interval(-10, 0) << " = "
              << reunion(interval(1, 100), interval(-10, 0)) << std::endl;

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
    std::cout << "must be true " << (intersection, (a, n) == n) << std::endl;

    std::cout << std::endl;
}