// 
// YOUR FINAL VERSION OF THIS FILE SHOULD NOT INCLUDE ANY EDITS
// TO THIS FILE.
//

#include <cmath>
#include <iostream>
#include "shapes.h"

// ==================================================================
// Disk constructor

Disk::Disk(const Point &pt_, double radius_, const Color &color_) :
  pt(pt_),  radius(radius_), color(color_) {
  bbox = BoundingBox(Point(pt.x-radius,pt.y-radius),
                     Point(pt.x+radius,pt.y+radius));
}

// Disk helper function
bool intersect(const Disk &a, const Disk &b) {
  Point pta = a.getCenter();
  Point ptb = b.getCenter();
  double ra = a.getRadius();
  double rb = b.getRadius();
  double distance_between_centers = distance(pta,ptb);
  if (distance_between_centers <= ra+rb)
    return true;
  return false;
}

// ==================================================================
// Triangle constructor

Triangle::Triangle(const Point &a, const Point &b, const Point &c, const Color &color_) :
  color(color_) , bbox(a,a) {
  pts[0] = a; pts[1] = b; pts[2] = c;
  bbox.extend(b);
  bbox.extend(c);
  center = Point((a.x+b.x+c.x)/3.0,
                 (a.y+b.y+c.y)/3.0);
}


// --------------------------------
// Triangle helper functions
// --------------------------------

double TriangleArea(const Point &p, const Point &t1, const Point &t2) {
  // compute edge lengths
  double a = distance(p,t1);
  double b = distance(t1,t2);
  double c = distance(t2,p);
  // the half perimeter
  double hp = (a+b+c) / 2.0;
  // using Heron's formula
  return sqrt(hp * (hp-a) * (hp-b) * (hp-c));
}

// returns true if a point is inside the triangle
bool inTriangle(const Point &p, const Triangle &t) {
  double tarea = TriangleArea(t.getPoint(0),t.getPoint(1),t.getPoint(2));
  double a = TriangleArea(p,t.getPoint(0),t.getPoint(1));
  double b = TriangleArea(p,t.getPoint(1),t.getPoint(2));
  double c = TriangleArea(p,t.getPoint(2),t.getPoint(0));
  if (a+b+c > tarea + 0.01) {
    // outside
    return false;
  }
  // inside
  return true;
}

// from https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
int orientation(Point p, Point q, Point r) { 
    int val = (q.y - p.y) * (r.x - q.x) - 
              (q.x - p.x) * (r.y - q.y); 
    if (val == 0) return 0;  // colinear 
    return (val > 0)? 1: 2; // clock or counterclock wise 
} 

// returns true if two line segments intersect (cross)
bool segmentsIntersect(const Point &a1, const Point &a2,  const Point &b1, const Point &b2) {
  int o1 = orientation(a1, a2, b1); 
  int o2 = orientation(a1, a2, b2); 
  int o3 = orientation(b1, b2, a1); 
  int o4 = orientation(b1, b2, a2); 
  // General case 
  if (o1 != o2 && o3 != o4) 
    return true; 
  return false;
}

// returns true if any portion of the triangles overlap
bool intersect(const Triangle &a, const Triangle &b) {
  // it's complicated, but we need to test if any vertex from triangle
  // A is inside triangle B.  And vice versa.
  if (inTriangle(a.getPoint(0),b) ||
      inTriangle(a.getPoint(1),b) ||
      inTriangle(a.getPoint(2),b) ||
      inTriangle(b.getPoint(0),a) ||
      inTriangle(b.getPoint(1),a) ||
      inTriangle(b.getPoint(2),a)) {
    return true;
  }
  // and we *also* need to test if any of the edges cross an edge from
  // the other triangle.  (they can intersect even if a vertex is not
  // contained.)
  if (segmentsIntersect(a.getPoint(0),a.getPoint(1), b.getPoint(0),b.getPoint(1)) ||
      segmentsIntersect(a.getPoint(0),a.getPoint(1), b.getPoint(1),b.getPoint(2)) ||
      segmentsIntersect(a.getPoint(0),a.getPoint(1), b.getPoint(2),b.getPoint(0)) ||
      segmentsIntersect(a.getPoint(1),a.getPoint(2), b.getPoint(0),b.getPoint(1)) ||
      segmentsIntersect(a.getPoint(1),a.getPoint(2), b.getPoint(1),b.getPoint(2)) ||
      segmentsIntersect(a.getPoint(1),a.getPoint(2), b.getPoint(2),b.getPoint(0)) ||
      segmentsIntersect(a.getPoint(2),a.getPoint(0), b.getPoint(0),b.getPoint(1)) ||
      segmentsIntersect(a.getPoint(2),a.getPoint(0), b.getPoint(1),b.getPoint(2)) ||
      segmentsIntersect(a.getPoint(2),a.getPoint(0), b.getPoint(2),b.getPoint(0))) {
    return true;
  }
  return false;
}

// ==================================================================
// Quad constructor

Quad::Quad(const Point &a, const Point &b, const Point &c, const Point &d, const Color &color_) :
  color(color_) , bbox(a,a) {
  pts[0] = a; pts[1] = b; pts[2] = c; pts[3] = d;
  bbox.extend(b);
  bbox.extend(c);
  bbox.extend(d);
  center = Point((a.x+b.x+c.x+d.x)/4.0,
                 (a.y+b.y+c.y+d.y)/4.0);
}

// Quad helper function

// returns true if any portion of the quads overlap
bool intersect(const Quad &a, const Quad &b) {
  // leverage the triangle overlap code!
  Triangle a1(a.getPoint(0),a.getPoint(1),a.getPoint(2),a.getColor());
  Triangle a2(a.getPoint(0),a.getPoint(2),a.getPoint(3),a.getColor());
  Triangle b1(b.getPoint(0),b.getPoint(1),b.getPoint(2),b.getColor());
  Triangle b2(b.getPoint(0),b.getPoint(2),b.getPoint(3),b.getColor());
  if (intersect(a1,b1) ||
      intersect(a1,b2) ||
      intersect(a2,b1) ||
      intersect(a2,b2)) return true;
  return false;  
}

// ==================================================================
// Templated helper function

template <class T>
bool intersect(const std::vector<T> &all, const T &one) {
  for (unsigned int i = 0; i < all.size(); i++) {
    if (intersect(all[i],one)) return true;
  }
  return false;
}

// ==================================================================
