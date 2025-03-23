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
default: AddressSanitizer CppCheck Meter_Assembly Meter Ranges_constexpr \
         RangesRefactoring_Animals RangesRefactoring_Birthday RangesRefactoring_Countries \
         RangesRefactoring_Recipes Strategy_Refactoring StrongType_Assembly StrongType \
         StrongType1 StrongType2 StrongType3 UniquePtr_constexpr Visitor_Refactoring

AddressSanitizer: AddressSanitizer.cpp
	$(CXX) $(CXXFLAGS) -o AddressSanitizer AddressSanitizer.cpp

CppCheck: CppCheck.cpp
	$(CXX) $(CXXFLAGS) -o CppCheck CppCheck.cpp

Meter_Assembly: Meter_Assembly.cpp
	$(CXX) $(CXXFLAGS) -o Meter_Assembly Meter_Assembly.cpp

Meter: Meter.cpp
	$(CXX) $(CXXFLAGS) -o Meter Meter.cpp

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

StrongType: StrongType.cpp
	$(CXX) $(CXXFLAGS) -o StrongType StrongType.cpp

StrongType1: StrongType1.cpp
	$(CXX) $(CXXFLAGS) -o StrongType1 StrongType1.cpp

StrongType2: StrongType2.cpp
	$(CXX) $(CXXFLAGS) -o StrongType2 StrongType2.cpp

StrongType3: StrongType3.cpp
	$(CXX) $(CXXFLAGS) -o StrongType3 StrongType3.cpp

UniquePtr_constexpr: UniquePtr_constexpr.cpp
	$(CXX) $(CXXFLAGS) -o UniquePtr_constexpr UniquePtr_constexpr.cpp

Visitor_Refactoring: Visitor_Refactoring.cpp
	$(CXX) $(CXXFLAGS) -o Visitor_Refactoring Visitor_Refactoring.cpp

clean:
	@$(RM) $(BIN)


# Setting the independent commands
.PHONY: default clean
