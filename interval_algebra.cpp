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
    return {x.lo() + y.lo(), x.hi() + y.hi()};
}

void interval_algebra::testAdd() const
{
    check("test algebra Add", Add(interval(0, 100), interval(10, 500)), interval(10, 600));
}

//------------------------------------------------------------------------------------------
// Interval substraction

interval interval_algebra::Sub(const interval& x, const interval& y) const
{
    return {x.lo() - y.hi(), x.hi() - y.lo()};
}

void interval_algebra::testSub() const
{
    check("test algebra Sub", Sub(interval(0, 100), interval(10, 500)), interval(-500, 90));
}

//------------------------------------------------------------------------------------------
// Interval multiplication

interval interval_algebra::Mul(const interval& x, const interval& y) const
{
    if (x.empty() || y.empty()) {
        return {};
    } else {
        double a = specialmult(x.lo(), y.lo());
        double b = specialmult(x.lo(), y.hi());
        double c = specialmult(x.hi(), y.lo());
        double d = specialmult(x.hi(), y.hi());
        return interval(min4(a, b, c, d), max4(a, b, c, d));
    }
}

void interval_algebra::testMul() const
{
    check("test algebra Mul", Mul(interval(-1, 1), interval(0, 1)), interval(-1, 1));
    check("test algebra Mul", Mul(interval(-2, 3), interval(-50, 10)), interval(-150, 100));
    check("test algebra Mul", Mul(interval(-2, -1), interval(-2, -1)), interval(1, 4));
    check("test algebra Mul", Mul(interval(0), interval(-INFINITY, INFINITY)), interval(0));
    check("test algebra Mul", Mul(interval(-INFINITY, INFINITY), interval(0)), interval(0));
}

//------------------------------------------------------------------------------------------
// Interval inverse

interval interval_algebra::Inv(const interval& x) const
{
    if (x.lo() >= 0) {
        return {1.0 / x.hi(), 1.0 / x.lo()};
    } else if (x.hi() == 0) {
        return {-INFINITY, 1 / x.lo()};
    } else if (x.hasZero()) {
        return {-INFINITY, +INFINITY};
    } else {
        return {1.0 / x.hi(), 1.0 / x.lo()};
    }
}

void interval_algebra::testInv() const
{
    check("test algebra Inv", Inv(interval(-16, -4)), interval(-1. / 4., -1. / 16.));
    check("test algebra Inv", Inv(interval(4, 16)), interval(1.0 / 16, 0.25));
    check("test algebra Inv", Inv(interval(0, 10)), interval(0.1, +INFINITY));
    check("test algebra Inv", Inv(interval(-10, 0)), interval(-INFINITY, -0.1));
    check("test algebra Inv", Inv(interval(-20, +20)), interval(-INFINITY, +INFINITY));
    check("test algebra Inv", Inv(interval(0, 0)), interval(+INFINITY, +INFINITY));
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
    check("test algebra Div", Div(interval(-2, 3), interval(-1, 10)), interval(-INFINITY, +INFINITY));
    check("test algebra Div", Div(interval(-2, 3), interval(-0.1, -0.01)), interval(-300, 200));
    check("test algebra Div", Div(interval(0), interval(0)), interval(0));
    check("test algebra Div", Div(interval(0, 1), interval(0, 1)), interval(0, +INFINITY));
}

//------------------------------------------------------------------------------------------
// Interval natural logarithmic function

interval interval_algebra::Log(const interval& x) const
{
    interval i = intersection(interval(0, INFINITY), x);
    return {log(i.lo()), log(i.hi())};
}

void interval_algebra::testLog() const
{
    check("test algebra Log", Log(interval(1, 10)), interval(log(1), log(10)));
    check("test algebra Log", Log(interval(0, 10)), interval(log(0), log(10)));
    check("test algebra Log", Log(interval(-10, 10)), interval(log(0), log(10)));
}

void interval_algebra::testAll()
{
    testAdd();
    testSub();
    testMul();
    testDiv();
    testInv();
    testLog();
}
