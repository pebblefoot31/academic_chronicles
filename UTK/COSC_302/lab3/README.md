# CS302 -- Lab Assignment 3 (80 pts: Spring 2024)

------------------------------------------------------------------------

### Getting motivated

In this lab you will continue sorting the multi-column data from Lab 2 which consisted of a firstname, a lastname, and a phone number. The main difference is that the data will now be stored in double linked list. You will finish the implementation of mergesort from class for explicitly sorting the nodes that hold the data. You will also add a smart pointer based implementation that uses the std::sort() to get the job done.

CS307 students must also implement qsort\_r3() which is a modified of the quicksort() algorithm from Lab 2 that does 3-way partitioning.

------------------------------------------------------------------------

### Lab submission and due date

The due date for Prog3 is 11.59PM Thursday Feb 22, 2024. Submit a tar file that contains Prog3.cpp and Support.h. The submitted code must compile and execute without seg faulting to be graded.

### Assignment details

Get a copy of lab3.tar from Canvas. The file contains Prog3.cpp, which is a skeleton main program that will you expand on, Support.h, which is a header file where most of the code goes, a makefile for creating a Prog3 executable from these two files, an sprog3 solution executable, and two files called repeat1.txt and repeat2.txt which contain test data. You can also use the list\[123\].txt data files from Lab2.

NOTE: You will not be given incremental development guidelines. Work relevant versions of the code out yourself. The goal should be add enough new functionality to move your code forward but not so much that you can't easily debug if/when things go wrong. You only submit the final version.

-   **Prog3.cpp** Modify this file as follows. Add a private integer variable called ID to the data class. Set this variable to the position of the data entry in the input file. Do this by adding a static integer variable with the same name to the overloaded input operator. Increment this variable each time the operator is excuted and assign the value to the data ID member. Update the output operator to print the value of the data ID member (make the field 8 characters wide and right justified). This simple addition will it possible to see whether the data gets sorted in a stable manner or not. See examples below.

    Update the less-than data comparison operator to no longer use the phone number as a tie-breaker. That is, data objects should be compared on a lastname, firstname basis. This will create more cases where input data is considered equal.

    Update the main function to process command line arguments, read input data into a linked list, time and execute the specified sort algorithm, and write the output to a named file. When completed, any one of the following ways of executing Prog3 should be valid:

        unix> ./Prog3 -insertion list.txt
        unix> ./Prog3 -mergesort list.txt
        unix> ./Prog3 -stdsort list.txt

        CS307 students must also support
        unix> ./Prog3 -quicksort list.txt

    The insertion (sort) and mergesort options will apply so named implements to directly reorder nodes of the linked list. The stdsort and quicksort options will apply array-based sorting to a vector that holds smart pointers. This is all to a large extent based on code from the class06\_sorting5\_handout. Read this code several times till you understand how all of it works.

-   **Support.cpp** Modify this file as follows. Copy the sptr and dlist code from the class06\_sorting5\_handout verbatim. Add an overloaded less-than operator to the node class that compares key values. Add a public quicksort(int mode) member function to the dlist class. CS302 code always sets mode equal to 1. CS307 code sets mode equal to 1 for stdsort and 2 for quicksort.

    Implement the dlist::merge() member function as described in HW5.

    Implement the dlist::quicksort() member function based on the *abstract ideas* behind the data2ptr() and ptr2data() functions from the class06\_sorting5\_handout. Determine the number of elements N stored in the sublist considered. Allocate a vector of smart pointers of that size called Ap. Initialize the individual smart pointers to point to the list nodes. Note that this is done differently from data2ptr(). Here, if p = head, then Ap\[0\] = p-&gt;next, and so forth. Apply std::sort() and use the result to reorder the dlist nodes. This is also done differently from ptr2data(). Here, if p = head, then p-&gt;next = Ap\[0\], and so forth. Simple as that (once you figure it out). You may want to draw a picture of what's going on to help visualize the process. Keep in mind that you operate with pointers to dlist nodes, not pointers to addresses of array elements. What you do here is much easier.

-   **Support.cpp** CS307 students are required to also add support for commandline option quicksort which results in dlist::quicksort() applying an algorithm to be called qsort\_r3(). This is a modified version of the quicksort implementation from Lab 2. That algorithm used a randomly chosen pivot to partition data into three sublists, namely, {≤}, pivot, {≥}. The modified algorithm must create and maintain three sublists, namely, {&lt;}, {pivot=}, {&gt;}. Another albeit minor difference is that the recursion is initiated directly by dlist::quicksort(). The is possible since the bounding indices of interest are known (namely, 0 and N-1). See the notes from Class 5 for an abstract description for how to do the 3-way partitioning. As a reminder, pivot valued data are moved to the sublist ends during the partitioning and when done with that, a couple of for-loops move the pivot valued data next to the pivot after it has been placed at the proper location. You will likely struggle a bit until you wrap your head around the data movement, but rest asured that the code changes are minimal. Questions that pertain to the abstract nature of the problem and its solution will be answered but you must write the code on your own. That is, neither the instructor nor the GTA will debug non-functioning code.

------------------------------------------------------------------------

