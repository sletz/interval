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
    testNeg();
    testMod();
    testCeil();
    testFloor();
    testRint();
    testAcos();
    testAcosh();
    testAnd();
    testAsin();
    testAsinh();
    testAtan();
    testAtanh();
    testCos();
    testCosh();
    testDelay();
    testEq();
    testExp();
    testFloor();
    testGe();
    testGt();
    testInt();
    testLog();
    testLog10();
    testLsh();
    testLt();
    testMax();
    testMin();
    testNe();
    testRsh();
    testNot();
    testSin();
    testSinh();
    testSqrt();
    testTan();
    testTanh();
    testMem();
}
