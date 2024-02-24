# COSC 202 — Lab Assignment 2

Table of Contents

-   [Getting Motivated](#_getting_motivated)
-   [Lab Submission](#_lab_submission)
-   [Assignment Details](#_assignment_details)
    -   [Prog2 (120 points)](#_prog2_120_points)
-   [Grade Rubric](#_grade_rubric)

## Getting Motivated

In Lab 2, you will replace the vector-arrays used to store weather data for a handful of TN cities with a linked list and dynamically allocated arrays used to store weather for close to 300 hundred US cities. The point of the exercise (pun intended) is for you gain experience with the underlying pointer based data structures. Once again, get started early. You will be reusing some code from Lab 1 but most of it will be new.

## Lab Submission

Your tar file must contain the following files:

-   Prog2.cpp

-   Support.cpp

In order to earn points, the code must compile and produce output as described below.

## Assignment Details

The lab2.tar file contains:

-   Prog2.cpp

    -   Contains near complete code

-   Support.cpp

    -   An empty file that will ultimately contain the code you write

-   Support.h

    -   Header that you cannot edit.

-   makefile

    -   For creating a Prog2 executable as well as an sprog2 solution executable

-   Data files called weather\_TN.csv, weather\_SE.csv and weather\_US.csv,

    -   Contain data for Tennessee, multiple Southeastern states, and all 50 US states.

Your code must not make any assumptions about the number of states and cities present in a file, or the order in which data is stored. Expect the grade script to run randomized subsets of the data.

### Prog2 (120 points)

In the file Prog2.cpp, weather data will be read from a weather.csv file which contains data as described for Lab 1. The code will include the function for mapping spaces to underscores and replacing commas by spaces as well command line argument handling. A list object called city\_list is instantiated. New weather station data is added to this list incrementally using member function `list::insert()`. Implementing the class `list` will be your main task. You also need to implement member function `list::print()` which writes a summary to stdout identical to that produced by Prog1c. In order for Prog2.cpp to compile, you need to add the code for function `extract_values()` that you wrote for Prog1a. The only reason this code is not included here is that some students may not have submitted Lab 1 when this assignment is released.

<table><colgroup><col style="width: 50%" /><col style="width: 50%" /></colgroup><tbody><tr class="odd"><td><div class="title">Note</div></td><td>If you didn’t complete Prog1c, that is where you need to start. In particular, you will need the location and data structs. The <code>location::empty()</code> and <code>location::set_geocode()</code> member functions have been removed and a less-than comparison operator has been added as follows.</td></tr></tbody></table>

    struct location {
      string city;
      string state;
      string geocode;

      bool operator<(const location &) const;
      bool operator==(const location &) const;
      bool operator==(const string &) const;
    };

    struct data {
      int month;
      float precip;
      int temp;
    };

Less-than comparison operator `location::operator<()` is used to ensure city summaries are sorted first by state and then by city. You can modify a copy of Prog1c to work this logic out before you add the code to Support.cpp along with comparison operator `location::operator==()`.

There are two versions of the `location::operator==()`. The one that compares to a location is just like Lab 1. The one that compares to a string will return true if city, state, or geocode match the string given.

The big new data structure is the list class which defines a linked list. The private node structure defines how station information and weather data is stored. The vector-array used in Prog1c to hold the monthly data has been replaced by dynamicaly allocated arrays that you must maintain.

    class list {
      struct node {
        node(const location &n_station=location());
        ~node();

        void print_station();
        void print_data();

        location station;

        int *N;

        float *total_precip;
        float *max_precip;
        float *min_precip;

        int *total_temp;
        int *max_temp;
        int *min_temp;

        node *next;
      };

      public:
        list();
        ~list();

        void insert(const location &, const data &);
        void print(const char *);

      private:
        node *head;
    };

The node constructor uses the location object given to it to initialize the station. When one is not specified, the default location constructor is used. Memory is allocated for the many data arrays which are also initialized to appropriate values. Again, see Prog1c. The node destructor deallocates the data arrays. Node member functions `print_station()` and `print_data()` can be copied from Prog1c.

The list constructor allocates the sentinel head node. The list destructor iteratively deallocates all list nodes. Do this by unlinking and deallocating the first data node until none are left.

The list insert member function looks for a station in the linked list. The search stops if the station is found. When the station is not found, a new node is allocated and inserted into the linked list in the sort order determined by the less-than node comparison operator. Finally, the weather data is updated. Again, see Prog1c.

<table><colgroup><col style="width: 50%" /><col style="width: 50%" /></colgroup><tbody><tr class="odd"><td><div class="title">Tip</div></td><td>Scan thru the linked list. If the target station is found, end the search. Otherwise check if it should go before the next station stored in the linked list. If so, create and insert a new node for the target station and end the search. Otherwise, continue the search. If the search exhausts the list, create and insert a new node for the target station at the end of the list. The search thru the list must be based on node pointers. The data update must be based on a pointer to the target node.</td></tr></tbody></table>

The list print member function uses node member functions `print_station()` and `print_data()` to report city summaries to stdout. When the target\_location pointer given to this function is NULL, a summary is printed for all cities. Otherwise, the target\_location pointer could either specify a city, a state or a geocode for which summary should be printed. The function must be based on a search thru the list based on node pointers.

    unix> ./Prog2 < weather_SE.csv
    ------------------------------------------
    Birmingham, Alabama (BHM)
    ------------------------------------------
    Jan:  3.79  0.63  1.55  0.00 :  44  54  36
    Feb:  7.46  1.87  3.17  0.00 :  49  55  41
    Mar:  4.80  1.20  1.86  0.03 :  58  68  49
    Apr:  2.87  0.72  1.94  0.28 :  61  66  58
    May:  1.39  0.28  0.67  0.01 :  70  76  65
    Jun:  2.65  0.66  2.17  0.01 :  80  83  79
    Jul:  7.08  1.42  2.64  0.00 :  83  86  81
    Aug:  2.52  0.63  1.38  0.16 :  83  85  82
    Sep:  0.68  0.17  0.39  0.00 :  81  82  81
    Oct:  0.00  0.00  0.00  0.00 :  70  74  69
    Nov:  0.01  0.00  0.01  0.00 :  58  68  51
    Dec:  1.88  0.47  0.93  0.00 :  47  50  44

    [lots of output]

    ------------------------------------------
    Nashville, Tennessee (BNA)
    ------------------------------------------
    Jan:  3.39  0.56  1.42  0.00 :  39  50  26
    Feb:  4.46  1.12  1.79  0.28 :  43  50  31
    Mar:  3.65  0.91  1.88  0.01 :  55  65  45
    Apr:  0.52  0.13  0.27  0.00 :  59  67  52
    May:  2.37  0.47  1.42  0.00 :  67  74  62
    Jun:  3.91  0.98  2.01  0.00 :  79  83  75
    Jul:  6.28  1.26  4.70  0.00 :  82  85  80
    Aug:  6.44  1.61  2.15  0.87 :  81  83  79
    Sep:  1.64  0.41  1.33  0.00 :  78  80  77
    Oct:  0.43  0.09  0.36  0.00 :  67  70  66
    Nov:  0.15  0.04  0.13  0.00 :  55  66  47
    Dec:  5.72  1.43  2.39  0.42 :  41  44  39


    unix> ./Prog2 Knoxville < weather_SE.csv
    ------------------------------------------
    Knoxville, Tennessee (TYS)
    ------------------------------------------
    Jan:  4.21  0.70  1.45  0.00 :  37  46  27
    Feb:  7.12  1.78  3.09  0.14 :  41  47  29
    Mar:  2.32  0.58  1.13  0.28 :  54  63  43
    Apr:  1.78  0.44  0.71  0.26 :  58  67  50
    May:  4.04  0.81  1.42  0.19 :  67  72  63
    Jun:  4.17  1.04  3.11  0.00 :  77  80  74
    Jul:  4.80  0.96  3.71  0.00 :  81  84  80
    Aug:  2.33  0.58  1.00  0.10 :  81  83  80
    Sep:  0.91  0.23  0.56  0.00 :  78  79  77
    Oct:  0.18  0.04  0.14  0.00 :  65  68  64
    Nov:  0.27  0.07  0.16  0.00 :  53  64  46
    Dec:  5.51  1.38  2.28  0.64 :  41  43  41

## Grade Rubric

-   Prog2 (120 points)

    -   30: Correct output (requires data sorting and selection)

    -   10: Code: `location::operator<()`

    -   15: Code: list::node constructor and destructor

    -   15: Code: list constructor and destructor

    -   30: Code: list insert member function

    -   20: Code: list print member function

Last updated 2023-09-10 16:18:45 -0400
