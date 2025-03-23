/**************************************************************************************************
*
* \file StrongType_Cpp20.cpp
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
*         the strong 'Meter' and 'Kilometer' types.
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
#include <algorithm>
#include <iostream>
#include <type_traits>
#include <utility>


//---- <Addable.h> --------------------------------------------------------------------------------

template< typename Derived >
struct Addable
{
   friend constexpr Derived& operator+=( Derived& lhs, Derived const& rhs )
      noexcept( noexcept( lhs.get() += rhs.get() ) )
   {
      lhs.get() += rhs.get();
      return lhs;
   }

   friend constexpr Derived operator+( Derived const& lhs, Derived const& rhs )
      noexcept( noexcept( lhs.get() + rhs.get() ) )
   {
      return Derived{ lhs.get() + rhs.get() };
   }
};


//---- <Subtractable.h> ---------------------------------------------------------------------------

template< typename Derived >
struct Subtractable
{
   friend constexpr Derived& operator-=( Derived& lhs, Derived const& rhs )
      noexcept( noexcept( lhs.get() -= rhs.get() ) )
   {
      lhs.get() -= rhs.get();
      return lhs;
   }

   friend constexpr Derived operator-( Derived const& lhs, Derived const& rhs )
      noexcept( noexcept( lhs.get() - rhs.get() ) )
   {
      return Derived{ lhs.get() - rhs.get() };
   }
};


//---- <IntegralArithmetic.h> ---------------------------------------------------------------------

template< typename Derived >
struct IntegralArithmetic
   : public Addable<Derived>
   , public Subtractable<Derived>
{};


//---- <Printable.h> ------------------------------------------------------------------------------

template< typename Derived >
struct Printable
{
   friend std::ostream& operator<<( std::ostream& os, Derived const& d )
   {
      os << d.get();
      return os;
   }
};


//---- <EqualityComparable.h> ---------------------------------------------------------------------

template< typename Derived >
struct EqualityComparable
{
   friend constexpr bool operator==( Derived const& lhs, Derived const& rhs )
   {
      return lhs.get() == rhs.get();
   }
};


//---- Positive -----------------------------------------------------------------------------------

template< typename Derived >
struct Positive
{
   template< typename T >
   constexpr void checkValue( T const& value ) const {
      if( value < T{} ) {
         throw std::invalid_argument( "Negative value detected" );
      }
   }
};


//---- <StrongType.h> -----------------------------------------------------------------------------

template< typename T, typename Tag, template<typename...> class... Skills >
class StrongType final
   : public Skills< StrongType<T,Tag,Skills...> >...
{
 public:
   using value_type = T;

   constexpr StrongType() = default;

   // Constructor option 1: Two constructors for lvalues and rvalues
   /*
   explicit constexpr StrongType( T const& value ) : value_( value )
   {
      if constexpr( requires { this->checkValue(value_); } ) {
         this->checkValue(value_);
      }
   }

   explicit constexpr StrongType( T&& value ) requires ( not std::is_reference_v<T> )
      : value_( std::move( value ) )
   {
      if constexpr( requires { this->checkValue(value_); } ) {
         this->checkValue(value_);
      }
   }
   */

   // Constructor option 2: One constructor with forwarding reference, convertible types allowed
   template< typename U >
      requires std::constructible_from<T,U>
   explicit constexpr StrongType( U&& value ) : value_( std::forward<U>(value) )
   {
      if constexpr( requires { this->checkValue(value_); } ) {
         this->checkValue(value_);
      }
   }

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
   constexpr explicit StrongType( StrongType<U,Tag,Skills...> const& value )
      : value_{ value.get() }
   {}

   template< typename U >
      requires std::constructible_from<T,U>
   constexpr explicit StrongType( StrongType<U,Tag,Skills...>&& value )
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
      if constexpr( requires { this->checkValue(value_); } ) {
         this->checkValue(value_);
      }

      value_ = std::forward<U>(value);
      return *this;
   }

   // Assignment operator option 3: One assignment with forwarding reference, no (narrowing) conversion allowed
   /*
   template< typename U >
      requires std::same_as<std::remove_cvref_t<U>,T>
   constexpr StrongType& operator=( U&& value )
   {
      if constexpr( requires { this->checkValue(value_); } ) {
         this->checkValue(value_);
      }

      value_ = std::forward<U>(value);
      return *this;
   }
   */

   template< typename U >
      requires std::assignable_from<T&,U>
   constexpr StrongType& operator=( StrongType<U,Tag,Skills...> const& strong )
   {
      value_ = strong.get();
      return *this;
   }

   template< typename U >
      requires std::assignable_from<T&,U>
   constexpr StrongType& operator=( StrongType<U,Tag,Skills...>&& strong )
   {
      value_ = std::move(strong).get();
      return *this;
   }

   [[nodiscard]] constexpr T&        get()       &  noexcept { return value_; }
   [[nodiscard]] constexpr T const&  get() const &  noexcept { return value_; }
   [[nodiscard]] constexpr T const&& get()       && noexcept { return std::move(value_); }
   [[nodiscard]] constexpr T&&       get() const && noexcept { return std::move(value_); }

   constexpr void swap( StrongType& other ) noexcept( std::is_nothrow_swappable_v<T> )
   {
      std::ranges::swap( value_, other.value_ );
   }

 private:
   T value_{};
};

template< typename T, typename Tag, template<typename> class... Skills >
constexpr void swap( StrongType<T,Tag,Skills...>& a, StrongType<T,Tag,Skills...>& b )
   noexcept( std::is_nothrow_swappable_v<T> )
{
   a.swap( b );
}


//---- <Meter.h> ----------------------------------------------------------------------------------

template< typename T >
using Meter = StrongType<T,struct MeterTag,IntegralArithmetic,Printable,EqualityComparable,Positive>;

[[nodiscard]] constexpr Meter<long> operator""_m( unsigned long long m ) noexcept
{
   return Meter<long>{ static_cast<long>(m) };
}

[[nodiscard]] constexpr Meter<long double> operator""_m( long double m ) noexcept
{
   return Meter<long double>{ m };
}


//---- <Kilometer.h> ------------------------------------------------------------------------------

template< typename T >
using Kilometer = StrongType<T,struct KilometerTag,IntegralArithmetic,Printable,EqualityComparable>;

[[nodiscard]] constexpr Kilometer<int> operator""_km( unsigned long long m ) noexcept
{
   return Kilometer<int>{ static_cast<int>(m) };
}

[[nodiscard]] constexpr Kilometer<long double> operator""_km( long double m ) noexcept
{
   return Kilometer<long double>{ m };
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   // Meters
   {
      auto const m1 = Meter<long>{ 100L };

      Meter<long> m2{};
      m2 = 50L;

      auto m3 = m1 + m2;  // Addition of two 'Meter' objects
      m3 -= Meter<long>{108L};  // Subtraction assignment

      std::cout << "\n m3  = " << m3 << "m\n\n";
   }

   // Kilometers
   {
      auto const km1 = Kilometer<int>{ 56 };

      Kilometer<int> km2{};
      km2 = 44;

      auto km3 = km1 + km2;  // Addition of two 'Kilometer' objects
      km3 -= Kilometer<int>{58};  // Subtraction assignment

      std::cout << "\n km3  = " << km3 << "m\n\n";
   }

   static_assert( Meter<long>{100L} + Meter<long>{50L} == Meter<long>{150L} );
   static_assert( Kilometer<int>{100} - Kilometer<int>{50} != Kilometer<int>{150} );

   return EXIT_SUCCESS;
}
