// 
// YOUR FINAL VERSION OF THIS FILE SHOULD NOT INCLUDE ANY EDITS
// TO THIS FILE.
//

#ifndef _UTILS_H_
#define _UTILS_H_

#include <cassert>
#include <fstream>
#include <sstream>

// ==================================================================
// Point stores a two-dimensional coordinate.

class Point {
public:
  Point (double x_=0, double y_=0) : x(x_),y(y_) {}
  double x;
  double y;
};

// Point helper functions
std::ostream& operator<< (std::ostream &ostr, const Point &p);
double distance(const Point &p1, const Point &p2);
  
// ==================================================================
// Color stores an r,g,b triple
// Note: 0,0,0 == black and 255,255,255 == white

class Color {
public:
  Color (int r_, int g_, int b_) : r(r_),g(g_),b(b_) {}
  std::string getHexString() const;
  void mix(Color c2,float f=0.5);
  int r;
  int g;
  int b;
};

std::ostream& operator<< (std::ostream &ostr, const Color &c);

// ==================================================================
// The bounding box is the smallest axis-aligned, region that contains
// an object or all of the elements in a collection.  We represent the
// bounding box with the minimum and maximum coordinates.  The box can
// be extended or increased in size to fit additional elements.

class BoundingBox {
public:
  // CONSTRUCTOR
  BoundingBox(Point min_=Point(), Point max_=Point())
    : min(min_),max(max_) {}

  // ACCESSORS
  const Point& getMin() const { return min; }
  const Point& getMax() const { return max; }
  double dx() const { return max.x-min.x; }
  double dy() const { return max.y-min.y; }
  double getArea() const { return dx()*dy(); }
  bool overlaps(const BoundingBox &bbox) const;

  // MODIFIERS
  void extend(const Point &a);
  void extend(const BoundingBox &bbox);
  
  // DRAW TO SVG
  void render(std::ostream &ostr, const Color &color) const;

private:
  // REPRESENTATION
  Point min;
  Point max;
};

// Bounding Box helper functions
std::ostream& operator<<(std::ostream &ostr, const BoundingBox &bb);

// ==================================================================

#endif