### Example runs based on repeat1.txt

    unix> cat repeat1.txt | head -10

    LEILA CASTILLO          728-119-1606
    KELLIE HOWE             312-444-8860
    WALKER REILLY           802-389-9875
    GERALD SNOW             470-783-7503
    KATE MAYNARD            759-781-1736
    LEMUEL RUSSO            298-116-4751
    INEZ JOHNSTON           371-784-4888
    CELINA TYLER            743-606-7028
    DAPHNE TUCKER           516-451-2466
    MARSHA LIVINGSTON       336-695-5281

    unix> ./Prog3 -insertion repeat1.txt 
    5.9 ms

    unix> cat insertion_repeat1.txt | head -10

    ACEVEDO,GAVIN.......... 356-488-3678       87 ***
    ACEVEDO,GAVIN.......... 356-488-3678      258 ***
    ADKINS,NOREEN.......... 218-589-7364      267
    AGUIRRE,ROLANDO........ 232-480-9863       67 ***
    AGUIRRE,ROLANDO........ 232-480-9863      100 ***
    AGUIRRE,ROLANDO........ 232-480-9863      311 ***
    ALLISON,CHELSEA........ 565-133-4367      185
    ALSTON,ELOY............ 625-705-2549      285 ***
    ALSTON,ELOY............ 625-705-2549      292 ***
    ANTHONY,EDMOND......... 498-558-5625      291

    unix> ./Prog3 -mergesort repeat1.txt 
    0.2 ms

    unix> cat mergesort_repeat1.txt | head -10

    ACEVEDO,GAVIN.......... 356-488-3678       87 ***
    ACEVEDO,GAVIN.......... 356-488-3678      258 ***
    ADKINS,NOREEN.......... 218-589-7364      267
    AGUIRRE,ROLANDO........ 232-480-9863       67 ***
    AGUIRRE,ROLANDO........ 232-480-9863      100 ***
    AGUIRRE,ROLANDO........ 232-480-9863      311 ***
    ALLISON,CHELSEA........ 565-133-4367      185
    ALSTON,ELOY............ 625-705-2549      285 ***
    ALSTON,ELOY............ 625-705-2549      292 ***
    ANTHONY,EDMOND......... 498-558-5625      291

    unix> ./Prog3 -stdsort repeat1.txt 
    0.3 ms

    unix> cat stdsort_repeat1.txt | head -20

    ACEVEDO,GAVIN.......... 356-488-3678       87 ***
    ACEVEDO,GAVIN.......... 356-488-3678      258 ***
    ADKINS,NOREEN.......... 218-589-7364      267
    AGUIRRE,ROLANDO........ 232-480-9863      311 +++
    AGUIRRE,ROLANDO........ 232-480-9863       67 +++
    AGUIRRE,ROLANDO........ 232-480-9863      100 +++
    ALLISON,CHELSEA........ 565-133-4367      185
    ALSTON,ELOY............ 625-705-2549      285 ***
    ALSTON,ELOY............ 625-705-2549      292 ***
    ANTHONY,EDMOND......... 498-558-5625      291
    ASHLEY,ROSALIND........ 381-587-7613      302 +++
    ASHLEY,ROSALIND........ 381-587-7613      176 +++
    ATKINSON,BETHANY....... 475-954-1105       93
    AYALA,DAMON............ 376-528-9382      319 +++
    AYALA,DAMON............ 376-528-9382       82 +++
    AYALA,DAMON............ 376-528-9382       44 +++
    AYALA,DAMON............ 376-528-9382      118 +++
    BAILEY,ROBERTO......... 846-171-8639      159
    BAIRD,LINWOOD.......... 936-892-1659      191 +++
    BAIRD,LINWOOD.......... 936-892-1659       99 +++

    unix> ./Prog3 -quicksort repeat1.txt
    0.8 ms

    unix> cat quicksort_repeat1.txt | head -20

    ACEVEDO,GAVIN.......... 356-488-3678       87 ***
    ACEVEDO,GAVIN.......... 356-488-3678      258 ***
    ADKINS,NOREEN.......... 218-589-7364      267
    AGUIRRE,ROLANDO........ 232-480-9863       67 ***
    AGUIRRE,ROLANDO........ 232-480-9863      100 ***
    AGUIRRE,ROLANDO........ 232-480-9863      311 ***
    ALLISON,CHELSEA........ 565-133-4367      185
    ALSTON,ELOY............ 625-705-2549      285 ***
    ALSTON,ELOY............ 625-705-2549      292 ***
    ANTHONY,EDMOND......... 498-558-5625      291
    ASHLEY,ROSALIND........ 381-587-7613      302 +++
    ASHLEY,ROSALIND........ 381-587-7613      176 +++
    ATKINSON,BETHANY....... 475-954-1105       93
    AYALA,DAMON............ 376-528-9382      319 +++
    AYALA,DAMON............ 376-528-9382      118 +++
    AYALA,DAMON............ 376-528-9382       44 +++
    AYALA,DAMON............ 376-528-9382       82 +++
    BAILEY,ROBERTO......... 846-171-8639      159
    BAIRD,LINWOOD.......... 936-892-1659       28 ***
    BAIRD,LINWOOD.......... 936-892-1659       99 ***

The entries marked with an asterisk are equal entries for which the input order is preserved. The entries marked with a plus sign are equal entries for which the input order is not preverbed. Note that insertion sort and mergesort maintain the order while stdsort and quicksort sometimes do and sometimes don't. Also note that the latter two sometimes produce a different sort order for equal data since they partition the data differently. Finally, as always, compare your output against the solution executable. Your computer may use a different random number generator from the one used to produce the above.

------------------------------------------------------------------------

### Grading rubric

Note: Output format of your program MUST MATCH the solution executable. Use the diff command to compare.  
CS302 students can earn extra credit for the qsort\_r3 code CS307 students must complete for full credit.

#### Prog3 (80)

    20: Prog3.cpp: data ID, input and output operators, main() functionality.
    20: Option mergesort: merge() function.
    20: Option stdsort: smart pointer and std::sort() implementation.
    20: Correct output for all four sorting algorithms.

    CS307 (Points are deducted if option not implemented (correctly))
    20: Option quicksort: 3-way quicksort using randomly chosen pivot.

------------------------------------------------------------------------

Tue Feb 13 12:52:12 EST 2024
