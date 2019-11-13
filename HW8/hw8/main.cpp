// 
// YOUR FINAL VERSION OF THIS FILE SHOULD NOT INCLUDE ANY EDITS,
// EXCEPT TO ADD YOUR OWN TESTS WHERE INDICATED
//

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cmath>

#include "utils.h"
#include "shapes.h"
#include "bvh.h"

void AdditionalStudentTests();

// ==============================================================================
// ==============================================================================
// Template specializations to load the different object types

void load(std::istream &istr, std::vector<Disk> &disks) {
    std::string token;
    char open,close;
    float x,y,radius;
    int r,g,b;
    while (istr >> token >> open >> x >> y >> close) {
        assert (token == "pt=");
        assert (open == '<');
        assert (close == '>');
        istr >> token >> radius;
        assert (token == "radius=");
        istr >> token >> open >> r >> g >> b >> close;
        assert (token == "color=");
        assert (open == '{');
        assert (close == '}');
        Disk d(Point(x,y),radius,Color(r,g,b));
        disks.push_back(d);
    }
}

void load(std::istream &istr, std::vector<Triangle> &triangles) {
    std::string token;
    char open,close;
    float ax,ay,bx,by,cx,cy;
    int r,g,b;
    while (istr >> token >> open >> ax >> ay >> close) {
        assert (token == "pt=");
        assert (open == '<');
        assert (close == '>');
        istr >> token >> open >> bx >> by >> close;
        assert (token == "pt=");
        assert (open == '<');
        assert (close == '>');
        istr >> token >> open >> cx >> cy >> close;
        assert (token == "pt=");
        assert (open == '<');
        assert (close == '>');
        istr >> token >> open >> r >> g >> b >> close;
        assert (token == "color=");
        assert (open == '{');
        assert (close == '}');
        Triangle t(Point(ax,ay),Point(bx,by),Point(cx,cy),Color(r,g,b));
        triangles.push_back(t);
    }
}

void load(std::istream &istr, std::vector<Quad> &quads) {
    std::string token;
    char open,close;
    float ax,ay,bx,by,cx,cy,dx,dy;
    int r,g,b;
    while (istr >> token >> open >> ax >> ay >> close) {
        assert (token == "pt=");
        assert (open == '<');
        assert (close == '>');
        istr >> token >> open >> bx >> by >> close;
        assert (token == "pt=");
        assert (open == '<');
        assert (close == '>');
        istr >> token >> open >> cx >> cy >> close;
        assert (token == "pt=");
        assert (open == '<');
        assert (close == '>');
        istr >> token >> open >> dx >> dy >> close;
        assert (token == "pt=");
        assert (open == '<');
        assert (close == '>');
        istr >> token >> open >> r >> g >> b >> close;
        assert (token == "color=");
        assert (open == '{');
        assert (close == '}');
        Quad q(Point(ax,ay),Point(bx,by),Point(cx,cy),Point(dx,dy),Color(r,g,b));
        quads.push_back(q);
    }
}

// ==============================================================================
// ==============================================================================
// Render the geometry as an SVG (Scalable Vector Graphics)
// File & graphics can be viewed in most web browsers

// misc header information including dimensions
void render_start(std::ostream &ostr) {
    ostr << "<?xml version=\"1.0\" standalone=\"no\"?>" << std::endl;
    ostr << "<svg width=\"1000\" height=\"1000\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">" << std::endl;
}


// Template specializations to render the different element types.
// Note that we use the BVH iterator to visit all of the elements
// stored in the container!

void render_elements(std::ostream &ostr, const BVH<Disk> &bvh) {
    for (BVH<Disk>::iterator itr = bvh.begin(); itr != bvh.end(); itr++) {
        const Disk &d = *itr;
        std::string s = d.getColor().getHexString();
        ostr << "<circle cx = \"" << d.getPoint(0).x << "\" cy = \"" << d.getPoint(0).y << "\" r = \"" << d.getRadius() << "\""
             << " style=\"fill:#" << s << "\" />" << std::endl;
    }
}

void render_elements(std::ostream &ostr, const BVH<Triangle> &bvh) {
    for (BVH<Triangle>::iterator itr = bvh.begin(); itr != bvh.end(); itr++) {
        const Triangle &t = *itr;
        std::string s = t.getColor().getHexString();
        ostr << "<polygon points=\" "
             << t.getPoint(0).x << "," << t.getPoint(0).y << " "
             << t.getPoint(1).x << "," << t.getPoint(1).y << " "
             << t.getPoint(2).x << "," << t.getPoint(2).y << " \""
             << " style=\"fill:#" << s << "\" />" << std::endl;
    }
}

