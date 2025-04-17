/**************************************************************************************************
*
* \file Erase.cpp
* \brief C++ Training - Example for alternatives to remove elements from a std::vector
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Consider the given 'std::vector<int>'. Remove all odd elements from the vector as
*       efficiently as possible.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <vector>


int main()
{
   std::vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };


   // TODO: Remove all odd elements


   std::cout << "\n v = {";
   for( int i : v ) {
      std::cout << ' ' << i;
   }
   std::cout << "}\n\n";

   return EXIT_SUCCESS;
}
