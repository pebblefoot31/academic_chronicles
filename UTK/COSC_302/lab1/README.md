
# CS302 -- Lab Assignment 1 (80 pts: Spring 2024)

------------------------------------------------------------------------

### Getting motivated

Welcome to your first CS302 lab. The goal is for you to show that you master the data structures material covered in CS202. Emphasis is on their usage rather then their implementation.

------------------------------------------------------------------------

### Lab submission and due date

A tarball that contains Prog1.cpp, Support.h, and Support.cpp is due 11.59pm Tuesday Jan 30, 2024. The code must compile using the given makefile, so don't include it. As always, make sure you submit source code and not the executable. You will not be able to use grace days since this assignment is merely warm up. Once the deadline rolls around, time is up.

**NOTE**: The drop deadline is Jan 29. If you find this assignment exceedingly difficult, now is the time to drop CS302 and hone your C++/STL/Unix skills.

------------------------------------------------------------------------

### Programs you need to write

Write the following code. Give yourself ample time as the assignment may be more difficult than you first think.

-   Get a copy of lab1.tar from Canvas. This file contains skeleton files Prog1.cpp, Support.h, and Support.cpp, and a makefile for compiling them program into an executable. In addition, you are given a solution executable called sprog1 and data files weather\_TN.csv, weather\_SE.csv, and weather\_US.csv for cities in Tennessee, the South East and the entire United States. The solution executable showcases the functionality described next. When in doubt about what to do, run the code and study the output.
-   You are given comma-separated, weekly weather reports for a number of locations. Each weekly report contains the month (1-12) the data was recorded, the name of the city and state where the weather station was located, a three-letter geocode (e.g., TYS for Knoxville), the average amount of precipitation for the week in inches as well as the average temperature in degrees Fahrenheit.
    -   unix> cat weather_TN.csv

            1,Bristol/Jhnsn Cty/Kngsprt,Tennessee,TRI,0,34
            1,Chattanooga,Tennessee,CHA,0,40
            1,Clarksville,Tennessee,CKV,0,37
            1,Crossville,Tennessee,CSV,0,34
            1,Knoxville,Tennessee,TYS,0,36
            ...

    We will refer to the city, state, and geocode as a location and the month, precipitation and temperature as raw data. The assignment has two parts. Part 1 reads and writes weekly data. Part 2 extracts and writes monthly summaries. You will store location, raw data, and summary data in a database that also contains the functions needed to read, extract, and otherwise process everything using the data structures described below. NOTE: You MUST use these data structures to earn points.
-   For 40 points, write Prog1.cpp to have it check for a command line argument that specifies printing the weekly data followed by code that makes printing happen. This requires that you also update Support.h and Support.cpp to have them define and implement data structures and member functions needed by the location and rawdata structs and the database class. Add member function arguments and return data types as needed.
    -   Write location::operator&lt;() to order locations first by state and then by city.

    -   Write location::print() to output the location information with each line being 42 characters wide.

    -   Write database::init\_rawdata() to read and store the weekly data from a given datafile. Define and use a `vector< list<rawdata> >` data structure to hold the weekly data. The first index of this 2D data structure is unique to a location. The second index is for the data records associated with that location. Define and use a binary search tree that uses location as the key and an index into the raw data cache for the raw data. Abstractly,

            location_map(location,index) --> index
            rawdata_cache[index][...] --> output

    -   Write and use database::extract\_rawdata() to replace spaces with underscores and commas with spaces.

    -   Have the main() function instantiate and use a database object to read and print raw data as described above. When the command line option to do so is not specified, have main() proceed to works described next.

    -   Example output looks as follows:

            unix> ./Prog1 -rawdata weather_TN.csv

            ------------------------------------------
            Bristol/Jhnsn_Cty/Kngsprt, Tennessee (TRI)
            ------------------------------------------
                1  0.00    34
                1  0.67    37
                ...
               12  0.78    41
                1  1.09    43
               ...
            ------------------------------------------
            Nashville, Tennessee (BNA)
            ------------------------------------------
                1  0.00    39
                1  0.30    41
                ...
               12  2.17    44
                1  1.22    50

        Note that each city may have January data at the beginning and at the end of the year. This is because the last week of the year is labeled January. Somehow that made sense to the people who created the data. We will not question the logic.
