# COSC 202 — Lab Assignment 3

Table of Contents

-   [Getting Motivated](#_getting_motivated)
-   [Lab Submission](#_lab_submission)
-   [Assignment Details](#_assignment_details)
    -   [Prime numbers](#_prime_numbers)
    -   [Getting started](#_getting_started)
    -   [30 Points](#_30_points)
    -   [50 Points](#_50_points)
    -   [10 Extra Credit Points](#_10_extra_credit_points)
    -   [Grade Rubric (80 + 10) points](#_grade_rubric_80_10_points)

## Getting Motivated

In this lab, you will write a program for determining whether numbers are prime or not. You will make use of several STL functionalities. See <https://www.cplusplus.com> for descriptions and explanations. The `<algorithm>` section is probably where you want to focus your attention.

## Lab Submission

Your tar file must contain the following files:

-   Prog3.cpp

-   Support.cpp

In order to earn points, the code must compile and produce output as described below.

## Assignment Details

The lab3.tar file contains:

-   Prog3.cpp

    -   Empty file that you must write.

-   Support.cpp

    -   Empty file that you must write.

-   Support.h

    -   Provides a full class definition. You may not edit this file.

-   makefile

    -   For creating a Prog3 executable

-   sprog3

    -   Solution executable

-   Numbers

    -   Produces random numbers. Can be called with two command line parameters N and M which are the number of random numbers to generate and the max value to generate. For example, `./Numbers 10 20` would produce 10 numbers within the range `[1, 20]`.

### Prime numbers

An iterger represents a prime number if the number is greater than 1, and its only divisors are 1 and the number itself. Non-prime numbers are composite in that they are the product of primes.

Given a number N, you can determine if it is prime by trying to divide increasingly larger numbers into it. If a particular division is successful, the number is not prime, and you can stop. What is the biggest number you need to test? Well, say \\$N = XY\\$. If \\$X &gt; sqrt(N)\\$, then \\$Y &lt; sqrt(N)\\$. Therefore, once you have tested \\$X = 2, 3,... , sqrt(N)\\$, you have indirectly also tested \\$X = sqrt(N+1),... ,N\\$, since \\$XY = YX\\$. The following function does the job:

    bool isprime(int N) {
      for(int i = 2; i * i <= N; i++) {
        if(N % i == 0)
          return false;
      }
      return true;
    }

<table><colgroup><col style="width: 50%" /><col style="width: 50%" /></colgroup><tbody><tr class="odd"><td><div class="title">Note</div></td><td>We avoided computing \$sqrt(N)\$ by using the square of the test variable for the termination comparison. This likely doesn’t make a program run faster, but it allows using integers for everything.</td></tr></tbody></table>

### Getting started

Implement the code described below. Do not change names of functions or variables. Do not add functions not asked for. The provided makefile must be able compile your program.

### 30 Points

Write `Support.cpp` which contains the member functions for the `isprime` class defined in `Support.h` and reproduced here:

    class isprime {
      bool verbose;
      vector <int> known_primes;

      void expand_known_primes(int);

      public:
      isprime(bool verbose=false);
      bool operator()(int);
    };

The constructor sets the verbose variable, which has a default value of false, and initalizes the `known_primes` vector to hold one number, namely, the value 2 which is the smallest prime number.

The overloaded function operator returns false if given a number is less than 2. Otherwise, it compares the number against the last number added to the `known_primes` vector. If the new number is larger, the `expand_known_primes()` function is called to add more prime numbers as described next. Either way, `std::binary search()` is used to determine if the number is found in the `known_primes` sequence of prime numbers. See <https://www.cplusplus.com> for details.

Function `expand_known_primes()` implements an appropriately modified version of the `isprime()` function for determining whether a number is prime to add prime numbers to the `known_primes` vector until the new number being tested is on the list or the list contains a prime number larger than it. Do not simply implement and call the above `isprime()` function. Your class is a wrapper around it that uses past computations to make many new checks a simple lookup matter.

### 50 Points

Write `Prog3.cpp` which in its simplest form contains driver code reading an unspecified number of integers from stdin and printing the prime numbers to stdout.

Instantiate an `isprime` object and a vector that can hold integers. Read numbers from cin. Use the overloaded `isprime` function operator to check if a number is prime. Store a new prime number at the back of said vector. Continue until there is no more input on cin.

Print the prime numbers seen to cout as follows: use 4 characters per number, max 20 numbers per line. Test your program using the Numbers executable which takes two optional arguments. If provided, the first is a number that specifies how many random numbers to produce (default is 10) while the second number specifies the range of the random numbers (default is 20). The random number sequence is seeded by the number of random numbers produced. This makes comparing across runs easier.

<table><colgroup><col style="width: 50%" /><col style="width: 50%" /></colgroup><tbody><tr class="odd"><td><div class="title">Note</div></td><td><code>Numbers</code> will be consistent between runs on the same machine but not necessarily across machines. This means that the following examples might not match what you get on your machine. This is fine. We just want random numbers.</td></tr></tbody></table>

    unix> ./Numbers -help
    usage: ./Numbers [N M]

    unix> ./Numbers
      11    4    2   13    6    7    1   19    9    8

    unix> ./Numbers | ./Prog3
      11    2   13    7   19

    unix> ./Numbers 100 30
      11   10    6    6   30   24    3    2    2   20    5   24   20   30   26   17   22   11   15   29
      14   15   15   30   23   27   28   26    4    1    4   29   19   13   20   17   20   26   28   19
      23   25   17   16   16    2   30   25   22   10   29   22   30    2    6   29   25   28    1   29
      11   21    4   14   25   28   29   28    3   22   21   15    2    4   27   19   23   26   29   22
      27   17   24   15   19    7   30   27   28   15   20   21   16   14    8    3   24   13   19   14

    unix> ./Numbers 100 30 | ./Prog3
      11    3    2    2    5   17   11   29   23   29   19   13   17   19   23   17    2   29    2   29
      29   11   29    3    2   19   23   29   17   19    7    3   13   19

When the above works, add an optional command line argument to your program that either produces sorted prime numbers or a sorted sequence of unique prime numbers. Use `std::sort()`, `std::unique()`, and `vector::erase()`.

    unix> ./Numbers 100 30 | ./Prog3 -sorted
       2    2    2    2    2    3    3    3    5    7   11   11   11   13   13   17   17   17   17   19
      19   19   19   19   23   23   23   29   29   29   29   29   29   29

    unix> ./Numbers 100 30 | ./Prog3 -unique
       2    3    5    7   11   13   17   19   23   29

### 10 Extra Credit Points

Modify `Prog3.cpp` and `Support.cpp` to accept and use a second optional command line argument used to produce detailed output on when and how `isprime::known_primes` is updated.

    unix> ./Numbers 100 30 | ./Prog3 -verbose
    updating 11
    ** adding 3
    ** adding 5
    ** adding 7
    ** adding 11
    updating 30
    ** adding 13
    ** adding 17
    ** adding 19
    ** adding 23
    ** adding 29
    ** adding 31
      11    3    2    2    5   17   11   29   23   29   19   13   17   19   23   17    2   29    2   29
      29   11   29    3    2   19   23   29   17   19    7    3   13   19

Compare this with the Numbers output above. Checking 11 causes 3, 5, 7, and 11 to be added. This then allows 10, 6, and 6 to handled by lookup. Checking 30 causes 13, …​, 29, 31 to be added. This allows all remaining input to be handled by lookup. Try different cases yourself. The code needed consists of a few lines in `Prog3.cpp` and a couple of lines in `Support.cpp`. Don’t overthink it.

### Grade Rubric (80 + 10) points

-   30: Correct output (read and print all data)

-   15: Code: `isprime::isprime()`, `isprime::operator()`

-   15: Code: `isprime::expand_known_primes()`

-   10: Code: sorted option and output

-   10: Code: unique option and output

-   10: Extra: verbose option and output

Last updated 2023-09-16 10:41:52 -0400
