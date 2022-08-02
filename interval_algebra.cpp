#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval.hh"
#include "interval_algebra.hh"
namespace itv {
void interval_algebra::testAll()
{
    testAbs();
    testAcos();
    testAcosh();
    testAdd();
    testAnd();
    testAsin();
    testAsinh();
    testAtan();
    testAtanh();
    testCeil();
    testCos();
    testCosh();
    testDelay();
    testDiv();
    testEq();
    testExp();
    testFloat();
    testFloor();
    testGe();
    testGt();
    testInt();
    testInv();
    testLog();
    testLog10();
    testLsh();
    testLt();
    testMax();
    testMem();
    testMin();
    testMod();
    testMul();
    testNe();
    testNeg();
    testNot();
    testOr();
    testPow();
    testRint();
    testRsh();
    testSin();
    testSinh();
    testSqrt();
    testSub();
    testTan();
    testTanh();
    testXor();
}
}  // namespace itv
