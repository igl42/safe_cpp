/**************************************************************************************************
*
* \file AddressSanitizer.cpp
* \brief C++ Training - Demonstration of the static code analysis tool AddressSanitizer
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Use AddressSanitizer to detect the out-of-bounds access in the following demo code.
*
**************************************************************************************************/


//---- <ranges> -----------------------------------------------------------------------------------

#include <concepts>
#include <ranges>
#include <type_traits>

// Simplified implementation of C++23 'std::ranges::to<>()'
template< template<typename...> class C >
struct to_range
{};

template< template<typename...> class C, std::ranges::input_range R >
constexpr auto to( R&& range )
{
   using T = std::ranges::range_value_t<R>;
   static_assert( !std::is_reference_v<T> );
   return C<T>( std::ranges::begin(range), std::ranges::end(range) );
}

template< template<typename...> class C >
constexpr auto to()
{
   return to_range<C>{};
}

template< std::ranges::input_range R, template<typename...> class C >
constexpr auto operator|( R&& range, to_range<C> )
{
   return to<C>(range);
}


//---- <Country.h> --------------------------------------------------------------------------------

#include <iomanip>
#include <ostream>
#include <string>

struct Country
{
   std::string name{};     // Name of the country
   std::string capital{};  // Name of the capital
   unsigned int area{};    // Area in square kilometer
   float residents{};      // Number of residents in millions

   friend std::ostream& operator<<( std::ostream& os, Country const& country )
   {
      os << std::setw(13) << std::left << country.name
         << std::setw(13) << std::left << country.capital
         << std::setw(7)  << std::right << country.area
         << std::setw(6)  << std::right << country.residents;
      return os;
   }

   // Before C++20
   constexpr bool operator==( Country const& other ) const
   {
      return name == other.name &&
             capital == other.capital &&
             area == other.area &&
             residents == other.residents;
   }

   // Since C++20
   //bool operator==( Country const& ) const = default;
};


//---- <Continent.h> ------------------------------------------------------------------------------

//#include <Country.h>
#include <string>
#include <vector>

struct Continent
{
   std::string name{};                // Name of the continent
   std::vector<Country> countries{};  // Countries of the continent
};


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <Continent.h>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <ranges>

void print_countries()
{
   std::vector<Continent> continents
      { Continent{ "South America",
         { Country{ "Brasil", "Brasilia", 8'515'877U, 208.4F }
         , Country{ "Bolivia", "Sucre", 1'098'581U, 11.1F } } }
      , Continent{ "Asia",
         { Country{ "China", "Beijing", 9'596'961U, 1400.0F }
         , Country{ "Indonesia", "Jakarta", 1'904'569U, 264.2F } } }
      };


   std::vector<Country> tmp{};

   for( auto const& continent : continents ) {
      for( auto const& country : continent.countries )
      {
         auto pos = begin(tmp);

         while( pos != end(tmp) && pos->area > country.area )
            ++pos;

         tmp.insert( pos, country );
      }
   }

   std::vector<Country> countries{ begin(tmp), begin(tmp)+5U };

   for( size_t i=1U; i<5U; ++i )
   {
      auto& country1 = countries[i-1U];
      for( size_t j=i; j<5U; ++j ) {
         auto& country2 = countries[j];
         if( country1.residents < country2.residents ) {
            Country tmp{ country1 };
            country1 = country2;
            country2 = tmp;
         }
      }
   }

   for( auto const& country : countries ) {
      std::cout << country << '\n';
   }
}

int main()
{
   print_countries();

   return EXIT_SUCCESS;
}
