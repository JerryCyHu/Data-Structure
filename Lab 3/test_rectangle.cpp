#include <iostream>
#include "Rectangle.h"
#include "Point2D.h"
using namespace std;

int main() {
	Point2D p1REC1(1, 1);
	Point2D p2REC1(4, 6);
	Rectangle rec1(p1REC1, p2REC1);
	
	Point2D p1REC2(2, 3);
	Point2D p2REC2(6, 8);
	Rectangle rec2(p1REC2, p2REC2);
	Point2D p1(2, 4);
	if (rec1.add_point(p1)) {
		cout << "Complete";
	}
	else
	{
		cout << "invalid";
	}
	if (rec2.add_point(p1)) {
		cout << "Complete";
	}
	else
	{
		cout << "invalid";
	}
	print_rectangle(rec1);
	points_in_both(rec1, rec2);

}