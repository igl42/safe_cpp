/**************************************************************************************************
*
* \file CppCheck.cpp
* \brief C++ Training - Demonstration of the static code analysis tool CppCheck
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Use CppCheck to detect the following bugs in the example program: division-by-0,
*       use of uninitialized variables, out-of-bounds access, and use-after-free.
*
**************************************************************************************************/

#include <iostream>
#include <cstdlib>


void f( int i )
{
   std::cout << i << '\n';
}

struct Widget
{
   int i;  // Uninitialized member variable
};

int main()
{
   // Devision by 0 in conditional compilation
   /*
#ifdef A
   x=100/0;
#  ifdef B
      y=100/0;
#  endif
#else
   z=100/0;
#endif
   */

   // Uninitialized variables
   /*
   Widget w;
   f( w.i );
   */

   // Out-of-bounds access
   /*
   int array[10];

   for( int i=0; i<=10; ++i ) {
      array[i] = 0;
   }
   */

   // Memory management (use-after-free)
   /*
   int* ptr = new int[10];
   // ...
   delete ptr;
   for( int i=0; i<10; ++i ) {
      ptr[i] = 0;
   }
   */

   return EXIT_SUCCESS;
}