-   For 40 points, update Prog1.cpp to initialize the monthly summary data before entering into an infinite loop that prompts the user for a location to report for. The location can be specified either as a state or geocode. If specified as a state, all locations for the state most be reported. Once again, this requires that you update Support.h and Support.cpp to have them define and implement needed data structures and member functions.
    -   Write summary::summary() to have it initialize the class data members.

    -   Write summary::operator+=() to have it incorporate a new weekly data record. This means updating the number of records seen, precipitation and temperature sums, as well as max and min values. Use the avg data members to store the sums.

    -   Write summary::print() to output monthly summaries. Use fields that are 5 characters wide for each data item, print floats using 2 decimal places and ints using 1 decimal place.

    -   Write database::init\_summary() to compute and store monthly summaries for each location. Define and use a `vector< vector<summary> >` data structure to hold this data. The first index of this data structure is once again unique to a location. The second index are the months for that location. To facilitate the search, define and use two hash maps, namely, one that uses state as the key and a binary search tree that contains geocodes as values, and one that uses geocode as the key and the corresponding location as the value. Abstractly,

            state_map(state,bst) --> geocode1, ..., geocodeN
            geocode_map(geocode,location) --> location
            location_map(location,index) --> index
            summary_cache[index][...] --> output

        In words, a state query produces a set of geocodes. Each geocode produces a location. Each location provides an index to a list of monthly summaries. Each summary knows how to print itself. A geocode query simply bypasses the first step.

    -   Write and use database::extract\_summary() to iterate thru the location\_map data structure and update the monthly summary data cache. When done iterating thru the raw data for a particular location, convert the precipitation and temperature sums to averages.

    -   Write and use database::print() to print monthly location summaries. If the target location is a state, push all associated geocodes onto a queue. If the target location is a geocode, simply push it onto the queue. Either way, use the geocodes stored by said queue to print the relevant information.

    -   Example output looks as follows:

            unix> ./Prog1 weather_TN.csv

            print> Tennessee
            ------------------------------------------
            Nashville, Tennessee (BNA)
            ------------------------------------------
            Jan:  0.00  1.42  0.56 :  26.0  50.0  39.7
            Feb:  0.28  1.79  1.12 :  31.0  50.0  43.5
            ...

            ------------------------------------------
            Knoxville, Tennessee (TYS)
            ------------------------------------------
            Jan:  0.00  1.45  0.70 :  27.0  46.0  37.3
            Feb:  0.14  3.09  1.78 :  29.0  47.0  41.5
            ...
            Dec:  0.64  2.28  1.38 :  41.0  43.0  41.8

            print> MEM
            ------------------------------------------
            Memphis, Tennessee (MEM)
            ------------------------------------------
            Jan:  0.00  1.42  0.52 :  32.0  51.0  42.5
            Feb:  0.11  2.03  1.39 :  39.0  55.0  47.5
            ...
            Dec:  0.49  2.18  1.62 :  40.0  46.0  43.0
            print> CTRL-D

        Hint: Unlike the raw data, which is ordered by location, the monthly summary state output is ordered by geocode. This is a result of loading the queue that produces the output with geocodes stored in alphabetical order.
-   When reading the assignment, try to create a mental picture of the data, how stored and handled. Better yet, make a simple sketch on a piece of paper. Nothing fancy. Just enough to wrap your head around the problem. You may get it the first time. You may need need to do it a couple of times.

### Grade rubric

NOTE 1: Code that doesn't compile and/or run will most likely be given a score of 0. Effort is nice but ultimately code has to work in the real world, and we don't have the time to debug when grading. So, make sure you have a correctly functioning executable for the program you submit. Verify your output against the solution exectuables. The TAs will do the same when grading. Note that simply matching the output doesn't guarantee full credit for an assignment. The code must be implemented correctly as well.

NOTE 2: Always follow the instructions given in lab assignments. Automated grading scripts will look for class definitions and functions. **You must therefore use naming conventions described**.

NOTE 3: Appropriate comments are expected for all your programs. Don't simply provide a literal translation of each line of code. In fact, don't provide a literal translation of any line of code. Comments should explain the computation. Imagine yourself looking at the code months or years from now. What would you need to know to figure out what's going on? Better yet, imagine someone else looking at the code now. What do they need to know to figure out what's going on?

#### Prog1 (80 points)

    *40: Correct rawdata output and use of required data structures
    *40: Correct summary output and use of required data structures

------------------------------------------------------------------------

Sun Jan 14 17:57:15 EST 2024
