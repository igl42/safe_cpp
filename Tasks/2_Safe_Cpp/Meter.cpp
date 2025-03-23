/**************************************************************************************************
*
* \file Meter.cpp
* \brief C++ Training - Programming example about strong types and user-defined literals
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Consider the 'Meter', 'Second' and 'MeterPerSecond' classes that serve as wrappers
*       around integral values.
*
* Step 1: What do we need to improve to really make them strong types?
*
* Step 2: Define user-defined literals for the 'Meter', 'Second', and 'MeterPerSecond' types.
*
**************************************************************************************************/


//---- <Meter.h> ----------------------------------------------------------------------------------

#include <ostream>

class Meter
{
 public:
   Meter( double meter )
      : value_( meter )
   {}

   double get() const { return value_; }

 private:
   double value_;
};

std::ostream& operator<<( std::ostream& os, Meter const& meter )
{
   return os << meter.get();
}

Meter operator+( Meter lhs, Meter rhs )  // User-defined arithmetic operation
{
   return Meter{ lhs.get() + rhs.get() };
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <Meter.h>
//#include <Second.h>
//#include <MeterPerSecond.h>
#include <cassert>
#include <cstdlib>
#include <iostream>

int main()
{
   Meter meter1{ 100 };
   assert( meter1.get() == 100 );

   Meter meter2{ 4.0 };
   assert( meter2.get() == 4.0 );

   //Meter meter3{ 42 };     // Should not compile (integral to floating-point conversion)
   //Meter meter4{ 42.0L };  // Should not compile (narrowing conversion)

   Meter meter5{ meter1 + Meter{50} };  // Meter<int>
   assert( meter5.get() == 150 );

   //5_m = -21_m;  // Does and should not compile (this contains 2 problems).

   return EXIT_SUCCESS;
}
