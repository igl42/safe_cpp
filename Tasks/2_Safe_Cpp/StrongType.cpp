/**************************************************************************************************
*
* \file StrongType.cpp
* \brief C++ Training - Programming example about strong types and user-defined literals
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Refactor the following code by means of strong types and according user-defined literals.
*
* Step 1: Define the 'StrongType' class template as a basis for strong types. Use it to define
*         the strong 'Meter' and 'Kilometer' class templates.
*
* Step 2: Define user-defined literals for both the 'Meter' and 'Kilometer' type.
*
* Step 3: Extend the 'StrongType' type to enable strong reference types.
*
* Step 4: Extend the 'StrongType' type to support operations provided by the underlying type,
*         namely addition, subtraction, output/print, and equality comparison.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <type_traits>
#include <utility>


//---- <StrongType.h> -----------------------------------------------------------------------------

template< typename T >
class StrongType
{
 public:
   using value_type = T;

   // Step 1: Constructors

   // Step 1: Assignment operators

   // Step 1: Access functions to the underlying value type

   // Step 1: swap

 private:
   T value_;
};


//---- <Meter.h> ----------------------------------------------------------------------------------

// Step 1: Define the strong 'Meter' type

// Step 2: Define a user-defined literal for the 'Meter' type


//---- <Kilometer.h> ------------------------------------------------------------------------------

// Step 1: Define the strong 'Kilometer' type

// Step 2: Define a user-defined literal for the 'Kilometer' type


//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   // Meters
   /*
   {
      auto const m1 = Meter<long>{ 100L };

      Meter<long> m2{};
      m2 = 50L;

      auto m3 = m1 + m2;  // Addition of two 'Meter' objects
      m3 -= Meter<long>{108L};  // Subtraction assignment

      std::cout << "\n m3  = " << m3 << "m\n\n";
   }
   */

   // Kilometers
   /*
   {
      auto const km1 = Kilometer<int>{ 56 };

      Kilometer<int> km2{};
      km2 = 44;

      auto km3 = km1 + km2;  // Addition of two 'Kilometer' objects
      km3 -= Kilometer<int>{58};  // Subtraction assignment

      std::cout << "\n km3  = " << km3 << "m\n\n";
   }
   */

   //static_assert( Meter<long>{100L} + Meter<long>{50L} == Meter<long>{150L} );
   //static_assert( Kilometer<int>{100} - Kilometer<int>{50} != Kilometer<int>{150} );

   return EXIT_SUCCESS;
}
