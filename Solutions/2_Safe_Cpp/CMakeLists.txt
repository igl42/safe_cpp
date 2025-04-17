#==================================================================================================
#
#  CMakeLists for chapter "Safe C++"
#
#  Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
#
#  This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
#  context of the C++ training or with explicit agreement by Klaus Iglberger.
#
#==================================================================================================

cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)

add_executable(Erase
   Erase.cpp
   )

add_executable(Meter_Assembly
   Meter_Assembly.cpp
   )

add_executable(Meter_Cpp17
   Meter_Cpp17.cpp
   )

add_executable(Meter_Cpp20
   Meter_Cpp20.cpp
   )

add_executable(Ranges_constexpr
   Ranges_constexpr.cpp
   )

add_executable(RangesRefactoring_Animals
   RangesRefactoring_Animals.cpp
   )

add_executable(RangesRefactoring_Birthday
   RangesRefactoring_Birthday.cpp
   )

add_executable(RangesRefactoring_Countries
   RangesRefactoring_Countries.cpp
   )

add_executable(RangesRefactoring_Recipes
   RangesRefactoring_Recipes.cpp
   )

add_executable(Strategy_Refactoring
   Strategy_Refactoring.cpp
   )

add_executable(StrongType_Assembly
   StrongType_Assembly.cpp
   )

add_executable(StrongType_Cpp17
   StrongType_Cpp17.cpp
   )

add_executable(StrongType_Cpp20
   StrongType_Cpp20.cpp
   )

add_executable(StrongType_Cpp23
   StrongType_Cpp23.cpp
   )

add_executable(ToInt
   ToInt.cpp
   )

add_executable(UniquePtr_constexpr
   UniquePtr_constexpr.cpp
   )

add_executable(Visitor_Refactoring
   Visitor_Refactoring.cpp
   )

set_target_properties(
   Erase
   Meter_Assembly
   Meter_Cpp17
   Meter_Cpp20
   Ranges_constexpr
   RangesRefactoring_Animals
   RangesRefactoring_Birthday
   RangesRefactoring_Countries
   RangesRefactoring_Recipes
   Strategy_Refactoring
   StrongType_Assembly
   StrongType_Cpp17
   StrongType_Cpp20
   StrongType_Cpp23
   ToInt
   UniquePtr_constexpr
   Visitor_Refactoring
   PROPERTIES
   FOLDER "2_Safe_C++"
   )