void render_elements(std::ostream &ostr, const BVH<Quad> &bvh) {
    for (BVH<Quad>::iterator itr = bvh.begin(); itr != bvh.end(); itr++) {
        const Quad &t = *itr;
        std::string s = t.getColor().getHexString();
        ostr << "<polygon points=\" "
             << t.getPoint(0).x << "," << t.getPoint(0).y << " "
             << t.getPoint(1).x << "," << t.getPoint(1).y << " "
             << t.getPoint(2).x << "," << t.getPoint(2).y << " "
             << t.getPoint(3).x << "," << t.getPoint(3).y << " \""
             << " style=\"fill:#" << s << "\" />" << std::endl;
    }
}


// misc footer information, including a simple black outline for the scene
void render_end(std::ostream &ostr) {
    ostr << "<line x1=\"   1.0\" y1=\"   1.0\" x2=\" 999.0\" y2=\"   1.0\" stroke=\"black\" stroke-width=\"3\" />" << std::endl;
    ostr << "<line x1=\" 999.0\" y1=\"   1.0\" x2=\" 999.0\" y2=\" 999.0\" stroke=\"black\" stroke-width=\"3\" />" << std::endl;
    ostr << "<line x1=\" 999.0\" y1=\" 999.0\" x2=\"   1.0\" y2=\" 999.0\" stroke=\"black\" stroke-width=\"3\" />" << std::endl;
    ostr << "<line x1=\"   1.0\" y1=\" 999.0\" x2=\"   1.0\" y2=\"   1.0\" stroke=\"black\" stroke-width=\"3\" />" << std::endl;
    ostr << "</svg>" << std::endl;
}

// ==============================================================================
// ==============================================================================
// The core workflow of the program 

template <class T>
void ProcessAndVisualize(const std::vector<T> &elements,
                         std::ostream &ostr,
                         int split_threshold,
                         int depth_limit,
                         bool incremental,
                         bool discard_overlap,
                         bool print_tree,
                         bool visualize) {

    // header information for the SVG
    render_start(ostr);

    // create an empty bounding volume hierarchy
    BVH<T> bvh(split_threshold,depth_limit);

    if (!incremental) {

        // Give the BVH all of the elements at once.  Because the BVH can
        // sort and thoughtfully separate the data into groups with equal
        // count, this should yield a well-balanced tree.
        bvh.construct(elements);

    } else {

        // Simulate building the BVH incrementally, one randomly placed
        // element at a time.
        for (unsigned int i = 0; i < elements.size(); i++) {
            if (discard_overlap && bvh.collision(elements[i])) continue;
            bvh.insert(elements[i]);
        }
    }

    if (depth_limit > 0) {
        // If requested, print the full tree details (for debugging and grading).
        bvh.statistics(print_tree);
    }
    if (visualize) {
        // If requested, transparently render the bounding boxes for Nodes
        // of the tree.  And recolor the elements to match their bounding
        // box.
        bvh.render_recolor(ostr);
    }
    // Render the elements
    render_elements(ostr,bvh);

    // footer information for the SVG
    render_end(ostr);
}


// ==============================================================================
// ==============================================================================

