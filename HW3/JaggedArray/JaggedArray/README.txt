HOMEWORK 3: JAGGED ARRAY


NAME:  < Jagged Array >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

<Zhu Diyuan, Zixiang>

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < insert # hours >



ORDER NOTATION:
For each function, for each version (packed vs. unpacked).  
b = the number of bins
e = the number of elements
k = the number of elements in the largest bin

numElements
 unpacked:1
 packed:1

numBins
 unpacked:1
 packed:1

numElementsInBin
 unpacked:1
 packed:1

getElement
 unpacked:1
 packed:b

isPacked
 unpacked:1
 packed:1

clear
 unpacked:b*k
 packed:1

addElement
 unpacked:k
 packed:1

removeElement
 unpacked:k
 packed:1

pack
 unpacked:e+b*k
 packed:1

unpack
 unpacked:1
 packed:b*k+e

print 
 unpacked:b*k
 packed:e

constructor w/ integer argument
 unpacked:b
 packed:N/A

copy constructor
 unpacked:b*k
 packed:b

destructor
 unpacked:b*k
 packed:e

assignment operator
 unpacked:b*k
 packed:b




MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


