// 
// YOUR FINAL VERSION OF THIS FILE SHOULD NOT INCLUDE ANY EDITS
// TO THIS FILE.
//

#include <cmath>
#include <iomanip>
#include <algorithm>
#include "utils.h"

// ==================================================================
// Point helper functions

std::ostream& operator<< (std::ostream &ostr, const Point &p) {
  ostr << "<"
       << std::setw(5) << std::fixed << std::setprecision(1) << p.x 
       << " "
       << std::setw(5) << std::fixed << std::setprecision(1) << p.y
       << ">";
  return ostr;
}

// calculate the straight-line distance between two points.
double distance(const Point &p1, const Point &p2) {
  double dx = p1.x-p2.x;
  double dy = p1.y-p2.y;
  return sqrt(dx*dx + dy*dy);
}

// ==================================================================
// Color helper functions

// we convert the 0-255 r,g,b color to a hexidecimal string for SVG.
std::string Color::getHexString() const {
  std::stringstream ss;
  ss << std::hex << std::setfill('0')
     << std::setw(2) << r
     << std::setw(2) << g
     << std::setw(2) << b;
  return ss.str();
}

// we can blend two colors
void Color::mix(Color c2,float f) {
  r = r*f + c2.r*(1-f);
  g = g*f + c2.g*(1-f);
  b = b*f + c2.b*(1-f);
}

std::ostream& operator<< (std::ostream &ostr, const Color &c) {
  ostr << "{"
       << std::setw(3) << c.r
       << " "
       << std::setw(3) << c.g
       << " "
       << std::setw(3) << c.b
       << "}";
  return ostr;
}

// ==================================================================
// Bounding Box helper functions

void BoundingBox::extend(const Point &a) {
  min.x = std::min(min.x,a.x);
  min.y = std::min(min.y,a.y);
  max.x = std::max(max.x,a.x);
  max.y = std::max(max.y,a.y);
}

void BoundingBox::extend(const BoundingBox &bbox) {
  extend(bbox.min);
  extend(bbox.max);
}

// return false if these bounding boxes do not overlap at all
bool BoundingBox::overlaps(const BoundingBox &bbox) const {
  if (max.x < bbox.min.x) return false;
  if (max.y < bbox.min.y) return false;
  if (min.x > bbox.max.x) return false;
  if (min.y > bbox.max.y) return false;
  return true;
}

// draws a transparent box representing this region to the SVG
void BoundingBox::render(std::ostream &ostr, const Color &color) const {
  std::string s = color.getHexString();
  ostr << "<polygon points=\" "
       << min.x << "," << min.y << " "
       << min.x << "," << max.y << " "
       << max.x << "," << max.y << " "
       << max.x << "," << min.y << " \""
       << " style=\"fill:#" << s << ";fill-opacity:0.25\" />" << std::endl;
}

std::ostream& operator<<(std::ostream &ostr, const BoundingBox &bb) {
  ostr << "[" << bb.getMin() << " " << bb.getMax() << "]";
  return ostr;
}

// ==================================================================
