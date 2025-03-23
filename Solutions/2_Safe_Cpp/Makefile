#==================================================================================================
#
#  Makefile for chapter "Safe C++"
#
#  Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
#
#  This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
#  context of the C++ training or with explicit agreement by Klaus Iglberger.
#
#==================================================================================================


# Compiler settings
CXX = g++
CXXFLAGS = -std=c++20 -Wall


# Setting the source and binary files
SRC = $(wildcard *.cpp)
BIN = $(SRC:.cpp=)


# Rules
default: Meter_Assembly Meter_Cpp17 Meter_Cpp20 Ranges_constexpr RangesRefactoring_Animals \
         RangesRefactoring_Birthday RangesRefactoring_Countries RangesRefactoring_Recipes \
         Strategy_Refactoring StrongType_Assembly StrongType_Cpp17 StrongType_Cpp20 \
         StrongType_Cpp23 UniquePtr_constexpr Visitor_Refactoring

Meter_Assembly: Meter_Assembly.cpp
	$(CXX) $(CXXFLAGS) -o Meter_Assembly Meter_Assembly.cpp

Meter_Cpp17: Meter_Cpp17.cpp
	$(CXX) $(CXXFLAGS) -o Meter_Cpp17 Meter_Cpp17.cpp

Meter_Cpp20: Meter_Cpp20.cpp
	$(CXX) $(CXXFLAGS) -o Meter_Cpp20 Meter_Cpp20.cpp

Ranges_constexpr: Ranges_constexpr.cpp
	$(CXX) $(CXXFLAGS) -o Ranges_constexpr Ranges_constexpr.cpp

RangesRefactoring_Animals: RangesRefactoring_Animals.cpp
	$(CXX) $(CXXFLAGS) -o RangesRefactoring_Animals RangesRefactoring_Animals.cpp

RangesRefactoring_Birthday: RangesRefactoring_Birthday.cpp
	$(CXX) $(CXXFLAGS) -o RangesRefactoring_Birthday RangesRefactoring_Birthday.cpp

RangesRefactoring_Countries: RangesRefactoring_Countries.cpp
	$(CXX) $(CXXFLAGS) -o RangesRefactoring_Countries RangesRefactoring_Countries.cpp

RangesRefactoring_Recipes: RangesRefactoring_Recipes.cpp
	$(CXX) $(CXXFLAGS) -o RangesRefactoring_Recipes RangesRefactoring_Recipes.cpp

Strategy_Refactoring: Strategy_Refactoring.cpp
	$(CXX) $(CXXFLAGS) -o Strategy_Refactoring Strategy_Refactoring.cpp

StrongType_Assembly: StrongType_Assembly.cpp
	$(CXX) $(CXXFLAGS) -o StrongType_Assembly StrongType_Assembly.cpp

StrongType_Cpp17: StrongType_Cpp17.cpp
	$(CXX) $(CXXFLAGS) -o StrongType_Cpp17 StrongType_Cpp17.cpp

StrongType_Cpp20: StrongType_Cpp20.cpp
	$(CXX) $(CXXFLAGS) -o StrongType_Cpp20 StrongType_Cpp20.cpp

StrongType_Cpp23: StrongType_Cpp23.cpp
	$(CXX) $(CXXFLAGS) -o StrongType_Cpp23 StrongType_Cpp23.cpp

UniquePtr_constexpr: UniquePtr_constexpr.cpp
	$(CXX) $(CXXFLAGS) -o UniquePtr_constexpr UniquePtr_constexpr.cpp

Visitor_Refactoring: Visitor_Refactoring.cpp
	$(CXX) $(CXXFLAGS) -o Visitor_Refactoring Visitor_Refactoring.cpp

clean:
	@$(RM) $(BIN)


# Setting the independent commands
.PHONY: default clean
