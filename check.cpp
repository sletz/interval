#include <iostream>
#include <random>
#include <sstream>
#include <string>

#include "check.hh"
#include "interval_algebra.hh"

/**
 * @brief check we have the expected interval
 *
 * @param expected interval as a string
 * @param exp interval to test
 */
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

/**
 * @brief check that an interval result is the expected one
 *
 * @param testname
 * @param exp
 * @param res
 */
void check(const std::string& testname, const interval& exp, const interval& res)
{
    if (exp == res) {
        std::cout << "OK: " << testname << " " << exp << std::endl;
    } else {
        std::cout << "ERR:" << testname << " FAILED. We got " << exp << " instead of " << res << std::endl;
    }
}

/**
 * @brief check that a boolean result is the expected one
 *
 * @param testname
 * @param exp
 * @param res
 */
void check(const std::string& testname, bool exp, bool res)
{
    if (exp == res) {
        std::cout << "OK: " << testname << std::endl;
    } else {
        std::cout << "ERR:" << testname << " FAILED. We got " << exp << " instead of " << res << std::endl;
    }
}

/**
 * @brief Approximate the resulting interval of a function
 *
 * @param N the number of iterations
 * @param f the function to test
 * @param x the interval of its first argument
 * @param y the interval of its second argument
 * @return interval the interval of the results
 */

static double min4(double a, double b, double c, double d)
{
    return std::min(std::min(a, b), std::min(c, d));
}

static double max4(double a, double b, double c, double d)
{
    return std::max(std::max(a, b), std::max(c, d));
}

interval testfun(int N, bfun f, const interval& x, const interval& y)
{
    std::random_device                     rd;  // used to generate a random seed, based on some hardware randomness
    std::default_random_engine             generator(rd());
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

/**
 * @brief analyze the Mod function, print the simulated and computed resulting interval.
 * The two should be close enough.
 *
 * @param x first argument interval
 * @param y second argument interval
 */
void analyzemod(interval x, interval y)
{
    interval_algebra A;
    std::cout << "simulated fmod(" << x << "," << y << ") = " << testfun(10000, fmod, x, y) << std::endl;
    std::cout << "computed  fmod(" << x << "," << y << ") = " << A.Mod(x, y) << std::endl;
    std::cout << std::endl;
}

void analyzeufun(int E, int M, const char* title, const interval& D, ufun f)
{
    std::random_device                     R;  // used to generate a random seed, based on some hardware randomness
    std::default_random_engine             generator(R());
    std::uniform_real_distribution<double> rd(D.lo(), D.hi());

    std::cout << "Analysis of " << title << " in domain " << D << std::endl;

    for (int e = 0; e < E; e++) {  // E experiments

        // X: random input interval X < I
        double   a = rd(generator);
        double   b = rd(generator);
        interval X(std::min(a, b), std::max(a, b));

        // [ylo,yhi] initial f(X) interval
        double t0 = f(X.lo());
        double t1 = f(X.hi());
        double y0 = std::min(t0, t1);
        double y1 = std::max(t0, t1);

        // random values in X
        std::uniform_real_distribution<double> rx(X.lo(), X.hi());

        for (int m = 0; m < M; m++) {  // M measurements
            double y = f(rx(generator));
            if (y < y0) y0 = y;
            if (y > y1) y1 = y;
        }
        interval Y(y0, y1);

        std::cout << e << ": " << title << "(" << X << ") = " << Y << std::endl;
    }
    std::cout << std::endl;
}

void analyzeumth(int E, int M, const char* title, const interval& D, ufun f, umth mp)
{
    std::random_device                     R;  // used to generate a random seed, based on some hardware randomness
    std::default_random_engine             generator(R());
    std::uniform_real_distribution<double> rd(D.lo(), D.hi());
    interval_algebra                       A;

    std::cout << "Analysis of " << title << " in domain " << D << std::endl;

    for (int e = 0; e < E; e++) {  // E experiments

        // X: random input interval X < I
        double   a = rd(generator);
        double   b = rd(generator);
        interval X(std::min(a, b), std::max(a, b));

        // boundaries of the resulting interval
        double y0 = HUGE_VAL;   // std::min(t0, t1);
        double y1 = -HUGE_VAL;  // std::max(t0, t1);

        // random values in X
        std::uniform_real_distribution<double> rx(X.lo(), X.hi());

        for (int m = 0; m < M; m++) {  // M measurements
            double y = f(rx(generator));
            if (!std::isnan(y)) {
                if (y < y0) y0 = y;
                if (y > y1) y1 = y;
            }
        }
        interval Y(y0, y1);
        interval Z = (A.*mp)(X);

        if (Z >= Y) {
            std::cout << "OK    " << e << ": " << title << "(" << X << ") = " << Z << " >= " << Y << std::endl;
        } else {
            std::cout << "ERROR " << e << ": " << title << "(" << X << ") = " << Z << " INSTEAD OF" << Y << std::endl;
        }
    }
    std::cout << std::endl;
}
