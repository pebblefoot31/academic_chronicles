# CS302 -- Lab Assignment 2 (80 pts: Spring 2024)

------------------------------------------------------------------------

### Getting motivated

Another week, another sorting assignment. In this lab, you will first define a class for storing multi-column data consisting of a firstname, a lastname, and a phone number (all made up, but you knew that), read an unspecified amounts of such data from a given file and apply the std::sort algorithm before printing the result to stdout. Then the real work begins by you implementing a variant of the quicksort algorithm described in class that in its basic form replaces std::sort and in a more advanced version uses the quickselect algorithm to first partition the data for a given range before sorting it.

Read the assignment a couple of times. Look at the output examples. Run the solution code to become familiar with its behavior. Ask questions on Piazza so the whole class can benefit if something is confusing. Chances are you are not alone. Do this for every lab assignment.

------------------------------------------------------------------------

### Lab submission and due date

The due date for Prog2 is 11.59PM Tuesday Feb 13, 2024. Submit a tar file that contains Prog2.cpp and Support.h. The submitted code must compile and execute without seg faulting to be graded.

### Assignment details

Get a copy of lab2.tar from Canvas. The file contains Prog2.cpp, which is a skeleton main program that will you expand on, Support.h, which is a near-empty header file where the template based sorting code goes, a makefile for creating a Prog2 executable from these two files, an sprog2 solution executable, and three files called list1.txt, list2.txt and list3.txt which contain test data.

NOTE: The incremental development described next is merely intended to make solving the problem more manageable. You only submit the final version.

-   **Vers 1** Modify Prog2.cpp as follows. The data class has three private data members: firstname, lastname, and phonenumber. Write the code for the overloaded operator&lt; as well as the input and output operators.

    -   Objects that have the same lastname should use the firstnames to determine which is less than the other. Objects that also have the same firstnames should use the phone numbers to determine which is less than the other. Treat all data as character strings.
    -   The list.txt files contain FIRSTNAME LASTNAME PHONENUMBER data. The input operator reads (extracts) these three strings from an input stream and assigns them to the appropriate data object members when called. The output operator prints the data object members to an output stream using the modified format: LASTNAME,FIRSTNAME... PHONENUMBER. See actual examples below. The name field should be rightfilled with dots to create a fixed width of 23 characters so that all phone numbers are left justified to the same column position. The name and phone number fields are separated by a single blank space.

    Do what is needed to make the program read data from stdin, sort it using the std::sort algorithm, and write the result to stdout. Run tests to make sure the three operators work as intended.

-   **Vers 2** Add command line argument handling. When completed, any one of the following three ways of executing Prog2 should be valid:

        unix> ./Prog2 -stdsort list.txt
        unix> ./Prog2 -qsort list.txt
        unix> ./Prog2 -qsort k0 k1 list.txt

    The first version executes the Vers 1 code. The second version sorts the data using your own implementation of quicksort. The third version partitions the input data using quickselect before applying quicksort to sort the data in the range given by integers k0 and k1. Without checking, assume that k0 is less than k1. Do check if k0 is less than 0, in which case it should silently be changed to 0. Likewise, check if k1 is greater than or equal to the number of elements in the data array, say N, and if so, silently change it to N-1. All versions read data from list.txt. The stdsort mode writes to a file called stdsort\_list.txt. The qsort mode writes to a file called qsort\_list.txt while the qsort k0 k1 mode writes to a file called qselect\_list.txt. Update your code from Vers 1 to operate accordingly. Use std::sort for all three modes to test this all works before you continue.

-   **Vers 3** Replace the calls to std::sort for the two qsort modes with a call to your own implementation of quicksort. Update support.h to contain the partition and quicksort functions from the class04\_sorting\_3 handout. Embed the partition code within the quicksort function, then change the pivot selection to use a randomly chosen index in the left-to-right range. Update the code to allow for this change in pivot. For example, you may need to explicitly check and prevent going out-bounds during the search for data pairs to swap. You may NOT change how the partitioning works in principle. That is, the randomly chosen pivot MUST initially be moved to the right, and the search for out-of-order data MUST proceed as before with two while-loops that scan from left-to-right and right-to-left. Have the main function set 302 as the seed value (see srand()). Test that the modified quicksort code works before you continue.

-   **Vers 4** Copy the quickselect() function from the class04\_sorting\_3 handout. Embed the random pivot partition code that you created for quicksort() above. Change the function to take four arguments, namely, quickselect(A, left, k, right) where A is the data array, left and right designate the first and the last indices to consider (the range), and is k the element that needs to be selected (found and put in its proper place). Make whatever other modifications are needed to get the code to compile.

    Use quickselect(A, 0, k0, N-1) to put the k0-th element in its proper location and partition the data in A accordingly. That is, ensure that all data stored to the left of A\[k0\] is lexicographically less than or equal to it. All data stored to the right of A\[k0\] must likewise be greater than or equal to it.

    Use quickselect(A, k0, k1, N-1) to put the k1-th element in its proper location and partition the data in A accordingly. Note that data indexed below k0 is ignored at this point.

    Use quicksort(A, k0, k1) to sort the data in the k0 thru k1 index range.

    This completes the assignment. Submit Prog2.cpp and Support.h after you have cleaned the code up and added a few comments.

------------------------------------------------------------------------

