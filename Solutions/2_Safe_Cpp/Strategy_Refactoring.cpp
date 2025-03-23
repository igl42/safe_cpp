/**************************************************************************************************
*
* \file Strategy_Refactoring.cpp
* \brief C++ Training - Programming Task for the Strategy Design Pattern
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: Refactor the classic Strategy solution by a value semantics based solution. Note that
*         the general behavior should remain unchanged.
*
* Step 2: Switch from one to another graphics library. Discuss the feasibility of the change:
*         how easy is the change? How many pieces of code on which level of the architecture
*         have to be touched?
*
* Step 3: Add an 'area()' operations for all shapes. How easy is the change? How many pieces
*         of code on which level of the architecture have to be touched? Hint: the area of a
*         circle is 'radius*radius*M_PI', the area of a square is 'side*side'.
*
* Task 4: Add the new feature to serialize shapes by means of the 'FastSerialization' library.
*         Observe how well the new code can be integrated and how many new dependencies are
*         created.
*
**************************************************************************************************/


//---- <GraphicsLibrary.h> (external) -------------------------------------------------------------

#include <string>
// ... and many more graphics-related headers

namespace gl {

enum class Color
{
   red   = 0xFF0000,
   green = 0x00FF00,
   blue  = 0x0000FF
};

std::string to_string( Color color )
{
   switch( color ) {
      case Color::red:
         return "red (0xFF0000)";
      case Color::green:
         return "green (0x00FF00)";
      case Color::blue:
         return "blue (0x0000FF)";
      default:
         return "unknown";
   }
}

} // namespace gl


//---- <GraphicsFramework.h> (external) -----------------------------------------------------------

#include <sstream>
#include <string>
// ... and many more graphics-related headers

namespace gf {

enum class Color : int
{
   yellow  = 0xFFFF00,
   cyan    = 0x00FFFF,
   magenta = 0xFF00FF
};

using Brightness = unsigned int;

std::string print_string( Color color, Brightness brightness )
{
   std::ostringstream oss;

   switch( color ) {
      case Color::yellow:
         oss << "yellow (0xFFFF00)";
         break;
      case Color::cyan:
         oss << "cyan (0x00FFFF)";
         break;
      case Color::magenta:
         oss << "magenta (0xFF00FF)";
         break;
      default:
         oss << "unknown";
         break;
   }

   oss << ", brightness=" << brightness;

   return oss.str();
}

} // namespace gf


//---- <FastSerialization.h> (external) -----------------------------------------------------------

#include <cstddef>
#include <string>
#include <type_traits>
#include <vector>
// ... and many more serialization-related headers

namespace fs {

class Serializer
{
 public:
   std::string to_string() const
   {
      return std::string( buffer_.data(), buffer_.size() );
   }

 private:
   std::vector<char> buffer_;

   template< typename T, typename = std::enable_if_t< std::is_arithmetic_v<T> > >
   //   requires std::is_arithmetic_v<T>  // C++20 concept
   friend Serializer& operator<<( Serializer& serializer, T value )
   {
      size_t const old_size = serializer.buffer_.size();
      serializer.buffer_.resize( old_size + sizeof(T) );

      auto* data = serializer.buffer_.data() + old_size;
      ::new (data) T{value};

      return serializer;
   }
};

} // namespace fs


//---- <Point.h> ----------------------------------------------------------------------------------

struct Point
{
   double x;
   double y;
};


//---- <Shape.h> ----------------------------------------------------------------------------------

#include <string>

class Shape
{
 public:
   virtual ~Shape() = default;

   virtual void draw( /*Graphics-related parameters*/ ) const = 0;
   virtual std::string serialize( /*Serialization-related parameters*/ ) const = 0;  // Intrusive change!
};


//---- <Circle.h> ---------------------------------------------------------------------------------

//#include <Point.h>
//#include <Shape.h>
#include <functional>
#include <stdexcept>

class Circle : public Shape
{
 public:
   using DrawStrategy = std::function<void(Circle const&)>;
   using SerializationStrategy = std::function<std::string(Circle const&)>;

   explicit Circle( double radius, DrawStrategy drawer, SerializationStrategy serializer )
      : radius_{ radius }
      , center_{}
      , drawer_{ drawer }
      , serializer_{ serializer }
   {
      if( !drawer_ ) {
         throw std::invalid_argument( "Invalid draw strategy" );
      }
      if( !serializer_ ) {
         throw std::invalid_argument( "Invalid serialization strategy" );
      }
   }

   void draw() const override { drawer_(*this); }
   std::string serialize() const override { return serializer_(*this); }

