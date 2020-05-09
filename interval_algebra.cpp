#include <algorithm>
#include <functional>
#include <random>
#include "check.hh"
#include "interval.hh"

#include "interval_algebra.hh"

static double specialmult(double a, double b)
{
    // we want inf*0 to be 0
    return ((a == 0.0) || (b == 0.0)) ? 0.0 : a * b;
}

static double min4(double a, double b, double c, double d)
{
    return std::min(std::min(a, b), std::min(c, d));
}

static double max4(double a, double b, double c, double d)
{
    return std::max(std::max(a, b), std::max(c, d));
}

//==========================================================================================
//
// interval operations
//
//==========================================================================================

//------------------------------------------------------------------------------------------
// Interval addition

interval interval_algebra::Add(const interval& x, const interval& y) const
{
    if (x.isEmpty() || y.isEmpty()) {
        return {};
    } else {
        return {x.lo() + y.lo(), x.hi() + y.hi()};
    }
}

void interval_algebra::testAdd() const
{
    check("test algebra Add", Add(interval(0, 100), interval(10, 500)), interval(10, 600));
}

//------------------------------------------------------------------------------------------
// Interval substraction

interval interval_algebra::Sub(const interval& x, const interval& y) const
{
    if (x.isEmpty() || y.isEmpty()) {
        return {};
    } else {
        return {x.lo() - y.hi(), x.hi() - y.lo()};
    }
}

void interval_algebra::testSub() const
{
    check("test algebra Sub", Sub(interval(0, 100), interval(10, 500)), interval(-500, 90));
}

//------------------------------------------------------------------------------------------
// Interval multiplication

interval interval_algebra::Mul(const interval& x, const interval& y) const
{
    if (x.isEmpty() || y.isEmpty()) {
        return {};
    } else {
        double a = specialmult(x.lo(), y.lo());
        double b = specialmult(x.lo(), y.hi());
        double c = specialmult(x.hi(), y.lo());
        double d = specialmult(x.hi(), y.hi());
        return {min4(a, b, c, d), max4(a, b, c, d)};
    }
}

void interval_algebra::testMul() const
{
    check("test algebra Mul", Mul(interval(-1, 1), interval(0, 1)), interval(-1, 1));
    check("test algebra Mul", Mul(interval(-2, 3), interval(-50, 10)), interval(-150, 100));
    check("test algebra Mul", Mul(interval(-2, -1), interval(-2, -1)), interval(1, 4));
    check("test algebra Mul", Mul(interval(0), interval(-HUGE_VAL, HUGE_VAL)), interval(0));
    check("test algebra Mul", Mul(interval(-HUGE_VAL, HUGE_VAL), interval(0)), interval(0));
}

//------------------------------------------------------------------------------------------
// negation, invert sign

interval interval_algebra::Neg(const interval& x) const
{
    if (x.isEmpty()) {
        return {};
    } else {
        return {-x.hi(), -x.lo()};
    }
}

void interval_algebra::testNeg() const
{
    check("test algebra Neg", Neg(interval(-1, 1)), interval(-1, 1));
    check("test algebra Neg", Neg(interval(-10, 1)), interval(-1, 10));
}

//------------------------------------------------------------------------------------------
// Interval inverse

interval interval_algebra::Inv(const interval& x) const
{
    if (x.isEmpty()) {
        return {};
    } else if ((x.hi() < 0) || (x.lo() >= 0)) {
        return {1.0 / x.hi(), 1.0 / x.lo()};
    } else if (x.hi() == 0) {
        return {-HUGE_VAL, 1.0 / x.lo()};
    } else {
        return {-HUGE_VAL, HUGE_VAL};
    }
}

void interval_algebra::testInv() const
{
    check("test algebra Inv", Inv(interval(-16, -4)), interval(-1. / 4., -1. / 16.));
    check("test algebra Inv", Inv(interval(4, 16)), interval(1.0 / 16, 0.25));
    check("test algebra Inv", Inv(interval(0, 10)), interval(0.1, +HUGE_VAL));
    check("test algebra Inv", Inv(interval(-10, 0)), interval(-HUGE_VAL, -0.1));
    check("test algebra Inv", Inv(interval(-20, +20)), interval(-HUGE_VAL, +HUGE_VAL));
    check("test algebra Inv", Inv(interval(0, 0)), interval(+HUGE_VAL, +HUGE_VAL));
}

//------------------------------------------------------------------------------------------
// Interval division

interval interval_algebra::Div(const interval& x, const interval& y) const
{
    return Mul(x, Inv(y));
}

void interval_algebra::testDiv() const
{
    check("test algebra Div", Div(interval(-2, 3), interval(1, 10)), interval(-2, 3));
    check("test algebra Div", Div(interval(-2, 3), interval(-1, 10)), interval(-HUGE_VAL, +HUGE_VAL));
    check("test algebra Div", Div(interval(-2, 3), interval(-0.1, -0.01)), interval(-300, 200));
    check("test algebra Div", Div(interval(0), interval(0)), interval(0));
    check("test algebra Div", Div(interval(0, 1), interval(0, 1)), interval(0, +HUGE_VAL));
}

