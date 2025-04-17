/**************************************************************************************************
*
* \file Count.cpp
* \brief C++ Training - Undefined behavior in mixing signed and unsigned integral types
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Take a look at the given 'count()' function. What is the expected result for the calls
*       in the 'main()' function?
*
**************************************************************************************************/

#include <iostream>
#include <cstdint>


std::uint64_t count( std::uint64_t size )
{
   std::uint64_t count{};

   for( int i=0; size-i >= 0; ++i ) {
      ++count;
   }

   return count;
}


int main()
{
   const auto result_1 = count( 1 );
   const auto result_2 = count( 2 );
   const auto result_3 = count( 3 );

   std::cout << '\n'
             << " result_1 = " << result_1 << '\n'
             << " result_2 = " << result_2 << '\n'
             << " result_3 = " << result_3 << '\n'
             << '\n';

   return EXIT_SUCCESS;
}
