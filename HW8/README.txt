HOMEWORK 8: BOUNDING VOLUME HIERARCHY


NAME:  < Jerry Hu >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Zi Xiang >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < ∞ >



CORRECTNESS & PERFORMANCE ANALYSIS:
Summarize the performance of your implementation on a variety of
different input files and command line arguments.  Describe what you
seee visually in SVG file.  How is the running time (use the unix
'time' command) of your program for detecting and omitting elements
that overlap with previously inserted data?  Compare your measurements
to the gathereed statistics.  Does it match your expectations?
0m4.328s for ./bvh.out -i overlap_100000.disks -o discard_overlap_100000_disks.html --depth_limit 8 --incremental --discard_overla
0m1.781s for ./bvh.out -i overlap_100000.disks -o overlap_100000_disks.html
around 0m0.001s for the rest.

It matches my expectations.



EXTRA CREDIT: BVH CONSTRUCTION HEURISTICS
Explore and evaluate alternate methods of constructing or
incrementally inserting data to a BVH.
1.call construct in insert: This is the slowest since we need to destruct it and construct it every time when we insert. It will take about 10 minutes to excute 100000 shapes
2.call construct when the tree needs to increase the depth. For the rest of time just insert shapes to the leaf node. This is much faster than the first. It will take about 4 seconds to execute 100000 shapes.



EXTRA CREDIT: ERASE
Discuss the implications of implementing and using erase on a BVH.
How does it compare to erase on a standard binary search tree?
Optionally, implement, test, and evaluate the performace of this
operation.

BVH is just the three-child-node version of a Binary search tree. The performence of erase has the worse case: O(log3(N)).
The implication should be recursive. Just like insert but in a reverse way.


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