//------------------------------------------------------------------------------------------
// Interval natural logarithmic function

interval interval_algebra::Log(const interval& x) const
{
    if (x.isEmpty()) {
        return {};
    } else {
        interval i = intersection(interval(0, HUGE_VAL), x);
        return {log(i.lo()), log(i.hi())};
    }
}

void interval_algebra::testLog() const
{
    check("test algebra Log", Log(interval(1, 10)), interval(log(1), log(10)));
    check("test algebra Log", Log(interval(0, 10)), interval(log(0), log(10)));
    check("test algebra Log", Log(interval(-10, 10)), interval(log(0), log(10)));
}

//------------------------------------------------------------------------------------------
// modulo function
// (see https://stackoverflow.com/questions/31057473/calculating-the-modulo-of-two-intervals)

interval interval_algebra::Mod(const interval& x, double m) const
{
    if (x.isEmpty() || (m == 0)) {
        return {};
    } else if (x.hi() < 0) {
        return Neg(Mod({-x.hi(), -x.lo()}, m));
        // (3): split into negative and non-negative interval, compute and join
    } else if (x.lo() < 0) {
        return reunion(Mod({x.lo(), nextafter(-0.0, -HUGE_VAL)}, m), Mod({0.0, x.hi()}, m));
        // (4): there is no k > 0 such that x.lo() < k*m <= x.hi()
    } else if ((x.size() < fabs(m)) && (fmod(x.lo(), m) <= fmod(x.hi(), m))) {
        return {fmod(x.lo(), m), fmod(x.hi(), m)};
        // (5): we can't do better than that
    } else {
        // [0,m[
        return {0, nextafter(fabs(m), 0.0)};
    }
}

interval interval_algebra::Mod(const interval& x, const interval& y) const
{
    if (x.isEmpty() || y.isEmpty()) {
        return {};
    } else if (x.hi() < 0) {
        return Neg(Mod({-x.hi(), -x.lo()}, {y.lo(), y.hi()}));
        // (3): split into negative and non-negative interval, compute, and join
    } else if (x.lo() < 0) {
        return reunion(Mod({x.lo(), -1}, {y.lo(), y.hi()}), Mod({0, x.hi()}, {y.lo(), y.hi()}));
        // (4) use the simpler function from before
    } else if (y.lo() == y.hi()) {
        return Mod({x.lo(), x.hi()}, y.lo());
        // (5) use only non-negative y.lo() and y.hi()
    } else if (y.hi() <= 0) {
        return Mod({x.lo(), x.hi()}, {-y.hi(), -y.lo()});
        // (6) similar to (5), make modulus non-negative
    } else if (y.lo() <= 0) {
        return Mod({x.lo(), x.hi()}, {1, std::max(-y.lo(), y.hi())});
        // (7) compare to (4) in mod1, check x.hi()-x.lo() < |modulus|
    } else if (x.hi() - x.lo() >= y.hi()) {
        return {0, y.hi() - 1};
        // (8) similar to (7), split interval, compute, and join
    } else if (x.hi() - x.lo() >= y.lo()) {
        return reunion({0, x.hi() - x.lo() - 1}, Mod({x.lo(), x.hi()}, {x.hi() - x.lo() + 1, y.hi()}));
        // (9) modulo has no effect
    } else if (y.lo() > x.hi()) {
        return {x.lo(), x.hi()};
        // (10) there is some overlapping of {x.lo(),x.hi()} and {y.hi(),y.lo()}
    } else if (y.hi() > x.hi()) {
        return {0, x.hi()};
        // (11)  either compute all possibilities and join, or be imprecise
    } else {
        return {0, y.hi() - 1};
    }
}

void interval_algebra::testMod() const
{
    check("test algebra Mod", Mod(interval(-100, 100), 1.0), interval(nextafter(-1.0, 0.0), nextafter(1.0, 0.0)));
    check("test algebra Mod", Mod(interval(0, 100), 2), interval(0, nextafter(2.0, 0)));
    check("test algebra Mod", Mod(interval(0, 100), -1.0), interval(0, nextafter(1.0, 0)));
    check("test algebra Mod", Mod(interval(5, 7), interval(8, 10)), interval(5, 7));
    check("test algebra Mod", Mod(interval(-7, 7), interval(8, 10)), interval(-7, 7));
    check("test algebra Mod", Mod(interval(0, 100), interval(7, 7)), interval(0, nextafter(7.0, 0.0)));
}

void interval_algebra::testAll()
{
    testAdd();
    testSub();
    testMul();
    testDiv();
    testInv();
    testLog();
    testNeg();
    testMod();
}