   double radius() const { return radius_; }
   Point  center() const { return center_; }

 private:
   double radius_;
   Point center_;
   DrawStrategy drawer_;
   SerializationStrategy serializer_;
};


//---- <Square.h> ---------------------------------------------------------------------------------

//#include <Point.h>
//#include <Shape.h>
#include <functional>
#include <stdexcept>

class Square : public Shape
{
 public:
   using DrawStrategy = std::function<void(Square const&)>;
   using SerializationStrategy = std::function<std::string(Square const&)>;

   explicit Square( double side, DrawStrategy drawer, SerializationStrategy serializer )
      : side_{ side }
      , center_{}
      , drawer_{ drawer }
      , serializer_{ serializer }
   {
      if( !drawer_ ) {
         throw std::invalid_argument( "Invalid draw strategy" );
      }
      if( !serializer_ ) {
         throw std::invalid_argument( "Invalid serialization strategy" );
      }
   }

   void draw() const override { drawer_(*this); }
   std::string serialize() const override { return serializer_(*this); }

   double side() const { return side_; }
   Point  center() const { return center_; }

 private:
   double side_;
   Point center_;
   DrawStrategy drawer_;
   SerializationStrategy serializer_;
};


//---- <Shapes.h> ---------------------------------------------------------------------------------

//#include <Shape.h>
#include <memory>
#include <vector>

using Shapes = std::vector<std::unique_ptr<Shape>>;


//==== ARCHITECTURAL BOUNDARY =====================================================================


//---- <GLDrawer.h> -------------------------------------------------------------------------------

//#include <Circle.h>
//#include <Square.h>
//#include <GraphicsLibrary.h>
#include <iostream>

class GLDrawer
{
 public:
   explicit GLDrawer( gl::Color color ) : color_{color} {}

   void operator()( Circle const& circle ) const
   {
      std::cout << "circle: radius=" << circle.radius()
                << ", color = " << gl::to_string(color_) << '\n';
   }

   void operator()( Square const& square ) const
   {
      std::cout << "square: side=" << square.side()
                << ", color = " << gl::to_string(color_) << '\n';
   }

 private:
   gl::Color color_{};
};


//---- <DrawAllShapes.h> --------------------------------------------------------------------------

//#include <Shapes.h>

void drawAllShapes( Shapes const& shapes );


//---- <DrawAllShapes.cpp> ------------------------------------------------------------------------

//#include <DrawAllShapes.h>

void drawAllShapes( Shapes const& shapes )
{
   for( auto const& shape : shapes )
   {
      shape->draw();
   }
}


//---- <FSSerializer.h> ---------------------------------------------------------------------------

//#include <Circle.h>
//#include <Square.h>
//#include <FastSerialization.h>

class FSSerializer
{
 public:
   std::string operator()( Circle const& circle ) const
   {
      fs::Serializer serializer{};
      serializer << typeid(Circle).hash_code() << circle.radius()
                 << circle.center().x << circle.center().y;
      return serializer.to_string();
   }

   std::string operator()( Square const& square ) const
   {
      fs::Serializer serializer{};
      serializer << typeid(Square).hash_code() << square.side()
                 << square.center().x << square.center().y;
      return serializer.to_string();
   }
};


//---- <SerializeAllShapes.h> ---------------------------------------------------------------------

//#include <Shapes.h>

void serializeAllShapes( Shapes const& shapes );


//---- <SerializeAllShapes.cpp> -------------------------------------------------------------------

//#include <SerializeAllShapes.h>
#include <iostream>

void serializeAllShapes( Shapes const& shapes )
{
   std::string serialized_shapes{};

   for( auto const& shape : shapes )
   {
      serialized_shapes += shape->serialize();
   }

   std::cout << "Serialized shapes: \"" << serialized_shapes << "\"\n";
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <Circle.h>
//#include <Square.h>
//#include <Shapes.h>
//#include <DrawAllShapes.h>
//#include <GLDrawer.h>
#include <cstdlib>

int main()
{
   Shapes shapes{};

   shapes.emplace_back( std::make_unique<Circle>( 2.3, GLDrawer{gl::Color::red}, FSSerializer{} ) );
   shapes.emplace_back( std::make_unique<Square>( 1.2, GLDrawer{gl::Color::green}, FSSerializer{} ) );
   shapes.emplace_back( std::make_unique<Circle>( 4.1, GLDrawer{gl::Color::blue}, FSSerializer{} ) );

   drawAllShapes( shapes );

   serializeAllShapes( shapes );

   return EXIT_SUCCESS;
}

