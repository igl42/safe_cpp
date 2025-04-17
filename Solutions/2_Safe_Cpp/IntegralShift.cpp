/**************************************************************************************************
*
* \file IntegralShift.cpp
* \brief C++ Training - Undefined behavior in mixing signed and unsigned integral types
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Take a look at the given 'shift()' function. What is the expected result for the calls
*       in the 'main()' function?
*
**************************************************************************************************/

#include <iostream>
#include <cstdint>


std::uint64_t shift( std::uint64_t count )
{
   return 1 << (count % 64);
}


int main()
{
   const auto result_28 = shift( 28 );
   const auto result_29 = shift( 29 );
   const auto result_30 = shift( 30 );
   const auto result_31 = shift( 31 );
   const auto result_32 = shift( 32 );
   const auto result_33 = shift( 33 );
   const auto result_34 = shift( 34 );

   std::cout << "\n"
             << " result_28 = " << result_28 << "\n"
             << " result_29 = " << result_29 << "\n"
             << " result_30 = " << result_30 << "\n"
             << " result_31 = " << result_31 << "\n"
             << " result_32 = " << result_32 << "\n"
             << " result_33 = " << result_33 << "\n"
             << " result_34 = " << result_34 << "\n"
             << "\n";

   return EXIT_SUCCESS;
}
