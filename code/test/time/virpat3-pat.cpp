//
//  Mach7: Pattern Matching Library for C++
//
//  Copyright 2011-2013, Texas A&M University.
//  Copyright 2014 Yuriy Solodkyy.
//  All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met:
//
//      * Redistributions of source code must retain the above copyright
//        notice, this list of conditions and the following disclaimer.
//
//      * Redistributions in binary form must reproduce the above copyright
//        notice, this list of conditions and the following disclaimer in the
//        documentation and/or other materials provided with the distribution.
//
//      * Neither the names of Mach7 project nor the names of its contributors
//        may be used to endorse or promote products derived from this software
//        without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
//  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
//  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY
//  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
//  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

///
/// \file
///
/// This file is a part of Mach7 library test suite.
///
/// \author Yuriy Solodkyy <yuriy.solodkyy@gmail.com>
///
/// \see https://parasol.tamu.edu/mach7/
/// \see https://github.com/solodon4/Mach7
/// \see https://github.com/solodon4/SELL
///

#include <iostream>
#include <mach7/config.hpp>                // Mach7 configuration
#include <mach7/type_switchN-patterns.hpp> // Support for N-ary Match statement on patterns
#include <mach7/patterns/primitive.hpp>    // Wildcard, variable and value patterns
#include "timing.hpp"

//------------------------------------------------------------------------------

#if defined(XTL_TIMING_METHOD_1)
    XTL_MESSAGE("Timing method 1: based on QueryPerformanceCounter()")
#elif defined(XTL_TIMING_METHOD_2)
    XTL_MESSAGE("Timing method 2: based on rdtsc register")
#elif defined(XTL_TIMING_METHOD_3)
    XTL_MESSAGE("Timing method 3: based on clock()")
#endif

using namespace mch;

//------------------------------------------------------------------------------

int fac(int n)
{
    var<unsigned short> m;

    Match (n)
    {
      Case(0) return 1;
      Case(1) return 1;
      Case(m) return m*fac(m-1);
      Case(_) return 0;
    }
    EndMatch

    XTL_UNREACHABLE; // To avoid warning that control may reach end of a non-void function
}

//------------------------------------------------------------------------------

const size_t T = 1000000;

//------------------------------------------------------------------------------

int main()
{
    int tests[]   = {0,1,2,3,4,5,6,7,8,9,10};
    const size_t N = XTL_ARR_SIZE(tests);

    int r = 0;

    for (size_t i = 0; i < N; ++i)
    {
        mch::time_stamp liStart1 = mch::get_time_stamp();

        for (size_t j = 0; j < T; ++j)
        {
            r += fac(tests[i]);
        }

        mch::time_stamp liFinish1 = mch::get_time_stamp();
        std::cout << liStart1 << '-' << liFinish1 << ':' << (liFinish1-liStart1) << std::endl;
        std::cout << "fac(" << i << ")=" << fac(tests[i]) << " r=" << r << " timing=" << mch::cycles(liFinish1-liStart1)/T << " cycles/iteration" << std::endl;
    }
}

//------------------------------------------------------------------------------
