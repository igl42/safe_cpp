/**************************************************************************************************
*
* \file StrongType_Assembly.cpp
* \brief C++ Training - Assembly analysis of the code generation for strong types
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Compare the assembly output of the two functions 'test()' (for instance by means of
*       Compiler Explorer; godbolt.org). Is there any difference/overhead when using the
*       'StrongType' class template instead of the fundamental type?
*
**************************************************************************************************/


//---- <StrongType.h> -----------------------------------------------------------------------------

class StrongType
{
   // Add your implementation from <StrongType.cpp>
};


//---- <Main.cpp.h> -------------------------------------------------------------------------------

//#include <StrongType.h>
#include <cstdlib>
#include <iostream>

/*
using Meter = StrongType<int,struct MeterTag>;

int test( int meter )
{
   return meter+7;
}

Meter test( Meter meter )
{
   return Meter{ meter.get()+7 };
}
*/

int main()
{
   // Integral type
   /*
   int const i1 = 35;
   int const i2 = test( i1 );

   std::cout << "\n i = " << i2 << "\n\n";
   */

   // Strong type
   /*
   Meter const m1{ 35 };
   Meter const m2 = test( m1 );

   std::cout << "\n m = " << m2 << "\n\n";
   */

   return EXIT_SUCCESS;
}

