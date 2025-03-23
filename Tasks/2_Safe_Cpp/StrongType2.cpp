/**************************************************************************************************
*
* \file StrongType2.cpp
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
*         namely addition, subtraction, and output/print.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <type_traits>
#include <utility>


//---- <StrongType.h> -----------------------------------------------------------------------------

template< typename T, typename Tag >
class StrongType final
{
 public:
   using value_type = T;

   constexpr StrongType() = default;

   explicit constexpr StrongType( T const& value ) : value_( value ) {}

   explicit constexpr StrongType( T&& value ) : value_( std::move( value ) ) {}

   StrongType( StrongType const& ) = default;
   StrongType( StrongType&& ) = default;
   ~StrongType() = default;
   StrongType& operator=( StrongType const& ) & = default;
   StrongType& operator=( StrongType&& ) & = default;

   constexpr StrongType& operator=( T const& value ) { value_ = value; return *this; }
   constexpr StrongType& operator=( T&& value ) { value_ = std::move(value); return *this; }

   [[nodiscard]] constexpr T&        get()       &  noexcept { return value_; }
   [[nodiscard]] constexpr T const&  get() const &  noexcept { return value_; }
   [[nodiscard]] constexpr T const&& get()       && noexcept { return std::move(value_); }
   [[nodiscard]] constexpr T&&       get() const && noexcept { return std::move(value_); }

   constexpr void swap( StrongType& other ) {
      using std::swap;
      swap( value_, other.value_ );
   }

 private:
   T value_{};

   friend std::ostream& operator<<( std::ostream& os, StrongType const& nt )  // Hidden friend
   {
      os << nt.get();
      return os;
   }
};

template< typename T, typename Tag >
constexpr void swap( StrongType<T,Tag>& a, StrongType<T,Tag>& b )
{
   a.swap( b );
}


//---- <Meter.h> ----------------------------------------------------------------------------------

template< typename T >
using Meter = StrongType<T,struct MeterTag>;

constexpr Meter<long> operator""_m( unsigned long long m ) noexcept
{
   return Meter<long>{ static_cast<long>(m) };
}

//constexpr Meter<long double> operator""_m( long double m ) noexcept
//{
//   return Meter<long double>{ m };
//}


//---- <Kilometer.h> ------------------------------------------------------------------------------

template< typename T >
using Kilometer = StrongType<T,struct KilometerTag>;

constexpr Kilometer<int> operator""_km( unsigned long long m ) noexcept
{
   return Kilometer<int>{ static_cast<int>(m) };
}

//constexpr Kilometer<long double> operator""_km( long double m ) noexcept
//{
//   return Kilometer<long double>{ m };
//}


//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   // Meters
   {
      [[maybe_unused]] auto const m1 = 100_m;

      [[maybe_unused]] Meter<long> m2{};
      m2 = 50L;

      /*
      auto m3 = m1 + m2;  // Addition of two 'Meter' objects
      m3 -= Meter<long>{108L};  // Subtraction assignment

      std::cout << "\n m3  = " << m3 << "m\n\n";
      */
   }

   // Kilometers
   {
      [[maybe_unused]] auto const km1 = 56_km;

      [[maybe_unused]] Kilometer<int> km2{};
      km2 = 44;

      /*
      auto km3 = km1 + km2;  // Addition of two 'Kilometer' objects
      km3 -= Kilometer<int>{58};  // Subtraction assignment

      std::cout << "\n km3  = " << km3 << "m\n\n";
      */
   }

   //static_assert( Meter<long>{100L} + Meter<long>{50L} == Meter<long>{150L} );
   //static_assert( Kilometer<int>{100} - Kilometer<int>{50} != Kilometer<int>{150} );

   return EXIT_SUCCESS;
}
