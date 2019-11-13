// 
// The contents of this file are provided to help rendering and
// visualizing your BVH.  And for analyzing and formatting the
// statistics of your BVH.  
// 
// Your final version of this file (renamed to bvh.h) must include the
// full implementation of the BVH class and closely-related classes.
//
// You may make small edits within the body of these functions as
// necessary to work with the rest of your implementation.  But do not
// change the public prototypes (function names or arguments).
//
//

{


  /* NOTE: inside the BVH class declaration */
  

  // (public) user functions to gather statistics & print the tree visualization
  void statistics(bool print_tree) const;
  void render_recolor(std::ostream &ostr) { render_recolor(ostr,root,Color(128,128,128)); }



  // (private) helper functions
  void statistics(bool print_tree, Node* n, const std::string &indent,
                  int &node_count, int &max_depth,
                  double &inner_node_area, double &leaf_node_area) const;
  void render_recolor(std::ostream &ostr, Node *n, const Color &color);


}



// =============================================================================
// helper functions for statistics & printing


// This function walks over all nodes of the tree collecting
// information about the count, type (inner or leaf), and area of
// nodes in the tree.

template <class T>
void BVH<T>::statistics(bool print_tree) const {

  // node count & maximum depth can be used to partially evaluate if
  // the tree is mostly well-balanced.
  int node_count = 0;
  int max_depth = 0;

  //
  // Bittner, Hapala, & Havran, "Incremental BVH construction for ray
  // tracing". Computers & Graphics 2014.
  //
  // summarize the "surface area heuristic" for predicting the
  // efficiency of a bounding volume hierarchy.
  //
  // We calculate the sum of the (surface) area of all inner
  // (non-leaf) nodes and divide by the area of the entire scene.  It
  // is generally better for the inner nodes to have small surface
  // area -- which indicates the hierarchy is small and efficient, and
  // we can quickly navigate to the relevant leaf nodes.
  //
  double inner_node_area = 0;

  // We also calculate the sum of the leaf node surface area (again
  // divided by the scene area).  The leaf node area is multiplied
  // (penalized) by the number of elements at that leaf node.  We hope
  // this number is also small.
  //
  double leaf_node_area = 0;

  
  // sweep over the tree and print the results
  statistics(print_tree,root,"",node_count, max_depth, inner_node_area, leaf_node_area);
  std::cout << "node count:      " << std::setw(7) << node_count << std::endl;
  std::cout << "max depth:       " << std::setw(7) << max_depth << std::endl;
  std::cout << "inner node area: " << std::fixed << std::setw(7) << std::setprecision(3) << inner_node_area << std::endl;
  std::cout << "leaf node area:  " << std::fixed << std::setw(7) << std::setprecision(3) << leaf_node_area << std::endl;
}


// The core recursive function to collect the statistics above.  If
// the print_tree bool is enabled, we will also print data about the
// tree for debugging and autograding.
template <class T>
void BVH<T>::statistics(bool print_tree,
                        Node* n,
                        const std::string &indent,
                        int &node_count,
                        int &max_depth,
                        double &inner_node_area,
                        double &leaf_node_area) const {

  node_count++;
  max_depth = std::max(n->depth,max_depth);
  // scale the area by the area of the scene
  double area = n->bbox.getArea() / double(1000*1000);
  if (n->data.size() != 0) {
    leaf_node_area += n->data.size() * area;
    if (print_tree) {
      std::cout << indent + "leaf area=" << std::setprecision(3) << area << " " << n->bbox << " elements:";
      for (unsigned int i = 0; i < n->data.size(); i++) {
        std::cout << " " << n->data[i].getBox();
      }
      std::cout << std::endl;
    }
  } else {
    inner_node_area += area;
    if (print_tree) {
      std::cout << indent + "inner area=" << std::setprecision(3) << area << " " << n->bbox << std::endl;
    }
    statistics(print_tree,n->children[0],indent+"   ",node_count,max_depth,inner_node_area,leaf_node_area);
    statistics(print_tree,n->children[1],indent+"   ",node_count,max_depth,inner_node_area,leaf_node_area);
    statistics(print_tree,n->children[2],indent+"   ",node_count,max_depth,inner_node_area,leaf_node_area);
  }
}

// =============================================================================
// helper functions for rendering


template <class T>
void BVH<T>::render_recolor(std::ostream &ostr, Node *n, const Color &color) {

  // draw the bounding box of this node as a transparent colored rectangle
  n->bbox.render(ostr,color);

  if (n->children[0] != NULL) {

    // prepare variations of this node color for the 3 children
    Color red(255,0,0);
    Color green(0,255,0);
    Color blue(0,0,255);
    // blend the colors
    if (color.r != 128 && color.g != 128 && color.b != 128) {
      float m = 0.33;
      red.mix(color,m);
      green.mix(color,m);
      blue.mix(color,m);
    }

    // recurse to the children
    render_recolor(ostr,n->children[0],red);
    render_recolor(ostr,n->children[1],green);
    render_recolor(ostr,n->children[2],blue);

  } else {

    // if this is a leaf node, modify the color of all elements to
    // match the transparent box color.
    for (unsigned int i = 0; i < n->data.size(); i++) {
      n->data[i].setColor(color);
    }
  }
}

// =============================================================================
