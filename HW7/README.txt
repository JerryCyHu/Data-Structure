HOMEWORK 7: LIBRARY MAPS


NAME:  < Jerry Hu >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< None >

Remember: Your implementation for this assignment must be done on your
own, as described in the “Collaboration Policy & Academic Integrity”
handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 20 mins >



ORDER NOTATION ANALYSIS: 
Give the big O notation of each of the library operations and justify
your answer.  Let n be the number of different titles in the library,
m be the maximum number of copies of a given item, p be the number of
patrons using the library, and c be the maximum number of items any
patron has checked out at one time.  (Please be concise!)


add (a):
O(1);

checkout (c):
O(c)


return (r):
worst case: O(c*p);
optimistic: O(c);


lookup (l):
worst: O(p);
optimistic: O(1);

print (p):
O(p);



YOUR OWN TEST CASES:
describe each test case you created and your motivation for designing
each (why is the test case helpful for debugging and/or interesting)

For the first one, I put some corner cases inside the input file such as adding 0 book into the library to see if the program can work properly.

For the second one, I just mixed all test cases into one really big test cases to see if it can run properly.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


