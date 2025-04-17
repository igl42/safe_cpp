/**************************************************************************************************
*
* \file Erase.cpp
* \brief C++ Training - Example for alternatives to remove elements from a std::vector
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Consider the given 'std::vector<int>'. Remove all odd elements from the vector as
*       efficiently as possible.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <vector>


bool is_odd( int i )
{
   return i % 2 == 1;
}


auto is_odd_number()
{
   return []( int i ){
      return is_odd(i);
   };
}


int main()
{
   std::vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

   // SOLUTION 1: Classic for-loop (since C++98)
   /*
   for( auto pos=std::begin(v); pos!=std::end(v); ) {
      if( is_odd( *pos ) ) {
         pos = v.erase(pos);
      }
      else {
         ++pos;
      }
   }
   */

   // SOLUTION 2: Remove-erase-idiom (since C++98)
   /*
   v.erase( std::remove_if( std::begin(v), std::end(v), is_odd() ), std::end(v) );
   */

   // SOLUTION 3: 'std::erase_if()' (since C++23)
   std::erase_if( v, is_odd_number() );


   std::cout << "\n v = {";
   for( int i : v ) {
      std::cout << ' ' << i;
   }
   std::cout << "}\n\n";

   return EXIT_SUCCESS;
}
