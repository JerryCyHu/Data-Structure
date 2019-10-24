HOMEWORK 6: BRIDGES RECURSION


NAME:  < Jerry Hu >



COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Zi Xiang >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 30h >



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)
The dimensions of the board (w and h) 
The number of colored path endpoints (c)?
The number of bridges (b)?
The length of the longest path in the solution (e)?
Etc. 
The dimensions of the board will not effect the execution time very much.
The more bridge there are, the quicker the program will run, because when it is bridge, the program only needs to go straight.
The length of the longest path will also not going to effect the execution time very much.
The number of colored path endpoints will effect the program very much. The more endpoints there are, the longer time will it take the program to execute.
O(e^c+(w^2+h^2)*c)->O(e^c)
The big O is going to be O(e^c)



SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES:
# of solutions & approximate wall clock running time for different
puzzles and different command line arguments.
In general, puzzle_8 is the most time consuming and computing expensive since it has the most colors.
--All_solutions --covers_board is the most time consuming and computing expensive arguments.




MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


