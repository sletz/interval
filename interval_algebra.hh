#pragma once

#include "interval.hh"

class interval_algebra {
   public:
    interval Add(const interval& x, const interval& y) const;
    void     testAdd() const;
    //
    interval Sub(const interval& x, const interval& y) const;
    void     testSub() const;
    //
    interval Mul(const interval& x, const interval& y) const;
    void     testMul() const;
    //
    interval Div(const interval& x, const interval& y) const;
    void     testDiv() const;
    //
    interval Inv(const interval& x) const;
    void     testInv() const;
    //
    interval Mod(const interval& x, const interval& y) const;
    void     testMod() const;
    //
    interval Log(const interval& x) const;
    void     testLog() const;
    //
    interval Delay(const interval& x, const interval& y) const;
    void     testDelay() const;
    //
    interval And(const interval& x, const interval& y) const;
    void     testAnd() const;
    //
    interval Or(const interval& x, const interval& y) const;
    void     testOr() const;
    //
    interval Xor(const interval& x, const interval& y) const;
    void     testXor() const;
    //
    void testAll();
};
