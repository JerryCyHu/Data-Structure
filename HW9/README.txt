HOMEWORK 9:  PRIORITY QUEUES FOR MESH SIMPLIFICATION


NAME:  < Jerry Hu >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Piao Weiyi >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 8h >


ALGORITHM ANALYSIS: 

Assume v_0 vertices, e_0 edges, and t_0 triangles in the initial mesh,
k edges connected to each vertex (average or worst case),
reduced to t_final triangles using the -shortest criteria.

What is the overall order notation for the program?  Analyze the
separate compoenents of the program to justify your answer.

ALGORITHM ANALYSIS -- LINEAR:
Suppliment notations:
h:height of image
w:width of image
r:rows
c:colomns
O(r*c(log(t_0)+log(e_0)+k^2)+w*h)+(t_0-t_final)*[k*(log(k)+log(t_0))*(log(t_0)+log(e_0)+k^2)])
I think this is already the most concise and simplified version



ALGORITHM ANALYSIS -- PRIORITY QUEUE:
Suppliment notations:
h:height of image
w:width of image
r:rows
c:colomns
O(r*c(log(t_0)+log(e_0)+k^2)+w*h)+(t_0-t_final)*[k*(log(k)+log(t_0))*(log(t_0)+k^2)])
Again, I think this is already the most concise and simplifies version


ALGORITHM ANALYSIS -- IMPACT OF -preserve_area command line argument?
Do your answers above change with or without the -preserve_area
command line argument?  Describe.






EXTRA CREDIT:  COLOR & OVERALL APPERANCE
Discuss the quality of your results in your README.txt and include
screenshots of your more impressive results.  If you have submitted
screenshots, give the file names and describe the results.



MISC. COMMENTS TO GRADER:  
Optional, please be concise!






