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

#include <concepts>
#include <ostream>
#include <type_traits>
#include <utility>

template< typename T, typename Tag >
class StrongType final
{
 public:
   using value_type = T;

   constexpr StrongType() = default;

   // Constructor option 1: Two constructors for lvalues and rvalues
   /*
   explicit constexpr StrongType( T const& value ) : value_( value )
   {}

   explicit constexpr StrongType( T&& value ) requires ( not std::is_reference_v<T> )
      : value_( std::move( value ) )
   {}
   */

   // Constructor option 2: One constructor with forwarding reference, convertible types allowed
   template< typename U >
      requires std::constructible_from<T,U>
   explicit constexpr StrongType( U&& value ) : value_( std::forward<U>(value) )
   {}

   // Constructor option 3: One constructor with forwarding reference, no (narrowing) conversion allowed
   /*
   template< typename U >
      requires std::same_as<std::remove_cvref_t<U>,T>
   constexpr explicit StrongType( U&& value )
      : value_{ std::forward<U>(value) }
   {}
   */

   template< typename U >
      requires std::constructible_from<T,U>
   constexpr explicit StrongType( StrongType<U,Tag> const& value )
      : value_{ value.get() }
   {}

   template< typename U >
      requires std::constructible_from<T,U>
   constexpr explicit StrongType( StrongType<U,Tag>&& value )
      : value_{ std::move(value).get() }
   {}

   StrongType( StrongType const& ) = default;
   StrongType( StrongType&& ) = default;
   ~StrongType() = default;
   StrongType& operator=( StrongType const& ) & = default;
   StrongType& operator=( StrongType&& ) & = default;

   // Assignment operator option 1: Two assignment operators for lvalues and rvalues
   /*
   constexpr StrongType& operator=( T const& value ) { value_ = value; return *this; }
   constexpr StrongType& operator=( T&& value ) { value_ = std::move(value); return *this; }
   */

   // Assignment operator option 2: One assignment operator with forwarding reference, convertible types allowed
   template< typename U >
      requires std::assignable_from<T&,U>
   constexpr StrongType& operator=( U&& value )
   {
      value_ = std::forward<U>(value);
      return *this;
   }

   // Assignment operator option 3: One assignment with forwarding reference, no (narrowing) conversion allowed
   /*
   template< typename U >
      requires std::same_as<std::remove_cvref_t<U>,T>
   constexpr StrongType& operator=( U&& value )
   {
      if constexpr( is_detected_v< hasCheckValue, StrongType, T > ) {
         this->checkValue( value );
      }

      value_ = std::forward<U>(value);
      return *this;
   }
   */

   template< typename U >
      requires std::assignable_from<T&,U>
   constexpr StrongType& operator=( StrongType<U,Tag> const& strong )
   {
      value_ = strong.get();
      return *this;
   }

   template< typename U >
      requires std::assignable_from<T&,U>
   constexpr StrongType& operator=( StrongType<U,Tag>&& strong )
   {
      value_ = std::move(strong).get();
      return *this;
   }

   [[nodiscard]] constexpr T const& get() const &  noexcept { return value_; }
   [[nodiscard]] constexpr T&&      get()       && noexcept { return value_; }

   constexpr void swap( StrongType& other ) noexcept( std::is_nothrow_swappable_v<T> )
   {
      std::ranges::swap( value_, other.value_ );
   }

 private:
   T value_{};

   friend std::ostream& operator<<( std::ostream& os, StrongType const& s )  // Hidden friend
   {
      os << s.get();
      return os;
   }

   template< typename T_, typename Tag_ >
   friend constexpr void swap( StrongType<T_,Tag_>& a, StrongType<T_,Tag_>& b )  // Hidden friend
      noexcept( std::is_nothrow_swappable_v<T_> )
   {
      a.swap( b );
   }
};


//---- <Main.cpp.h> -------------------------------------------------------------------------------

//#include <StrongType.h>
#include <cstdlib>
#include <iostream>

using Meter = StrongType<int,struct MeterTag>;

int test( int meter )
{
   return meter+7;
}

Meter test( Meter meter )
{
   return Meter{ meter.get()+7 };
}

int main()
{
   // Integral type
   int const i1 = 35;
   int const i2 = test( i1 );

   std::cout << "\n i = " << i2 << "\n\n";

   // Strong type
   Meter const m1{ 35 };
   Meter const m2 = test( m1 );

   std::cout << "\n m = " << m2 << "\n\n";

   return EXIT_SUCCESS;
}

