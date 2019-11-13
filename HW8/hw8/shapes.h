// 
// YOUR FINAL VERSION OF THIS FILE SHOULD NOT INCLUDE ANY EDIT
// TO THIS FILE.
//

#ifndef _SHAPES_H_
#define _SHAPES_H_

#include <cassert>
#include <fstream>
#include <sstream>
#include <vector>
#include "utils.h"

// ==================================================================

// NOTE: These classes have a lot of similarity and it would be quite
// natural (and a good design) to instead implement them using a
// common base class and C++ class inheritance.  We are choosing
// instead to use templated classes...  mostly for practice! :) 

class Disk {
public:
  // CONSTRUCTOR
  Disk(const Point &pt_, double radius_, const Color &color_);
  // ACCESSORS
  int numPoints() const { return 1; }
  const Point& getPoint(int i) const { assert(i == 0); return pt; }
  const Point& getCenter() const { return pt; }
  const Color& getColor() const { return color; }
  const BoundingBox& getBox() const { return bbox; }
  double getRadius() const { return radius; }
  // MODIFIER
  void setColor(const Color &c) { color = c; }
private:
  // REPRESENTATION
  Point pt;
  double radius;
  Color color;
  BoundingBox bbox;
};

// Disk helper function
bool intersect(const Disk &a, const Disk &b);

// ==================================================================

class Triangle {
public:
  // CONSTRUCTOR
  Triangle(const Point &a, const Point &b, const Point &c, const Color &color_);    
  // ACCESSORS
  int numPoints() const { return 3; }
  const Point& getPoint(int i) const { assert(i >= 0 && i < numPoints()); return pts[i]; }
  const Point& getCenter() const { return center; }
  const Color& getColor() const { return color; }
  const BoundingBox& getBox() const { return bbox; }
  // MODIFIER
  void setColor(const Color &c) { color = c; }
private:
  // REPRESENTATION
  Point pts[3];
  Point center;
  Color color;
  BoundingBox bbox;
};

// Triangle helper function
bool intersect(const Triangle &a, const Triangle &b);

// ==================================================================
  
class Quad {
public:
  // CONSTRUCTOR
  Quad(const Point &a, const Point &b, const Point &c, const Point &d, const Color &color_);    
  // ACCESSORS
  int numPoints() const { return 4; }
  const Point& getPoint(int i) const { assert(i >= 0 && i < numPoints()); return pts[i]; }
  const Point& getCenter() const { return center; }
  const Color& getColor() const { return color; }
  const BoundingBox& getBox() const { return bbox; }
  // MODIFIER
  void setColor(const Color &c) { color = c; }
private:
  // REPRESENTATION
  Point pts[4];
  Point center;
  Color color;
  BoundingBox bbox;
};

// Quad helper function
bool intersect(const Quad &a, const Quad &b);

// ==================================================================

// Templated helper function
template <class T>
bool intersect(const std::vector<T> &all, const T &one);

// ==================================================================
  
#endif
