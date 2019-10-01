#include <iostream>
#include "Rectangle.h"


bool Rectangle::is_point_within(const Point2D& p) const {
  return
    (p.x() <= m_upper_right.x() && p.y() <= m_upper_right.y()) ||
    (p.x() >= m_lower_left.x() && p.y() >= m_lower_left.y());
}

bool Rectangle::add_point(const Point2D& p) {
	if (p.x()>m_lower_left.x()&&p.x()<m_upper_right.x()&&p.y()>m_lower_left.y()&&p.y()<m_upper_right.y())
	{
		m_points_contained.push_back(p);
		return true;
	}
	else
	{
		return false;
	}
}


std::vector<Point2D> points_in_both(const Rectangle& r1, const Rectangle& r2) {
  //  Use a reference/alias to access the vector of points in the two
  //  rectangles ** without copying ** these vectors.  Instead,
  //  r1_points and r2_points are references to the vectors of points,
  //  but since they are constants neither the vectors nor the points
  //  within them can be changed.
  const std::vector<Point2D> & r1_points = r1.points_contained();
  const std::vector<Point2D> & r2_points = r2.points_contained();
  std::vector<Point2D> pInBoth;
  for (const Point2D & p1 : r1_points) {
	  for (const Point2D & p2 : r2_points)
	  {
		  if (p1.x() == p2.x() && p1.y() == p2.y())
		  {
			  pInBoth.push_back(p1);
		  }
	  }
  }

  return pInBoth;
  // finish this implementation
  
  // Create and return a vector that contains only the points inside
  // of BOTH rectangles.  Don't include points that are only inside of
  // 1 rectangle.

   }


void print_rectangle(const Rectangle& r1) {

  // get all the points that are inside the rectangle
  const std::vector<Point2D> & r1_points = r1.points_contained();
  
  // print the rectangle coordinates
  std::cout << "Rectangle: " 
            << r1.lower_left_corner().x() << "," << r1.lower_left_corner().y() << "--"
            << r1.upper_right_corner().x() << "," << r1.upper_right_corner().y() << std::endl;
  
  // print points that are inside
  std::cout << "Points inside:" << std::endl;
  for( std::vector<Point2D>::size_type i = 0; i < r1_points.size(); ++i ) {
    std::cout << r1_points[i].x() << "," << r1_points[i].y() << std::endl;
  }
}


