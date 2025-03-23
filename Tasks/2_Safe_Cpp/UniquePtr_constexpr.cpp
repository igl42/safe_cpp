/**************************************************************************************************
*
* \file UniquePtr_constexpr.cpp
* \brief C++ Training - constexpr Example
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: What is wrong with the following given 'unique_ptr' class template? Try to find all
*       flaws and think about how you would test the class to detect these flaws.
*
**************************************************************************************************/

#include <cassert>
#include <cstdlib>
#include <utility>


//---- <memory> -----------------------------------------------------------------------------------

template< typename T >
class unique_ptr
{
 public:
   unique_ptr() {}
   unique_ptr( T* ptr ) : ptr_{ptr} {}

   T& operator*() const { return *ptr_; }
   T* get() const { return ptr_; }

 private:
   T* ptr_;
};


//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   assert( []()
   {
      unique_ptr<int> ptr;
      return ptr.get() == nullptr;
   }() );

   assert( []()
   {
      unique_ptr<int> ptr{ new int(42) };
      return ptr.get() != nullptr;
   }() );

   assert( []()
   {
      unique_ptr<int> ptr1{ new int(42) };
      unique_ptr<int> ptr2{ std::move(ptr1) };
      return ptr2.get() != nullptr && *ptr2 == 42;
   }() );

   return EXIT_SUCCESS;
}
