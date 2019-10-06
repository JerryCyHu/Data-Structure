HOMEWORK 4: DEBUGGING & GROCERY LISTS

NAME:  < Jerry Hu >


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < insert # hours >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(TAs, ALAC tutors, upperclassmen, students/instructor via LMS,
etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< DiYuan Zhu >


Remember: All finding and fixing bugs for this assignment must be done
on your own, as described in "Academic Integrity for Homework"
handout.  You may not discuss the bugs in this assignment with other
students in the course.



PART 2 ORDER NOTATION:
For each request/command,

i = # of different ingredients in the kitchen
u = maximum units of a single ingredient in the kitchen
r = # of different recipes
k = maximum # of different ingredients in a single recipe
v = maximum units of single ingredient in a single recipe
a = maximum # of different ingredients added with a single ’a’ command 
w = maximum units of a single ingredient added with a single ’a’ command


command 'r' / add a recipe: O(k)

command 'a' / add ingredients to the kitchen: O(a)

command 'p' / print a recipe: O(r*k)

command 'm' / make a recipe: O(i*r*k)

command 'k' / print the contents of the kitchen: O(i)



MISC. COMMENTS TO GRADER:
Optional, please be concise!
