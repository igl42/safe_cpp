/**************************************************************************************************
*
* \file Meter_Cpp20.cpp
* \brief C++ Training - Programming example about strong types and user-defined literals
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Consider the 'Meter' class that serve as wrapper around integral values.
*
* Step 1: What do we need to improve to really make this a strong type?
*
* Step 2: Define user-defined literals for the 'Meter' type.
*
**************************************************************************************************/


//---- <Meter.h> ----------------------------------------------------------------------------------

// Necessary improvements:
// 1. The constructor(s) should be 'explicit' to avoid implicit converions
// 2. The constructor(s) should control conversions (e.g. with constraints)
// 3. All operations should be 'constexpr' (if possible)
//
// Reasonable improvements:
// 4. The class should be 'final' to avoid misuse as a base class
// 5. The class should be templated to allow for different kinds of 'Meter'
// 6. The template parameter 'T' should be checked by means of a constraint
// 7. The 'get()' function should get the attribute 'nodiscard' to avoid misuse
// 8. The output operator should be a "hidden friend" to minimize compile time overhead
//
// Nice-to-have improvements:
// 9. The class could have a default constructor, given that the 'value_' is properly initialized
// 10. There could be a user-defined literal to allow easy setup of meters
// 11. The assignment operators could be marked with an lvalue reference qualifier

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

template< typename T >
Meter( T ) -> Meter<T>;  // User-defined deduction guide

constexpr Meter<long> operator""_m( unsigned long long meter )  // User-defined literal
{
   return Meter<long>{ static_cast<long>( meter ) };
}

constexpr Meter<double> operator""_m( long double meter )  // User-defined literal
{
   return Meter<double>{ static_cast<double>( meter ) };
}

template< typename T >
constexpr Meter<T> operator+( Meter<T> lhs, Meter<T> rhs )  // User-defined arithmetic operation
{
   return Meter<T>{ lhs.get() + rhs.get() };
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <Meter.h>
#include <concepts>
#include <cstdlib>
#include <iostream>

int main()
{
   constexpr Meter meter1{ 100 };  // Meter<int>
   static_assert( std::same_as<decltype(meter1),Meter<int> const> );
   static_assert( meter1.get() == 100 );

   constexpr Meter meter2{ 4.0 };  // Meter<double>
   static_assert( std::same_as<decltype(meter2),Meter<double> const> );
   static_assert( meter2.get() == 4.0 );

   //Meter meter3<double>{ 42 };     // Does not compile (integral to floating-point conversion)
   //Meter meter4<double>{ 42.0L };  // Does not compile (narrowing conversion)

   constexpr Meter meter5{ meter1 + Meter{50} };  // Meter<int>
   static_assert( std::same_as<decltype(meter5),Meter<int> const> );
   static_assert( meter5.get() == 150 );

   //Meter meter5{ meter1 + meter2 };  // Does not compile

   //5_m = -21_m;  // Does and should not compile (this contains 2 problems).

   return EXIT_SUCCESS;
}
