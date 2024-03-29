COSC202 -- Lab Assignment 1

# COSC202 -- Lab Assignment 1 (100 pts: Fall 2023)

------------------------------------------------------------------------

### Getting motivated

WELCOME to your first CS202 lab. During the semester, you will be taken through a sequence of increasingly more difficult programming assignments. They will be challenging but matched to your programming skills which will become better and better as we go along.

Get started early. If you run into trouble, seek help from the TAs or the instructor (in that order). You can also post questions to the class using Piazza (public questions and answers must be conceptual, private questions to instructor and TAs can include code). The important thing is for you not to back yourself into a corner and get so frustrated that you give up. That said, if Lab 1 seems beyond your skill level, be aware that the deadline for dropping CS202 without a W is Aug 29, 2023.

------------------------------------------------------------------------

### Lab submission and due dates

Your friendly TAs will tell you how to submit a tar file with your work the first day in lab. Also see posting on Piazza. The due date for Prog1 is 11.59PM Thursday Sep 7, 2023. You submit either Prog1a.cpp, Prog1b.cpp or Prog1c.cpp. If submitting Prog1c.cpp, you must also submit Support.h and Support.cpp. More on these files below.

------------------------------------------------------------------------

### Getting Started

In CS202, you will write, compile and execute programs on computers that run Linux. This requires Unix proficiency. You went thru a Unix bootstrap in CS102, but in case you never quite got the hang of it, have forgotten what you learned, or have transferred from a school that wasn't Unix based, your first task is to work thru a Unix tutorial such as [tutorialspoint.com/unix](http://www.tutorialspoint.com/unix/). Unix will seem very complicated at first but you don't need to know all that many commands to get started. Then, as time goes by and you become more confident, you can branch out and familiarize yourself with other commands and tools.

