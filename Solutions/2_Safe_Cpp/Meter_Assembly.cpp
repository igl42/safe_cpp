/**************************************************************************************************
*
* \file Meter_Assembly.cpp
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


//---- <Meter.h> ----------------------------------------------------------------------------------

#include <concepts>
#include <ostream>
#include <type_traits>

template< typename T >
   requires std::is_arithmetic_v<T>  // Constraint on the template parameter: only arithmetic types allowed!
class Meter final
{
 public:
   constexpr Meter() = default;

   template< typename U >
      requires std::same_as<T,U>  // Constraint on the parameter: no conversion allowed!
   explicit constexpr Meter( U meter )
      : value_( meter )
   {}

   Meter( Meter const& ) = default;
   Meter( Meter&& ) = default;
   ~Meter() = default;
   Meter& operator=( Meter const& ) & = default;
   Meter& operator=( Meter&& ) & = default;

   [[nodiscard]] constexpr T get() const noexcept { return value_; }

 private:
   T value_{};

   friend std::ostream& operator<<( std::ostream& os, Meter const& meter )  // Hidden friend
   {
      return os << meter.get();
   }
};


//---- <Main.cpp.h> -------------------------------------------------------------------------------

//#include <Meter.h>
#include <cstdlib>
#include <iostream>

int test( int meter )
{
   return meter+7;
}

Meter<int> test( Meter<int> meter )
{
   return Meter<int>{ meter.get()+7 };
}

int main()
{
   // Integral type
   int const i1 = 35;
   int const i2 = test( i1 );

   std::cout << "\n i = " << i2 << "\n\n";

   // Strong type
   Meter<int> const m1{ 35 };
   Meter<int> const m2 = test( m1 );

   std::cout << "\n m = " << m2 << "\n\n";

   return EXIT_SUCCESS;
}

