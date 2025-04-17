/**************************************************************************************************
*
* \file ToInt.cpp
* \brief C++ Training - Example for the advantages of value semantics
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Compare the five different solutions to convert a string into an integer and think about
*       the pros and cons of every solution.
*
**************************************************************************************************/

#include <charconv>
#include <iostream>
#include <optional>


// SOLUTION 1: Always returning an integer; returns 0 on error
// Pros: TODO
// Cons: TODO

int to_int( std::string_view sv )
{
   int i{};

   std::from_chars( sv.data(), sv.data() + sv.size(), i );

   return i;
}


// SOLUTION 2: Throwing on error
// Pros: TODO
// Cons: TODO
/*
int to_int( std::string_view sv )
{
   int i{};

   auto const result = std::from_chars( sv.data(), sv.data() + sv.size(), i );

   if( result.ec != std::errc::invalid_argument ) {
      return i;
   }
   else {
      throw std::invalid_argument( "No integer could be extracted" );
   }
}
*/

// SOLUTION 3: Returning a boolean
// Pros: TODO
// Cons: TODO
/*
bool to_int( std::string_view sv, int& value )
{
   auto const result = std::from_chars( sv.data(), sv.data() + sv.size(), value );

   return result.ec != std::errc::invalid_argument;
}
*/


// SOLUTION 4: Returning a (smart) pointer
// Pros: TODO
// Cons: TODO
/*
std::unique_ptr<int> to_int( std::string_view sv )
{
   int i{};

   auto const result = std::from_chars( sv.data(), sv.data() + sv.size(), i );

   if( result.ec != std::errc::invalid_argument ) {
      return std::make_unique<int>( i );
   }
   else {
      return std::unique_ptr<int>{};
   }
}
*/


// SOLUTION 5: Returning a std::optional<int>
// Pros: TODO
// Cons: TODO
/*
std::optional<int> to_int( std::string_view sv )
{
   std::optional<int> oi{};
   int i{};

   auto const result = std::from_chars( sv.data(), sv.data() + sv.size(), i );

   if( result.ec != std::errc::invalid_argument ) {
      oi = i;
   }

   return oi;
}
*/


int main()
{
   std::string const s1{ "0" };
   std::string const s2{ "1" };
   std::string const s3{ "-2" };
   std::string const s4{ "a" };
   std::string const s5{ " 3" };


   // SOLUTION 1

   auto const result1 = to_int( s1 );
   auto const result2 = to_int( s2 );
   auto const result3 = to_int( s3 );
   auto const result4 = to_int( s4 );
   auto const result5 = to_int( s5 );

   std::cerr << "\n"
             << " result1 = " << result1 << "\n"
             << " result2 = " << result2 << "\n"
             << " result3 = " << result3 << "\n"
             << " result4 = " << result4 << "\n"
             << " result5 = " << result5 << "\n"
             << "\n";


   // SOLUTION 2
   /*
   try {
      auto const result1 = to_int( s1 );
      auto const result2 = to_int( s2 );
      auto const result3 = to_int( s3 );
      auto const result4 = to_int( s4 );
      auto const result5 = to_int( s5 );

      std::cerr << "\n"
                << " result1 = " << result1 << "\n"
                << " result2 = " << result2 << "\n"
                << " result3 = " << result3 << "\n"
                << " result4 = " << result4 << "\n"
                << " result5 = " << result5 << "\n"
                << "\n";
   }
   catch( std::invalid_argument const& ex )
   {}
   */

   // SOLUTION 3
   /*
   int result1{};
   int result2{};
   int result3{};
   int result4{};
   int result5{};

   [[maybe_unused]] auto const error1 = to_int( s1, result1 );
   [[maybe_unused]] auto const error2 = to_int( s2, result2 );
   [[maybe_unused]] auto const error3 = to_int( s3, result3 );
   [[maybe_unused]] auto const error4 = to_int( s4, result4 );
   [[maybe_unused]] auto const error5 = to_int( s5, result5 );

   std::cerr << "\n"
             << " result1 = " << result1 << "\n"
             << " result2 = " << result2 << "\n"
             << " result3 = " << result3 << "\n"
             << " result4 = " << result4 << "\n"
             << " result5 = " << result5 << "\n"
             << "\n";
   */

   // SOLUTION 4
   /*
   auto const ptr1 = to_int( s1 );
   auto const ptr2 = to_int( s2 );
   auto const ptr3 = to_int( s3 );
   auto const ptr4 = to_int( s4 );
   auto const ptr5 = to_int( s5 );

   auto const result1 = ( ptr1 ? *ptr1 : 0 );
   auto const result2 = ( ptr2 ? *ptr2 : 0 );
   auto const result3 = ( ptr3 ? *ptr3 : 0 );
   auto const result4 = ( ptr4 ? *ptr4 : 0 );
   auto const result5 = ( ptr5 ? *ptr5 : 0 );

   std::cerr << "\n"
             << " result1 = " << result1 << "\n"
             << " result2 = " << result2 << "\n"
             << " result3 = " << result3 << "\n"
             << " result4 = " << result4 << "\n"
             << " result5 = " << result5 << "\n"
             << "\n";
   */

   // SOLUTION 5
   /*
   auto const result1 = to_int( s1 );
   auto const result2 = to_int( s2 );
   auto const result3 = to_int( s3 );
   auto const result4 = to_int( s4 );
   auto const result5 = to_int( s5 );

   std::cerr << "\n"
             << " result1 = " << ( result1.has_value() ? *result1 : 0 ) << "\n"
             << " result2 = " << ( result2.has_value() ? *result2 : 0 ) << "\n"
             << " result3 = " << ( result3.has_value() ? *result3 : 0 ) << "\n"
             << " result4 = " << ( result4.has_value() ? *result4 : 0 ) << "\n"
             << " result5 = " << ( result5.has_value() ? *result5 : 0 ) << "\n"
             << "\n";
   */

   return EXIT_SUCCESS;
}