int main(int argc, char *argv[]) {

    // ======================================
    // DEFAULT ARGUMENT VALUES
    int split_threshold = 4;
    int depth_limit = 0;
    bool incremental = false;
    bool discard_overlap = false;
    bool visualize = false;
    bool print_tree = false;
    std::string input_file = "";
    std::string output_file = "";
    bool run_student_tests = false;


    // ======================================
    // PARSE ARGUMENTS
    for (int i = 1; i < argc; i++) {
        if (argv[i] == std::string("--split_threshold")) {
            i++;
            assert (i < argc);
            split_threshold = std::stoi(argv[i]);
            assert (split_threshold >= 1);
        } else if (argv[i] == std::string("--depth_limit")) {
            i++;
            assert (i < argc);
            depth_limit = std::stoi(argv[i]);
            assert (depth_limit >= 1);
        } else if (argv[i] == std::string("--incremental")) {
            incremental = true;
        } else if (argv[i] == std::string("--discard_overlap")) {
            assert (incremental == true);
            discard_overlap = true;
        } else if (argv[i] == std::string("--visualize")) {
            visualize = true;
        } else if (argv[i] == std::string("--print_tree")) {
            print_tree = true;
        } else if (argv[i] == std::string("--run_student_tests")) {
            run_student_tests = true;
        } else if (argv[i] == std::string("-i") || argv[i] == std::string("--input")) {
            i++;
            assert (i < argc);
            input_file = argv[i];
        } else if (argv[i] == std::string("-o") || argv[i] == std::string("--output")) {
            i++;
            assert (i < argc);
            output_file = argv[i];
        } else {
            std::cout << "ERROR: UNKNOWN ARGUMENT '" << argv[i] << "'" << std::endl;
            exit(1);
        }
    }


    if (run_student_tests) {
        std::cout << "\nGoing to start additional student tests... \n" << std::endl;
        AdditionalStudentTests();
        std::cout << "\nStudent tests complete\n" << std::endl;
    }

    else {

        // ======================================
        // ERROR CHECKING ON THE INPUT FILE
        assert (input_file != "");
        bool disks = false;
        bool triangles = false;
        bool quads = false;
        // determine the templated element type by the file suffix
        if (input_file.size() > 6 && input_file.substr(input_file.size()-6) == ".disks") {
            disks = true;
        } else if (input_file.size() > 10 && input_file.substr(input_file.size()-10) == ".triangles") {
            triangles = true;
        } else if (input_file.size() > 6 && input_file.substr(input_file.size()-6) == ".quads") {
            quads = true;
        } else {
            std::cout << "ERROR: unknown input file type " << input_file << std::endl;
        }
        std::ifstream istr(input_file);
        assert (istr.good());


        // ======================================
        // ERROR CHECKING ON THE OUTPUT FILE
        assert (output_file != "");
        assert (output_file.substr(output_file.size()-5) == ".html");
        std::ofstream ostr(output_file);
        assert (ostr.good());


        // Based on the templated type, launch the core program logic for
        // for creating & using the BVH.
        if (disks) {
            std::vector<Disk> disks;
            load(istr,disks);
            ProcessAndVisualize(disks,ostr,split_threshold,depth_limit,incremental,discard_overlap,print_tree,visualize);
        } else if (triangles) {
            std::vector<Triangle> triangles;
            load(istr,triangles);
            ProcessAndVisualize(triangles,ostr,split_threshold,depth_limit,incremental,discard_overlap,print_tree,visualize);
        } else if (quads) {
            std::vector<Quad> quads;
            load(istr,quads);
            ProcessAndVisualize(quads,ostr,split_threshold,depth_limit,incremental,discard_overlap,print_tree,visualize);
        }
    }
}

// ==============================================================================
// ==============================================================================

void AdditionalStudentTests() {

  //
  // Complete this function 
  //
  //   Add additional tests of the BVH class including:
  //   * copy constructor
  //   * assignment operator
  //   * pre- & post- increment & decrement
  BVH<Disk> b1 = BVH<Disk>(2,2);
  Disk a = Disk(Point(12,13), 6, Color(12,21,12));
  b1.insert(a);
  BVH<Disk> b2 = BVH<Disk>(b1);
  assert((*b2.begin()).getCenter().x == (*b1.begin()).getCenter().x);
  assert((*b2.begin()).getCenter().y == (*b1.begin()).getCenter().y);
  cout<<"copy constructor complete\n";
  BVH<Disk> b3 = BVH<Disk>(4,2);
  Disk b = Disk(Point(13,33), 6, Color(12,21,12));
  b3.insert(b);
  b3 = b2;
  assert((*b3.begin()).getCenter().x == (*b1.begin()).getCenter().x);
  assert((*b3.begin()).getCenter().y == (*b1.begin()).getCenter().y);
  cout<<"assinment operator complete\n";
  int x = 3;
  int y = 3;

    for (int j = 0; j < 20; ++j) {
        x++;
        y++;
        Disk c = Disk(Point(x,y), 6, Color(12,21,12));
        b3.insert(c);
    }
    BVH<Disk> :: iterator itr = b3.begin();
    for (int j = 0; j < 20; ++j) {
        itr++;
    }
    for (itr; itr!=b3.begin();) {
        itr--;
    }
    assert((*itr).getCenter().x == 4);
    assert((*itr).getCenter().y == 4);
    cout<<"pre- & post- increment & decrement complete\n";
  //
  //   For extra credit:
  //   * explore and evaluate alternate methods of constructing or 
  //     inserting data to a BVH.
  //   * implementation, testing, and performance evaluation of the 
  //     erase function.
  //

}

// ==============================================================================
