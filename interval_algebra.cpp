#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval.hh"
#include "interval_algebra.hh"

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
    testCeil();
    testFloor();
    testRint();
}