There are many ways to edit files under Unix. Old timers prefer "vi" which is a screen-oriented editor. You should consider using a newer improved version called "vim" which is available for Macs and Windows computers. The above Unix tutorial has a short section on "vi" that outlines the basic commands for inserting and deleting text, moving up/down and across lines, etc (which is really all you need). Evautally, you will want to read the PDF manual available from [vim.org/docs.php](http://www.vim.org/docs.php) to learn how to do things more efficiently.

You need to figure out how to connect to a Hydra computer from your own computer. That way you can work from anywhere. You will also need to know how to copy files back and forth. There are many ways to do this. See posting on Piazza called "Guidelines for lab submissions". You can also ask the TAs and/or your classmates for suggestions. If you choose to do the labs on your own computer, be forewarned that your code must compile and run on a Hydra computer, as that's where it will be graded; if it doesn't, you will likely be assigned a score of 0 for the assignment. Missing header files are a typical source of problems. You may also run into name clashes. The best defense is to compile and execute your code on a Hydra computer before submitting and fixing any problems that crop up.

Before you attend lab, login to your EECS account and do the following:

-   Create a directory in your home directory called cosc202 (use lower case). Make sure that read and write access is disallowed for anyone but yourself.

        UNIX> mkdir ~/cosc202
        UNIX> chmod 700 ~/cosc202

    In case you wonder, most faculty and students refer to computer science courses as CSXXX but the official designation is COSCXXX. Expect intermingled references.

-   Create a subdirectory called cosc202/labs and within it, a subdirectory called lab1. Go to this last directory. Write a C++ program called "Hello" which prints "Hello world" to stdout. Use "vi" to create the cpp file and "g++" to compile the executable.

        UNIX> mkdir -p ~/cosc202/labs/lab1
        UNIX> cd ~/cosc202/labs/lab1
        UNIX> vi Hello.cpp
        ... enter the code ...
        (To learn how to insert text, save a file, and exit vi, read the tutorials above)
        UNIX> g++ -o Hello Hello.cpp
        UNIX> ./Hello
        Hello world

    As you can see, the only tricky bit is using "vi". If you want to understand what the mentioned commands do, use the "man" page system.

        UNIX> man man
        UNIX> man mkdir

    The first command displays a manual for how to use the manual. The second command tells you everything you need to know about creating a directory. You scroll thru multiple man pages using the "space" bar.

-   To make life easier for you, Hydra solution executables will be made available for all lab assignments. Sometimes you will also be given data files and source code skeleton files that you will modify. For lab1, download lab1.tar from Canvas and copy it to the home directory in your Hydra account, then unpack it as follows:

        UNIX> cd ~/cosc202/labs/lab1
        UNIX> tar xvf ~/lab1.tar
        UNIX> ls -1
        makefile
        sprog1a
        sprog1b
        sprog1c
        weather_TN.csv

    **WARNING:** The tar file extraction doesn't check if an extracted file exists with the same name in the target directory. Name clashes will result in the existing file being overwritten without warning. For that reason, you should always backup your work after you have started making changes. Same goes when you copy files between your own computer and the Hydra computer. Better safe than sorry!

    To help prevent problems on Hydra, any source code file given to you will be all lowercase with a .txt suffix to disinguish them from the .cpp file you create, e.g., "prog1.txt" vs "Prog1.cpp". Solution executables will likewise be all lowercase and prefixed by the letter "s", e.g., "sprog1" vs "Prog1". NOTE: MacOS doesn't distinguish between upper and lowercase named files, so that difference alone will not suffice. Windows may or may not be behave the same way.

### Assignment Details

Next, you will be walked through three versions of Prog1 called Prog1a, Prog1b and Prog1c. Submit that last version you complete. Ideally, that will be Prog1c.

-   **Prog1a -- 20 pts**

    Write a program called "Prog1a" that reads weather data for a handful of TN cities. Make no assumptions about how many cities there are or what their names are. You determine that from the data itself which is provided in the comma-separated-value file weather\_TN.csv which contains weekly reports. Each weekly report contains the month (1-12) the data was recorded, the name of the city and state where the weather station was located (we will revisit this data for all 50 US states later), a three-letter geocode (e.g., TYS for Knoxville), the average amount of precipiation for the week in inches as well as the average temperature in degrees Fahrenheit.

    Program Prog1a must read this data into variables of the following data types: month (int), city, state, and geocode (strings), precipitation (float) and temperature (int). Use std::getline() to read one line at a time. Scan through the text string and replace space characters (' ') with underscores ('\_') and commas (',') with space characters (' '). Then use a stringstream to extract the data and print it to stdout.

        unix> cat weather_TN.csv | head -5
        1,Bristol/Jhnsn Cty/Kngsprt,Tennessee,TRI,0,34
        1,Chattanooga,Tennessee,CHA,0,40
        1,Clarksville,Tennessee,CKV,0,37
        1,Crossville,Tennessee,CSV,0,34
        1,Knoxville,Tennessee,TYS,0,36

        unix> ./Prog1a < weather_TN.csv | head -5
        1 Bristol/Jhnsn_Cty/Kngsprt Tennessee TRI 0 34
        1 Chattanooga Tennessee CHA 0 40
        1 Clarksville Tennessee CKV 0 37
        1 Crossville Tennessee CSV 0 34
        1 Knoxville Tennessee TYS 0 36

    To understand more about the command syntax, read the "Unix - Pipes & Filters" section of the Unix tutorial above. If you don't know what stringstreams are or how they work, now is a good time to learn. [cplusplus.com/reference/sstream](http://www.cplusplus.com/reference/sstream/). You will not be given explict references like this again. If you see a Unix command that you don't know what does, type "man commandname" on a Unix computer. This produces the man-page (manual) for the command.

-   **Prog1b -- 30 pts**

    Write a program called "Prog1b" which is a simple rewrite of "Prog1a". Create a struct called "location" that contains the city, state, and geocode information as well as a struct called "data" that contains the month, precipitation and temperature data. Move the code for extracting data from the text string read from weather\_TN.csv into a function whose signature is "void extract\_values (string &, location &, data &)". The first argument is the unprocessed text string, the second and third arguments are the similar named structs for returning the extracted data values. The main program should call this functions and then print the data like before. The Prog1b output is indistinguishable from the Prog1a output. The difference is merely with respect to how it is produced.

        unix> ./Prog1b < weather_TN.csv | head -5
        1 Bristol/Jhnsn_Cty/Kngsprt Tennessee TRI 0 34
        1 Chattanooga Tennessee CHA 0 40
        1 Clarksville Tennessee CKV 0 37
        1 Crossville Tennessee CSV 0 34
        1 Knoxville Tennessee TYS 0 36

-   **Prog1c -- 100 pts**

    Write a program called "Prog1c" which reports monthly total, average, max and min precipitation amounts as well as monthly average, max and min temperature values per city. The program will consist of three files called "Prog1.cpp", "Support.h" and "Support.cpp". More on their content below.

    **Support.h**: Add three class definitions to this file, namely, a struct called "location", a struct called "data" and a class called "summary". The two structs were created in Prog1b, so you simply move them here. The summary class is new.

    Update the location struct to include member function empty() which returns true if the geocode string member has not been set, member function set\_geocode(const char \*) which assigns the C-style character string given to the geocode string member, and comparison operator==() which returns true if the right-hand side location argument has the exact same geocode.

    Define the summary class to have the following public member functions: default constructor, constructor that takes a location object reference as its argument, getter function "get\_station()" which returns a location object reference, function "incorporate\_data(const data &)" which updates the private data members described next given a data object reference, and functions "print\_station()" and "print\_data()" which print station and data information to stdout as shown below.

    All summary class data variables must be kept private. These include a location object called station, and vector-arrays for holding monthly total, max and min precipitation and temperature data. You also need a vector-array for keeping track of the number of the weekly weather reports incorporated per month, so you can calculate monthly averages. Determine whether to use ints or floats for these vector-arrays by looking at the weather data.

    **Support.cpp**: Place the code for the member functions defined by the two structs and the class in Support.h.

    **Prog1c.cpp**: Make a copy of Prog1b.cpp, strip code that has been moved to Support.h and Support.cpp, update the header-file include list, and update the main function as follows.

    Check for command-line arguments. When Prog1c is executed without one, weather summaries are produced for all cities. When Prog1c is given a geocode that matches a city, only the weather summary for that city is produced. Each city report starts with the city name, state and geocode printed in a header consisting of 42 dashes above and below. This is followed by precipitation and temperature data for each month. The header is produced by summary::print\_station(). The data is produced by summary::print\_data().

        unix> ./Prog1c TYS < weather_TN.csv 
        ------------------------------------------
        Knoxville, Tennessee (TYS)
        ------------------------------------------
        Jan:  2.76  0.55  1.29  0.00 :  35  42  27
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

    Too many commandline arguments (more than 1) must produce a meaningful error message that says how to execute the program. Optional commandline arguments should be shown in \[ \].

        unix> ./Prog1c TYS BNA < weather_TN.csv 
        usage: ./Prog1c [geocode] < datafile

    Before you can print any summary report, you must read and store a summart of the weekly report data. Update the while-loop used to read data from the given csv file to follow data value extraction by a search for the station in a vector-array that holds station summaries. If the station has not been seen before, instantiate a summary object with the new station information (this is where the non-default location constructor comes into play) and push it onto the back of the vector-array holding station summaries. This must of course have been declared before you start reading data. Keep track of the station index and use the summary::incorporate\_data() member function to increase the weekly report count for the approppriate month as well as the precipation sum, max and min values.

    NOTE: In order for summary::incorporate\_data() to work, the summary constructor needs to initialize the data members appropriately. That is, all vector-arrays need be 12 elements long. Those holding sums should be initialized to 0. Those holding max values should be initialized to a value no greater than the largest value seen in the data (e.g., 0). Those holding min values should be initialized to a value larger than one seen in the data (e.g., 100).

-   **Postamble** Once you get the hang of Unix, Prog1c is by far the most difficult part of the lab. Use reference guides such as [cplusplus.com](http://www.cplusplus.com/) to help you with C++ library function syntax and use. There is also a C++ tutorial in the documentation section.

    When reading the assignment, try to create a mental picture of the data, how stored and handled. Better yet, make a simple sketch on a piece of paper. Nothing fancy. Just enough to wrap your head around the problem. You may get it the first time. You may need need to do it a couple of times.

### Grade Rubric

NOTE 1: Code that doesn't compile and/or run will most likely be given a score of 0. Effort is nice but ultimately code has to work in the real world, and we don't have the time to debug when grading. So, make sure you have a correctly functioning executable for the program you submit. Verify your output against the solution exectuables. The TAs will do the same when grading. Note that simply matching the output doesn't guarantee full credit for an assignment. The code must be implemented correctly as well.

NOTE 2: Always follow the instructions given in lab assignments. Automated grading scripts will look for class definitions and functions. **You must use naming conventions described**.

NOTE 3: Appropriate comments are expected for all your programs. Don't simply provide a literal translation of each line of code. In fact, don't provide a literal translation of any line of code. Comments should explain the computation. Imagine yourself looking at the code months or years from now. What would you need to know to figure out what's going on? Better yet, imagine someone else looking at the code now. What do they need to know to figure out what's going on?

NOTE 4: You get points for ONE of the three Prog1 cases below. That is, if you submit a solution for Prog1a, then you can at most earn 20 points while for Prog1b and Prog1c you can earn 30 points and 100 points, respectively.

#### Prog1a (20 points)

    *10: Correct output (requires reading, converting and writing data)
    *10: Stringstream based value extraction

#### Prog1b (30 points)

    *10: Correct output (requires reading, converting and writing data)
    *10: Stringstream based value extraction
    *05: Struct location, struct data
    *05: Function extract_values()

#### Prog1c (100 points)

    *20: Correct output (requires reading, converting and writing data)
    *10: Stringstream based data value extraction
    *10: Command line argument parsing and usage
    *20: Struct location, struct data incl. member function implementation
    *30: Class summary incl. member function implemention
    *10: Building vector-array city summaries

------------------------------------------------------------------------

Tue Aug 22 12:55:34 EDT 2023