### Data and executable output examples

    unix> cat -n list1.txt

         1  EMILIO NGUYEN           479-272-4704
         2  APRIL JUAREZ            797-884-7359
         3  MAY WHITE               377-478-2317
         4  ZACHERY PIERCE          372-775-2096
         5  MAY WHITE               292-698-2214
         6  TERRA ROY               954-377-4587
         7  MARQUITA HAMILTON       427-596-7490
         8  LENARD ORR              948-836-8442
         9  WENDY DOWNS             973-843-8182
        10  ROSA MCNEIL             371-600-6252
        11  REGGIE SNIDER           292-618-9887
        12  ANDREA JOYCE            973-301-1325
        13  RUBY ROY                920-777-5449
        14  CLEVELAND PIERCE        620-966-4334
        15  DOLORES SNIDER          945-847-4679
        16  DELLA DORSEY            619-905-1761
        17  DEBORA NGUYEN           768-170-8249
        18  MARILYN GRAY            734-182-9137

    unix> ./Prog2 -stdsort list1.txt 
    unix> cat -n stdsort_list1.txt 

         1  DORSEY,DELLA........... 619-905-1761
         2  DOWNS,WENDY............ 973-843-8182
         3  GRAY,MARILYN........... 734-182-9137
         4  HAMILTON,MARQUITA...... 427-596-7490
         5  JOYCE,ANDREA........... 973-301-1325
         6  JUAREZ,APRIL........... 797-884-7359
         7  MCNEIL,ROSA............ 371-600-6252
         8  NGUYEN,DEBORA.......... 768-170-8249
         9  NGUYEN,EMILIO.......... 479-272-4704
        10  ORR,LENARD............. 948-836-8442
        11  PIERCE,CLEVELAND....... 620-966-4334
        12  PIERCE,ZACHERY......... 372-775-2096
        13  ROY,RUBY............... 920-777-5449
        14  ROY,TERRA.............. 954-377-4587
        15  SNIDER,DOLORES......... 945-847-4679
        16  SNIDER,REGGIE.......... 292-618-9887
        17  WHITE,MAY.............. 292-698-2214
        18  WHITE,MAY.............. 377-478-2317

    unix> ./Prog2 -qsort list1.txt 
    unix> cat -n qsort_list1.txt 

    [same as above]

    unix> ./Prog2 -qsort 6 8 list1.txt
    unix> cat -n qselect_list1.txt 

         1  DOWNS,WENDY............ 973-843-8182
         2  HAMILTON,MARQUITA...... 427-596-7490
         3  GRAY,MARILYN........... 734-182-9137
         4  JOYCE,ANDREA........... 973-301-1325
         5  DORSEY,DELLA........... 619-905-1761
         6  JUAREZ,APRIL........... 797-884-7359
         7  MCNEIL,ROSA............ 371-600-6252
         8  NGUYEN,DEBORA.......... 768-170-8249
         9  NGUYEN,EMILIO.......... 479-272-4704
        10  ORR,LENARD............. 948-836-8442
        11  WHITE,MAY.............. 377-478-2317
        12  PIERCE,ZACHERY......... 372-775-2096
        13  ROY,RUBY............... 920-777-5449
        14  ROY,TERRA.............. 954-377-4587
        15  SNIDER,DOLORES......... 945-847-4679
        16  WHITE,MAY.............. 292-698-2214
        17  SNIDER,REGGIE.......... 292-618-9887
        18  PIERCE,CLEVELAND....... 620-966-4334

Notice that the data in lines 1-5 should go before line 6, but it is not sorted. Likewise, the data in lines 9-18 should go after line 8, but it is not sorted. The data has been partitioned correctly relative to lines 6-8 which have been sorted. The above was produced an a MacBook. You may see different orderings on a Hydra machine. This has to do with how the random numbers are generated. Always run the solution executable to produce output for comparison with output produced by your code.


    unix> ./Prog2 -stdsort list3.txt 
    unix> cat -n stdsort_list3.txt  

        [snip]
        70  ALLEN,ALDEN............ 788-305-9775
        71  ALLEN,JESSE............ 845-316-9563
        72  ALLEN,KENDALL.......... 737-817-8872

        73  ALLISON,AIDA........... 494-461-5374
        74  ALLISON,EDDY........... 604-153-7974
        75  ALLISON,JIMMIE......... 713-552-4180
        76  ALLISON,JUANA.......... 456-778-9470
        77  ALLISON,KATINA......... 964-821-9988
        78  ALLISON,MAYRA.......... 386-151-5636
        79  ALLISON,MAYRA.......... 811-844-2524
        80  ALLISON,SAL............ 443-244-3465
        81  ALLISON,SAL............ 694-613-2997

        82  ALSTON,ARNOLD.......... 607-430-6838
        83  ALSTON,JULIANA......... 625-523-1294
        84  ALSTON,JULIET.......... 513-574-8327
        85  ALSTON,LAKISHA......... 908-289-9774
        86  ALSTON,OSCAR........... 875-730-8656
        87  ALSTON,TAMEKA.......... 844-480-2321
        88  ALSTON,TREVOR.......... 950-488-3715
        [snip]

Notice that the data is sorted first by lastname (ALLEN before ALLISON before ALSTON), then by firstname (AIDA before EDDY before ... before SAL), and then phonenumber (MAYRA and SAL). There may be other examples in the data you are given. If not, you can always add some yourself.

------------------------------------------------------------------------

### Grading rubric

Note: Output format of your program must MATCH the solution executable. Use the diff command to compare.  

#### Prog2 (80 points)

    10: Class data: operator<(), operator>>(), and operator<< ()
    20: Main function: command line arguments, program flow
    30: Quicksort: random pivot, integrated partitioning, recursive
    20: Quickselect: random pivot, integrated partitioning, iterative

------------------------------------------------------------------------

Sun Jan 28 17:14:54 EST 2024
