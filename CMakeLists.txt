cmake_minimum_required(VERSION 3.10)

# set the project name
project(TestInterval)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(. ./implementation)

# add the executable
add_executable(TestInterval implementation/intervalFloat.cpp implementation/intervalRint.cpp implementation/intervalAcos.cpp implementation/intervalOr.cpp implementation/intervalAsin.cpp implementation/intervalLog.cpp implementation/intervalDelay.cpp implementation/intervalRemainder.cpp implementation/intervalRsh.cpp implementation/intervalNot.cpp implementation/intervalNe.cpp implementation/intervalSinh.cpp implementation/intervalLsh.cpp implementation/intervalNeg.cpp implementation/intervalPow.cpp implementation/intervalTanh.cpp implementation/intervalAsinh.cpp implementation/intervalExp.cpp implementation/intervalTan.cpp implementation/intervalAtanh.cpp implementation/intervalEq.cpp implementation/intervalMax.cpp implementation/intervalMod.cpp implementation/intervalLog10.cpp implementation/intervalInv.cpp implementation/intervalSqrt.cpp implementation/intervalInt.cpp implementation/intervalMul.cpp implementation/intervalCosh.cpp implementation/intervalCeil.cpp implementation/intervalAcosh.cpp implementation/intervalGe.cpp implementation/intervalAbs.cpp implementation/intervalAnd.cpp implementation/intervalGt.cpp implementation/intervalDiv.cpp implementation/intervalXor.cpp implementation/intervalSin.cpp implementation/intervalCos.cpp implementation/intervalAtan2.cpp implementation/intervalLt.cpp implementation/intervalMem.cpp implementation/intervalMin.cpp implementation/intervalAdd.cpp implementation/intervalAtan.cpp implementation/intervalLe.cpp implementation/intervalFloor.cpp implementation/intervalSub.cpp implementation/interval_algebra.cpp implementation/check.cpp main.cpp)


