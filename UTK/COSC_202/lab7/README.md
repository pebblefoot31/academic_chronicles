# COSC 202 — Lab Assignment 7

Table of Contents

-   [Getting Motivated](#_getting_motivated)
-   [Lab Submission](#_lab_submission)
-   [Provided Files](#_provided_files)
-   [Getting Started](#_getting_started)
    -   [Mode 1](#_mode_1)
    -   [Mode 2](#_mode_2)
    -   [Mode 3](#_mode_3)
    -   [Mode 4](#_mode_4)
-   [Grade Rubric (150+25 points)](#_grade_rubric_15025_points)
    -   [Mode 1 (30 points)](#_mode_1_30_points)
    -   [Mode 2 (80 points)](#_mode_2_80_points)
    -   [Mode 3 (40 points)](#_mode_3_40_points)
    -   [Mode 4 (25 extra points)](#_mode_4_25_extra_points)

## Getting Motivated

In this lab, you will gain familiarity with the binary search tree data structure and the iterator abstraction.

## Lab Submission

Your tar file must contain the following files:

-   `bst.h`

In order to earn points, the code must compile with the provided makefile and produce output as described below. Implement the code as described below. Do not change names of functions or variables. Do not add functions not asked for.

## Provided Files

The lab6.tar file contains:

-   `bst.h`

    -   Skeleton file that you must convert to working code.

-   `makefile`

    -   For creating a Prog7 executable from your code

-   `sprog7_str`, `sprog7_char`, `sprog7_int`

    -   Solution executables

-   `test1_int.txt`, `test2_int.txt`, `test_char.txt`, `test_string.txt`

    -   Some example data files to use for testing

## Getting Started

For this lab, you are completing the binary search tree class in `bst.h`. The main program takes two required command line options that specify the mode and the data used as well as an optional verbose option.

    unix> ./sprog7_char
    usage: ./sprog7_char -1|2|3|4 [-verbose] data.txt
    unix> cat ../test_char.txt
    H
    W
    B
    E
    T
    F

    unix> ./sprog7_char -1 ../test_char.txt
      0   H : ROOT  L=  2 R=  1
      2   B : P=  0       R=  3
      1   W : P=  0 L=  4
      3   E : P=  2       R=  5
      4   T : P=  1
      5   F : P=  3

    unix> ./sprog7_char -2 ../test_char.txt
       B   E   F   H   T   W

    unix> ./sprog7_char -3 -verbose ../test_char.txt
       B   E   F   H   T   W

    Print [key0:key1] A O
    *** lower bound B
    *** upper bound T
       B   E   F   H

    Print [key0:key1] K X
    *** lower bound T
    *** upper bound NA
       T   W

    Print [key0:key1] ^D

    unix> ./sprog7_char -4 -verbose ../test_char.txt
       W   T   H   F   E   B

    Print [key0:key1] A O
    *** lower bound B
    *** upper bound T
       H   F   E   B

    Print [key0:key1] K X
    *** lower bound T
    *** upper bound NA
       W   T

    Print [key0:key1] ^D

Mode 1 exectures a level-by-level traversal and prints the node labels to stdout. Mode 2 executes an inorder traversal and prints the node labels to stdout using a forward iterator loop (using `operator++()`). Mode 3 repeats Mode 2 before entering an interactive loop that prints user defined ranges of the data. Printing of the data is based on the same forward iterator loop used in Mode 2. Mode 4 is similar to Mode 2 but prints everything in reverse. This is based on a reverse iterator loop (using `operator--()`)

<table><colgroup><col style="width: 50%" /><col style="width: 50%" /></colgroup><tbody><tr class="odd"><td><div class="title">Tip</div></td><td>The level-by-level printout uses node IDs to identify parent nodes and subtrees. In the example above, the root node has <code>ID=0</code> and <code>label=H</code>. The left child has <code>ID=2</code> and <code>label=B</code> while the right child has <code>ID=1</code> and <code>label=W</code>. Both children have <code>P=0</code> meaning the root node.</td></tr></tbody></table>

<table><colgroup><col style="width: 50%" /><col style="width: 50%" /></colgroup><tbody><tr class="odd"><td><div class="title">Note</div></td><td>Mode 4 is extra credit. If you successfully implement Mode 2, then you should not have much trouble implementing Mode 4.</td></tr></tbody></table>

### Mode 1

Look at `bst.h`. Strip out comments as well as code not needed like the iterator subclass and undefined `bst` member functions. Add a node ID that is an int and a parent pointer that is a node pointer to the `bst::node` subclass. Define and implement the `bst::node()` constructor. Have the constructor take a node ID argument which is set to 0 if absent, and use this argument to initialize the node ID. Set the parent pointer to NULL.

The node ID is an unique integer assigned to nodes as they are created. Add a node ID to the `bst` class which is initialized to 0 in the `bst` constructor and updated everytime a new node is added to the binary search tree. Update `bst::insert()` to do the latter and to pass the updated value along to the `bst::node` constructor.

With respect to the parent pointer, be aware that `bst::insert()` is a recursive function which does not have access to the parent when processing a node. You must therefore set the parent pointer as you ascend out of the recursion.

<table><colgroup><col style="width: 50%" /><col style="width: 50%" /></colgroup><tbody><tr class="odd"><td><div class="title">Note</div></td><td>When you reach the parent, you have access to the root of the subtree just processed.</td></tr></tbody></table>

Update `bst::node::print()` to output the node ID, its key, the parent ID, and the left and right subtree IDs (if they exist).

Add a specialized version of `bst::node::print()` for string data. Make the key width 20. Temporarily modify `Prog7.cpp` to read string data, then process `test_string.txt` and make sure you understand the output produced by Modes 1 and 2.

#### Changing Data Types

The main function in `Prog7.cpp` defaults to using ints for the `bst`. You can edit the `data_t` typedef to use different types for testing. Your `bst` should work for any reasonable type since it is templated.

### Mode 2

A quick look should convince you that this is a matter of adding an iterator subclass to the `bst` class. Here is how you do that.

Add public member functions `bst::begin()` and `bst::end()` which respectively return an iterator that points to the node which holds the smallest key and an iterator that contains a NULL pointer which indicates the binary search tree has been exhausted (analogous to the first node and the dummy value at the end of a sequence container). Recall that the smallest key is found in the leftmost node. You must find it by iteratively searching through the sequence of left children starting at the root of the tree.

The `bst.h` file lists a number of iterator operators that must be included.

-   `++ PRE increment` for an inorder move to the next node

-   `*` for dereferencing the iterator and thus accessing the node key

-   `==` and `!=` for comparing iterators

The `++ PRE increment` operator is by far the most complicated code you will write in this lab assignment. Before you even think about programming it, make sure you know how to carry out an inorder traversal with focus on how to advance from one node to the next. Be aware that you will NOT be using recursion. Each call to `bst::iterator::operator++` must explicitly update the underlying node pointer to the next node.

HINT: The `bst::begin()` function should be the node pointer to the leftmost node in the binary search tree. The next node is the parent of that node. The next node after that is the leftmost node in that parent’s right subtree (if it has any). You then return to that node’s parent before you process it’s right subtree. Eventually, you return to the root of the tree before you descend into the main right subtree. See the pattern? Be very careful when you ascend out of the tree when the last node has been processed. You must detect and handle an attempt to access the parent of the root node since it doesn’t exist. If you forget to this, your code will seg fault. Guaranteed.

When the `bst::iterator` subclass has been implemented, the `print_inorder()` function in `Prog7.cpp` will output the content of the binary search tree in lexicographically sorted order as shown above. Make sure your code produces a comparable result for the `test_string.txt` data.

### Mode 3

A quick look should convince you that this is a matter of adding two public member functions to the `bst` class, namely, `bst::lower_bound()` and `bst::upper_bound()` which both take a key as input and return an iterator corresponding to a node in the binary search tree. Here is how these functions are suppposed to work.

The `bst::lower_bound(key)` function returns an iterator to the first node in the binary search tree whose key is not less than the given key, i.e., key ≤ lower\_bound. If the key exists, the returned iterator points to that node. If the key does not exist, the returned iterator points to the first node whose key value is greater.

<table><colgroup><col style="width: 50%" /><col style="width: 50%" /></colgroup><tbody><tr class="odd"><td><div class="title">Warning</div></td><td>Your search must be based on explicitly traversing the appropriate path from the root to the target node. Do not use an iterator based inorder traversal.</td></tr></tbody></table>

The `bst::upper_bound()` function returns an iterator to the first node in the binary search tree whose key is strictly greater than the given key, i.e., key &lt; upper\_bound. If the key exists, the returned iterator points to the next node when performing an inorder traversal. If there is no next node, the returned iterator should represent a NULL pointer.

<table><colgroup><col style="width: 50%" /><col style="width: 50%" /></colgroup><tbody><tr class="odd"><td><div class="title">Warning</div></td><td>Your search must be based on explicitly traversing the appropriate path from the root to the target node. Again, do not use an iterator based inorder traversal.</td></tr></tbody></table>

HINT: `bst::lower_bound()` and `bst::upper_bound()` are nearly identical. Only the comparison operator is different.

The iterators returned from `bst::lower_bound()` and `bst::upper_bound()` are passed to `print_inorder()` which outputs the corresponding sequence of data stored in the binary search tree.

### Mode 4

A quick look should convince you that this is a matter of updating the iterator subclass. Here is how you do that.

Add public member functions `bst::rbegin()` and `bst::rend()` which respectively return an iterator that points to the node which holds the largest key and an iterator that contains a NULL pointer which indicates the binary search tree has been exhausted. Recall that the largest key is found in the rightmost node. You must find it by iteratively searching through the sequence of right children starting at the root of the tree.

Add iterator `pass[operator — PRE]` decrement for an inorder move to the previous node. If you understand how the forward operator works, then it should be easy for you convert it to produce the needed reverse operator.

<table><colgroup><col style="width: 50%" /><col style="width: 50%" /></colgroup><tbody><tr class="odd"><td><div class="title">Note</div></td><td>Unlike the STL, we are not implementing a separate reverse iterator subclass. This is simply adding a decrement operator to the iterator subclass.</td></tr></tbody></table>

## Grade Rubric (150+25 points)

### Mode 1 (30 points)

-   20: Definition and use of `bst::node` ID information

-   00: Specialized string version of `bst::node::print()`

-   10: Correct output

### Mode 2 (80 points)

-   10: Definition of `bst::iterator` subclass

-   10: Implementation of constructors, and operators `*, ==, !=`

-   30: Implementation of `operator++()`

-   10: Implementation of `bst::begin()` and `bst::end()`

-   20: Correct output

### Mode 3 (40 points)

-   15: Implementation of `bst::lower_bound()` member function

-   15: Implementation of `bst::upper_bound()` member function

-   10: Correct output

### Mode 4 (25 extra points)

-   15: Implementation of `operator--()`

-   10: Correct output

Last updated 2023-11-06 10:35:36 -0500
