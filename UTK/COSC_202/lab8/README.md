# COSC 202 — Lab Assignment 8

Table of Contents

-   [Getting Motivated](#_getting_motivated)
-   [Lab Submission](#_lab_submission)
-   [Provided Files](#_provided_files)
-   [Goldbach Partitioning](#_goldbach_partitioning)
-   [Getting Started](#_getting_started)
    -   [`main()` (15 points)](#_main_15_points)
    -   [`class prime_partition` (15 points)](#_class_prime_partition_15_points)
    -   [`create_pset()` function (20 points)](#_create_pset_function_20_points)
    -   [Non-recursive `find_partition()` function (15 points)](#_non_recursive_find_partition_function_15_points)
    -   [Recursive `find_partition()` function (25 points)](#_recursive_find_partition_function_25_points)
    -   [Verbose output (10 points)](#_verbose_output_10_points)
-   [Grade Rubric (120 points)](#_grade_rubric_120_points)

## Getting Motivated

Positive integers greater than 3 can be written as the sum of prime numbers (aka primes). Indeed, a German mathematician by the name of Goldbach conjectured in 1742 that even integers greater than 2 can be expressed as the sum of two primes and that every integer greater than 5 can be written as the sum of three primes. According to Wikipedia, the former condition has been shown empirically for integers less than 4,000,000,000,000,000,000 (which is a really big number) but a formal proof has yet to be established.

Your job is to write a program that can partition user supplied integers into a sum of three primes. To keep things simple, we will use 100,000 as an untested cap on the input. That is, you can try arbitraily large integers but the grade script will only use "small" valued integers.

## Lab Submission

Your tar file must contain the following files:

-   `Prog8.cpp`

-   `Support.h`

-   `Support.cpp`

In order to earn points, the code must compile with the provided makefile and produce output as described below. Implement the code as described below. Do not change names of functions or variables. Do not add functions not asked for.

## Provided Files

The `lab8.tar` file contains:

-   `Prog8.cpp`, `Support.h`, `Support.cpp`

    -   Skeleton files that you must convert to working code.

-   `makefile`

    -   For creating a Prog7 executable from your code

-   `sprog8`

    -   Solution executables

## Goldbach Partitioning

With this being your last regular lab assignment, you will only be given skeleton code to work with. Ultimately, your program must consist of a main function that instantiates a prime\_partition object called goldbach which uses backtracking to partition user given numbers into said sums of three primes. To avoid repeatly checking for primality, the prime\_partition object maintains a binary search tree that holds known primes. This set is expanded when a number given exceeds the largest known prime.

If this sounds familiar, then you have paid attention. Lab 3 had you write a program that checked whether numbers were primes based on a list of known prime numbers. Here you use a binary search tree plus a more efficient algorithm. Lab 6 gave you experience with backtracking based enumeration of possible solutions. Here you add a valid check to rule out numbers that cannot lead to a solution. Lab 7 had you implement binary search tree iterators as well as lower and upper bounds. Here you use the std::set implementation.

<table><colgroup><col style="width: 50%" /><col style="width: 50%" /></colgroup><tbody><tr class="odd"><td><div class="title">Warning</div></td><td>You may need to read the assignment and the skeleton code given to you several times before you can wrap your head around the problem and its solution. You will likely find working out the logic for the solution to be more difficult than writing the code that implements it.</td></tr></tbody></table>

## Getting Started

-   Prog8 has a required command line argument that controls the underlying computation. The solution executable allows this argument to be forward or reverse. Your program must implement the forward mode. Students who seek an extra challenge (and bragging rights) are encouraged to implement the reverse mode as an option. More on both modes below. Your program must accept a single optional command line argument that activates verbose output.

    unix> ./Prog8 -forward [-verbose]           <-- required
    unix> ./Prog8 -forward|reverse [-verbose]   <-- bragging rights

### `main()` (15 points)

Implement Prog8.cpp to contain a properly functioning main function that can read command line arguments, provide meaningful error output when given incorrect/missing arguments. All being well, the program then enters into an endless while-loop that prompts for and accepts numbers from stdin, provides meaningful error output if they are less than 6, and otherwise partitions the number into a sum of three primes. Include all header files needed to make your program compile. Do NOT include header files that are not needed. You MUST leave the prime\_partition definition of the goldbach object and the call to the find\_partition() member function as is.

### `class prime_partition` (15 points)

-   Define the prime\_partition class, so that it can do the job specified in the main function. You will need a constructor and a public member function for activating verbose output, and the public non-recursive `find_partition()` member function for initiating the computation. You will need a few private member functions for implementing the latter including `expand_pset()` for expanding and maintaining a set of known primes, `is_valid()` for determining whether a number has the potential to be part of the solution or not, and a recursive version of `find_partition()` that uses backtracking to iterate thru known primes. You are free to add other private member functions. You will also need private data members including a data structure for storing known primes and a data structure for storing the partition values as they are computed. You **MUST** use an std::set based binary search tree called pset to store and process the known primes. You are free to chose how to store the partition values (these are the primes that sum up to the input number).

<table><colgroup><col style="width: 50%" /><col style="width: 50%" /></colgroup><tbody><tr class="odd"><td><div class="title">Note</div></td><td>Function and data members named in Support.h <strong>MUST</strong> remain part of your program. Access to the binary search tree data <strong>MUST</strong> be based on iterators except when inserting new data at which point you <strong>MUST</strong> use the <code>insert()</code> member function.</td></tr></tbody></table>

The prime\_partition class constructor and member functions must **ALL** be implemented in `Support.cpp` as described next.

Implement the constructor which initializes the pset to contain the value 2. You will add more values to pset next. Do not don’t do it here. Initialize all other data members so that they all have defined values.

Implement a support function for activating verbose output. Consider using a setter function that updates a boolean variable. Students who decide to implement the above mentioned reverse mode, should add a setter function and an enum variable that can activate it.

### `create_pset()` function (20 points)

Implement the `create_pset()` function which is called by the non-recursive `find_partition()` function when given a number that is larger than pset\_max, the largest known prime stored by pset. Initially, import the equivalent code from Lab 3. When you have that working, replace the simple for-loop based search with a so-called sieve based algorithm.

With reference to Wikipedia, [The Sieve of Eratosthenes](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes) is a 2,000 year old algorithm for finding all prime numbers up to a given limit. The basic version says to write out all numbers and mark off composites of known primes. For example, 2 is a prime number. That allows marking off \\${4, 6, 8, ...}\\$ as not being prime. Since 3 is not marked off, it is prime. This allows marking off \\${6, 9, 12, ...}\\$ as not being prime. And so forth. Instead of creating a list of all numbers and indicate whether they are prime or not, we can use modulo arithmetic as follows.

    expand_pset(number) {
      next = pset_max+1
      while (pset_max < number) {
        for each k in pset {
          if (next%k == 0) {
            next not prime
            break
          }
        }

        if (next is prime) {
          add to pset
          update pset_max
        }

        next += 1
      }
    }

We can make the algorithm even more efficient by realizing that we only need to check the pset values \\$k &lt;= sqrt(text(number))\\$. You work out the logic for why this is and how to incorporate it above.

There are a couple of pitfalls. Watch out for whether pset\_max is smaller or larger than this upper bound. Additionally, since we are dealing with integers, round-off associated with a square root based condition can be problematic. A better approach is to define the largest pset value that needs to be checked based on \\$k\_max \* k\_max &gt;= text(number)\\$. Starting with \\$k\_max = sqrt(text(number))\\$, we need to incrementally increase this value as long as \\$k\_max \* k\_max &lt; text(number)\\$. When this condition no longer holds, then \\$k\_max \* k\_max &gt;= text(number)\\$.

### Non-recursive `find_partition()` function (15 points)

Implement the non-recursive `find_partition()`. First, if necessary, expand the set of known primes using `expand_pset()`. Next, apply the recursive `find_partition()` function. Lastly, print the partition to stdout. You will see that the skeleton code includes a check for success and an error message if the the computation was unsuccesful. Keep this even though you are unlikely to ever execute it.

### Recursive `find_partition()` function (25 points)

Implement the recursive `find_partition()` which implements a backtracking based search. The function takes two arguments, namely, the number to be partitioned and the partition term index of the number. Initially, you make make the call `find_partition(number, 0)` before iteratively trying `find_partition(number - k, 1)` for all k values in pset less than or equal to the number itself until a solution has been found.

There is single base case to consider, namely, when the number considered is 0 since that leaves nothing to partition. When this condition is not met, all relevant prime numbers are tested in order. The forward mode you are asked to implement iterates thru increasingly larger pset values. The optional reverse mode iterates thru decreasingly smaller pset values. We could add more base cases that detect we are not on the right track, but we will implement and use a boolean `is_valid()` instead. Having function control whether to execute a recursive call on a subproblem is similar to what you saw in class for N-queens and Sudoku.

Work the logic for `is_valid()` out yourself. Pass the number to potentially be partitioned next along with the number of terms in the current partition to `is_valid()`. Think about what it means if the number is 0 or 1. Think about what it means if the number of terms has reached the max number to be considered — or not. For example, should `is_valid(0,1)` return true or false? What about `is_valid(0,2)` and `is_valid(0,3)`? Should `is_valid(1,1)`, `valid(1,2)`, and `is_valid(1,3)` return true or false? What about `is_valid(N,1)`, `is_valid(N,2)`, and `is_valid(N,3)` where \\$1 &lt; N\\$?

Let us work thru an example, so you get a better feel for the computation. This contains a lot of details. Write everything out and make sure you follow the logic.

    unix> ./Prog8 -forward
    number = 24
    2+3+19

We first calculate all primes needed to cover 24 and add them to pset: 2, 3, 5, 7, 11, 13, 17, 19, 23, 25. Then we call `find_partition(24,0)` which sets off the following search. Since 24 is not 0, we iteratively try \\$k = 2, 3, ..., 23\\$. When trying 2, we find that `is_valid(24-2,1)` is true and therefore make the recursive call `find_partition(22,1)`. Since 22 is not 0, we initiate a second search, again starting with 2, which leads to `is_valid(22-2,2)` which is true thus producing the call `find_partition(20,2)`. Since 20 is not 0, we try a new sequence of prime numbers starting with 2 and end with 19. For 2, `is_valid(20-2,3)` returns false since we have used 3 terms and have 18 left to partition. We therefore move on to 3. Different numbers, same situation. This continues until we have exhausted the allowed prime values including 19 for which `is_valid(20-19,3)` is false since the resulting value of 1 cannot be partitioned. We therefore backtrack and change the second term to 3 which leads to `find_partition(19,2)`. Since 19 is not 0, we iteratively try \\$k = 2, 3, ..., 19\\$. We find that `is_valid(19-k,3)` is false until `k=19` at which point we execute `find_partition(0,4)`. This is recognized as our base which indicates a solution has been found. We ascend back out of the recursion and print the solution `2+3+19` shown above. Write these steps out on a piece of paper. Make sure you understand them.

    unix> ./Prog8 -reverse
    number = 24
    19+3+2

Since 24 is not 0, we iteratively try \\$k = 23, 19, 17, ..., 3, 2\\$. For 23, `is_valid(1,1)` returns false. Continuing with 19, `is_valid(24-19,1)` is true which means the search continues for `find_partition(5,1)`. We then iteratively try \\$k = 3, 2\\$. Since `is_valid(5-3, 2)` is true, we call `find_partition(2,2)`. Since 2 is not prime, we then try the only prime available, namely, 2 for which `is_valid(0,3)` is true since the 0 shows we have found a sum that adds up to the original number and the 3 means we have do it using 3 terms as desired. We therefore stop ascend out of the recursion and print the solution `19+3+2`. Again, write these steps out on a piece of paper. Make sure you understand them.

That’s it! Once you can follow the above logic, writing the code not as difficult as it may sound. That said, expect seg faults and endless loops until you get the order of the termination conditions right.

A few final words on the optional reverse mode. The search should start with the largest prime not greater than the number considered and should end with the smallest prime number possible, viz., 2. While it would be tempting to somehow combine `std::upper_bound()` with `std::rbegin()` and `std::rend()`, the former returns a bidirectional iterator while the two latter return incompatible reverse\_iterators. Instead, work everything out using `std::begin()` and `std::end()` as appropriate and decrement the iterator used for the search. This will make more sense when you start doing it.

### Verbose output (10 points)

Add code that supports the verbose option. Specifically, make the non-recursive `find_partition()` function print the pset values to stdout each time the set is expanded to accommodate partioning of a new, larger number. To prevent too much output, print all values only if the pset contains 20 or fewer prime numbers. When it grows to contain more, print the first 10 and the last 4 with ellipses in between. In addition, add a few lines of code to the recursive `find_partition()` function so that it can print how the partioning is progressing. Do not print pset values that `in_valid()` determines don’t lead to a solution since that quickly becomes overwhelming to look at. The "←- explanation" is not part of the verbose output.

    unix> ./Prog8 -forward -verbose
    number = 19
    2 3 5 7 11 13 17 19
    19
    2+17     <-- 19=2+17
    2+2+15     <-- 17=2+15
    2+3+14     <-- ...
    2+5+12
    2+7+10
    2+11+6     <-- ...
    2+13+4     <-- 17=13+4
    3+16     <-- 19=3+16
    3+2+14     <-- 16=2+14
    3+3+13     <-- 16=3+13

    number = 24
    2 3 5 7 11 13 17 19 23 29
    24
    2+22
    2+2+20
    2+3+19

Notice how the pset grows when a larger number is input. Students who implement the reverse mode should run the solution code to see the output produced.

## Grade Rubric (120 points)

-   15: Prog8.cpp: main() function

-   15: Support.h: prime\_partition class definition

-   20: Support.cpp: create\_pset() function

-   15: Support.cpp: non-recursive find\_partition() function

-   25: Support.cpp: recursive find\_partition() function

-   10: Support.cpp: verbose output

-   20: Correct output

Last updated 2023-11-18 07:58:06 -0500
