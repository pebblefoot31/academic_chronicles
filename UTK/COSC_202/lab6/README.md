# COSC 202 — Lab Assignment 6

Table of Contents

-   [Getting Motivated](#_getting_motivated)
-   [Lab Submission](#_lab_submission)
-   [Provided Files](#_provided_files)
-   [Prog6.cpp](#_prog6_cpp)
    -   [`main()` (20 points)](#_main_20_points)
    -   [`main()` calling `find_solution()` (10 points)](#_main_calling_find_solution_10_points)
    -   [`find_solution()` (40 points)](#_find_solution_40_points)
    -   [`show_solution()` (10 points)](#_show_solution_10_points)
-   [Grade Rubric (120 points)](#_grade_rubric_120_points)

## Getting Motivated

In this lab, you will gain experience with recursion. Specifically, you will write a program that determines one or more sequences of arithmetic operations that produce the correct answer given a sequence of numbers and a solution. For example, the sequence 5 3 4 2 3 has two answers, namely, \\$((5-3)+4)//2 = 3\\$ written as `-+/`, and \\$((5//3)+4)-2 = 3\\$ written as `/+-`. You will also explore permutations of the input. More on that below. Your program will not consist of very many lines of code, but it may take you a while to get things rights, so pace yourself.

In this lab, we will make use of backtracking. Backtracking is a recursive method for exploring different branches in the search tree that represents all the possible ways solutions can be obtained as well as branches that correspond to failed attempts. If this seemed abstract, then you might want to revisit your notes on the game of Nqueens and Sudoku before continuing.

## Lab Submission

Your tar file must contain the following files:

-   Prog6.cpp

In order to earn points, the code must compile with the provided makefile and produce output as described below. Implement the code as described below. Do not change names of functions or variables. Do not add functions not asked for.

## Provided Files

The lab6.tar file contains:

-   Prog6.cpp

    -   Skeleton file that you must convert to working code.

-   makefile

    -   For creating a Prog6 executable from your code

-   sprog6

    -   Solution executable

-   Numbers

    -   Executable to generate random numbers

## Prog6.cpp

This file consists of two functions called `show_solution()` and `find_solution()` plus a main function that handles command line parsing and code execution. You will not be defining a class. You will, on the other hand, be using a couple of global variables since that cuts back on the number of variables you need to pass to the two mentioned functions. In case you were ever told to not use global variables, then that was good advice, but we will do it anyway. Don’t worry, the sky won’t fall.

    bool success = false;
    bool findall = false;
    bool verbose = false;

    bool show_solution(vector, vector);
    bool find_solution(vector, vector, int k=0, int fvalue=0);

### `main()` (20 points)

Implement the main function to have it parse the command line arguments and read input data from stdin. Your program should take two required arguments. The first argument controls whether you consider the numbers in their given order (option `-inorder`) or any permutation of the first \\$n-1\\$ numbers (option `-anyorder`). That is to say for `-anyorder`, the target solution will stay the same. The second argument controls whether you produce just one solution (option `-1` should set findall false) or all possible solutions (option `-2` should set findall true). Finally, the program should accept an optional argument that changes how you report a solution (option `-verbose` should set verbose true). That is,

    unix> ./Prog6 -inorder|anyorder -1|2 [-verbose] < numbers.txt

Print an error message if missing or incorrect command line options are at play. As indicated, read data from stdin. Store the data in a vector object. The last number read is the solution (target value). The other numbers are the values you combine arithmetically to produce the solution.

### `main()` calling `find_solution()` (10 points)

Have the main function execute the appropriate calls to `find_solution()`. That is, the inorder mode should result in a single call that explores one or more solutions for the data as given while the anyorder mode should result in all permutations of the data being explored.

HINT: Use `std::next_permutation()` to implement the anyorder mode.

### `find_solution()` (40 points)

Implement `find_solution()` to have it compute either one or all solutions based on the value of `findall`. The only difference is whether the base case returns true or false when having found a solution.

The base case is reached when the number to be processed represents the target value. This is indicated by the third argument, which is called k above. If the fourth argument, which is called fvalue above, matches the target value, a solution has been found in which case `show_solution()` is called and success is set to true. Then `find_solution()` returns true or false as needed to stop or continue the search for more solutions.

Initially, `find_solution()` is called with just the numbers and operations vector objects given. This lets `k` and `fvalue` arguments take on their default values which are both 0. This means there is nothing for `find_solution()` to do other than issue a recursive call to `find_solution()` with a `k` value of 1 and an `fvalue` equal to the first number. That is,

    find_solution(numbers, operations, 0, 0) --> find_solution(numbers, operations, 1, numbers[0])

From this point onward, each call to `find_solution()` causes an exhaustive search to be executed that enumerates the four arithmetic operations allowed. The order must be `+,-,*,/` to match the solution code. The operation is added to the back of the operations vector, the `fvalue` is updated based on the operation and the number considered, then `find_solution()` is called for the next number and the new `fvalue`. This continues until the base case is reached. The return value of the recursion is used to decide whether to end the search or to continue to look for another solution based on the next artimetic operation. If continuing, the last operation considered is popped off the operations vector so a new operation can take its place. When all operations have been tried, the function returns false to indicate the search is not over.

### `show_solution()` (10 points)

Implement `show_solution()` to have it print the sequence of operations to stdout. If the verbose option is active, a more readable format that includes the numbers is printed first ending with a calculated value that represents the result of applying the various operators in the order specified. Continuing the example from above, \\$((5-3)+4)//2 = 3\\$ would be written as `5-3+4/2=3 -+/` with verbose active and `-+/` without. See more examples below.

Numbers takes an integer argument N and produces that N random numbers, N-1 arithmetic operations, and the result of applying those. This data can be piped to Prog6. Both programs take an optional -verbose argument that produces human readable output for manual verification. See examples below.

    unix> ./Numbers 5
    13 20 1 19 3 4

    unix> ./Numbers 5 | ./Prog6 -inorder -1
    ++/+

    unix> ./Numbers 5 -verbose
    13 20 1 19 3 4
    13-20*1+19/3=4

    unix> ./Numbers 5 -verbose | ./Prog6 -inorder -1 -verbose
    13-20*1+19/3=4
    13+20+1/19+3=4 ++/+

    unix> ./Numbers 5 -verbose | ./Prog6 -inorder -2 -verbose
    13-20*1+19/3=4
    13+20+1/19+3=4 ++/+
    13+20-1-19/3=4 +--/
    13+20-1/19+3=4 +-/+
    13+20*1-19/3=4 +*-/
    13+20*1/19+3=4 +*/+
    13+20/1-19/3=4 +/-/
    13+20/1/19+3=4 +//+
    13-20+1+19/3=4 -++/
    13-20*1+19/3=4 -*+/ <-- original sequence
    13-20/1+19/3=4 -/+/
    13*20+1/19/3=4 *+//
    13*20-1/19/3=4 *-//
    13*20*1/19/3=4 **//
    13*20/1/19/3=4 *///

    unix> ./Numbers 5 -verbose | ./Prog6 -anyorder -1 -verbose
    13-20*1+19/3=4
    1+3*19+13/20=4 +*+/
    1+3*19-20/13=4 +*-/
    1+3*20+13/19=4 +*+/
    1+3*20-19/13=4 +*-/
    1/13+3-19+20=4 /+-+
    ...
    20+13-19/3*1=4 +-/*
    20-19-1+13/3=4 --+/
    20+19+3/13+1=4 ++/+
    20-19+13-1/3=4 -+-/
    20-19+13/3*1=4 -+/*

    unix> ./Numbers 5 -verbose | ./Prog6 -anyorder -2 -verbose
    13-20*1+19/3=4
    1+3*19+13/20=4 +*+/
    1+3*19-20/13=4 +*-/
    1+3*20+13/19=4 +*+/
    1+3*20-19/13=4 +*-/
    1/13+3-19+20=4 /+-+
    ...
    20/19+13/3*1=4 /+/*
    20/19+13/3/1=4 /+//
    20/19*13/3*1=4 /*/*
    20/19*13/3/1=4 /*//
    20/19/13+3+1=4 //++

The more numbers you produce, the greater the chance that many solutions exist. The inorder mode shown above found a total of 14 different solutions. The anyorder mode found 88 different solutions, even when considering only the first solution found for each permutation. When considering all solutions, a total of 504 are found. Run the programs as shown and study the full output. Write the anyorder mode for all solutions to file and look for the original sequence of numbers and operations.

HINT: You find it on line 235 but interestingly, 6 other permutations solve the problem using the same sequence of operations.

<table><colgroup><col style="width: 50%" /><col style="width: 50%" /></colgroup><tbody><tr class="odd"><td><div class="title">Note</div></td><td>You must search using the order of operations stated above to produce the same output as the solution executable. The grade script will not accept output ordered differently.</td></tr></tbody></table>

Since the number of solutions can get big for even short sequences, you may want to limit yourself to 6 numbers or less when you run the anyorder mode. You can (and should) try as many as 100 numbers when running the single solution inorder mode. For the all solutions inorder mode, you will also want to run shorter sequences.

## Grade Rubric (120 points)

-   20: `main` function: command line parsing, reading input data

-   10: execution of `find_solution`: inorder, anyorder (perms)

-   40: `find_solution`: backtracking, one vs all solutions

-   10: `show_solution`: quiet and verbose display of operations

-   40: correct output data

Last updated 2023-10-26 09:25:51 -0400
