#include <iostream>
#include <random>
#include <sstream>
#include <string>

#include "check.hh"
#include "interval_algebra.hh"

static double min4(double a, double b, double c, double d)
{
    return std::min(std::min(a, b), std::min(c, d));
}

static double max4(double a, double b, double c, double d)
{
    return std::max(std::max(a, b), std::max(c, d));
}

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

interval testfun(int N, fun f, const interval& x, const interval& y)
{
    std::default_random_engine             generator;
    std::uniform_real_distribution<double> rx(x.lo(), x.hi());
    std::uniform_real_distribution<double> ry(y.lo(), y.hi());

    double a = f(x.lo(), y.lo());
    double b = f(x.lo(), y.hi());
    double c = f(x.hi(), y.lo());
    double d = f(x.hi(), y.hi());

    double l = min4(a, b, c, d);
    double h = max4(a, b, c, d);

    for (int i = 0; i < N; i++) {
        double u = rx(generator);
        double v = ry(generator);
        double r = f(u, v);
        if (r < l) l = r;
        if (r > h) h = r;
    }

    return {l, h};
}

void analyzemod(interval x, interval y)
{
    interval_algebra A;
    std::cout << "simulated fmod(" << x << "," << y << ") = " << testfun(10000, fmod, x, y) << std::endl;
    std::cout << "computed  fmod(" << x << "," << y << ") = " << A.Mod(x, y) << std::endl;
    std::cout << std::endl;
}