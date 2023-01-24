![C/C++ CI](https://github.com/orlarey/interval/actions/workflows/ubuntu.yml/badge.svg)![C/C++ CI](https://github.com/orlarey/interval/actions/workflows/macos.yml/badge.svg)![C/C++ CI](https://github.com/orlarey/interval/actions/workflows/windows.yml/badge.svg)

# Intervals

A simple interval library for the Faust compiler. 

## Purposes of intervals as used by the Faust compiler

- determine the size of a delay line
- check that a Faust program will execute correctly, without producing infinite or NAN values
- compute the precision needed for fix-point and fpga implementations
- detect and report errors at compile time

## Definition of an interval

An interval is a triplet <lo,hi,lsb> where:
- lo: is the lowest value
- hi: is the highest value
- lsb: is the least significant bit
- The msb can be deduced from lo and hi

An interval represent integer values if lo and hi are integers and if lsb >= 0

## Organization of the code

All the code is encapsulated in the namespace 'itv'. It is organized as follows:

- interval_def.hh : defines intervals as data structures with some very basic methods to access the fields
- interval_algebra.hh/cpp: class gathering all operations on intervals as defined by Faust primitives.
- intervalXXX.cpp: implementation of the XXX operation on intervals.


