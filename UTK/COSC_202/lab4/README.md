# COSC 202 — Lab Assignment 4

Table of Contents

-   [Getting Motivated](#_getting_motivated)
-   [Lab Submission](#_lab_submission)
-   [Assignment Details](#_assignment_details)
    -   [Passwords and Salted-Hashing](#_passwords_and_salted_hashing)
    -   [Getting Started](#_getting_started)
    -   [Grade Rubric (125) points](#_grade_rubric_125_points)

## Getting Motivated

Everybody knows passwords are used to control account access. In this lab, you will implement a simple salted-hash method for creating and using encrypted passwords.

Technically, encryption refers to the process of encoding information into ciphertext that intended recipients can decode back into the original readable form. Rather than doing that, we will apply hashing which is an irreversible (one-way) cryptographic process that cannot be undone. A better description might be to say that we will scramble the password. We will consider these terms interchangeable here.

## Lab Submission

Your tar file must contain the following files:

-   Prog4.cpp

In order to earn points, the code must compile and produce output as described below.

## Assignment Details

The lab4.tar file contains:

-   Prog4.cpp

    -   Skeleton file that you must complete. Do not change names of functions or variables. Do not add functions not asked for.

-   makefile

    -   For creating a Prog4 executable

-   sprog4

    -   Solution executable

-   Logins

    -   Program to produce random usernames and passwords.

-   Corrupt

    -   Program to corrupt a subset of usernames and passwords.

-   logins1.txt and logins1X.txt

    -   Example input files

### Passwords and Salted-Hashing

Passwords are not stored as plain text. This prevents system administrators and bad actors from seeing what they are. The latter is important in case hackers obtain a copy of the password file. Real-world password management is hopefully more sophisticated than what you will implement in this lab, but it does do the job of encrypting passwords. We will use the cyclic-shift hash function for strings covered in class (SHL=5, SHR=27) to convert each password into a number which we then convert to a readable hex string that we can read and convert back to a number.

HINT: See `std::hex` in the `ios` section of <https://www.cplusplus.com>.

As an example, let’s encrypt the password "qwerty" which apparently is commonly used \[sic\]. The first hash is the unsigned long produced by our hash function which has been stripped of the table size modulo operation (we are interested in the actual hash, not a table index). The second hash is the equivalent hexadecimal number. COSC230 covers how to do the conversion manually, but that’s irrelevant here. The `std::hex` operator can do it for you. If you didn’t read the `ios` section of <https://www.cplusplus.com> mentioned above, do it now.

    username: cs202
    password: qwerty
    hash:     3919861497
    hash:     e9a456f9

This is all good and well, except with the password being commonly used, someone else might have decided to use it, so now we have identical entries in the password file. A simple solution consists of salting the password with random characters before computing the hash. These characters can be added before the password, e.g., "sa1tqwerty", after the password, e.g., "qwertysa1t", or interspersed with the password. We will use the second method of appending it. Ideally, a cryptographic random number generator is used to produce the salt, but we will use a fixed word that we garble. More on this below. For now, we will keep things simple and use "vols". This is no different than if the user had chosen "qwertyvols" as their password.

    username: cs202
    password: qwerty
    salt:     vols
    hash:     4110272695368760
    hash:     e9a456feffc38

Since the salt isn’t random, it does not prevent "qwerty" from being repeated. For our purposes, we will achieve randomness by applying the username to modify the salt. While this is not random, it likely produces a unique result since usernames are unique. We could make the salt equal to the username but that’s not fun. Instead, we extract and add the three least-significant bits of a username character to a salt character. If the result is not alphanumeric, then we set the salt character equal to `'*'`. We iterate thru the salt and username strings. If the salt is longer than the username, we reuse the username characters from the beginning.

HINT: You can extract the three least-significant bits using bit-logic, e.g., `username[i] & 0x7`, and you can repeat username characters by applying modulo artithmetic to the username indexing, i.e., `username[i%username.size()]`.

In order to understand what is going on, it helps to know how the ASCII character set is encoded. At the unix command line, type man ascii. The first table that appears shows the octal encoding. If you are not familiar with this concept, think of it as numbers for which 8 and 9 don’t exist. The rows in the octal ASCII table thus represent the numbers `000, 001, …​, 007, 010, 011, …​, 017`, and so forth through `170, 171, …​, 177`. Since three bits can represent the decimal numbers `0, 1, …​ 7`, it should be clear that our username based modification of the salt merely amounts to adding the least-significant octal digit of a username character to a salt character.

HINT: You don’t need to convert to an octal representation. That’s merely for illustrational purposes. We manipulate the underlying bits.

    username: cs202
    password: qwerty
    salt:     vols --> yrns
    hash:     4110272696326840
    hash:     0xe9a456ffe9ab8

The salted-hash is thus the result of hashing "qwertyyrns". We will not worry about hashing being a many-to-one operation, meaning other usernames that use the same password might produce the same salted-hash result. But as mentioned above, that is unlikely.

We arrived at the new salt as follows.

    v=166, c=143: 166+3 -> y=171  (166+3=167+2=168+1=170+1=171)
    o=157, s=163: 157+3 -> r=162  (157+3=158+2=160+2=161+1=162)
    l=154, 2=062: 154+2 -> n=156  (154+2=155+1=156)
    s=163, 0=060: 163+0 -> s=163  (163+0=163)

Now we are ready to formulate how to establish and check user credentials. Given a new username and password, we produce the salted-hash as described above, then store the username along with the salt and the salted-hash in a table. When asked to check a username and a password for valid access, we look for the username in the table. If found, we produce a salted-hash for the password and compare it against the one stored for the username. We grant access only if they match.

How do we store all this information? In a hash table with the key being the username and the value being the salt and salted password. Since we will operate with (key,value) data, we will use the `std::unordered_map`. Now would be a good time for you read up on that data structure on <https://www.cplusplus.com> if you haven’t already done so.

### Getting Started

Implement Prog4.cpp as described below. Do not change names of functions or variables. Do not add functions not asked for. The provided makefile must be able compile your program.

Prog4 is centered around the following credentials struct and functions. The credentials struct holds the salt and the salted password hash and provides the functions and operators to set and compare these variables. The functions `write_hashtable()` and `read_hashtable()` handle creating and recreating the hash table that stored the login information.

    typedef unsigned long ulong;

    struct credentials {
      void set_salt(string &);
      void set_hash(string &);

      void operator=(const credentials &);
      bool operator==(const credentials &);

      string salt;
      ulong password_hash;
    };

    ostream &operator<<(ostream &, const credentials &);
    istream &operator>>(istream &, credentials &);

    typedef unordered_map hashtable;

    void write_hashtable(hashtable &, bool);
    void read_hashtable(hashtable &, bool);

#### Credentials (35 points)

Implement the credentials member functions and operators. The `set_salt()` function is given a username which it uses to garble the salt variable which should be initialized to "g0b1g0rAnge" each time the function is called. The `set_hash()` function salts the password, then uses the cyclic-shift hash function for strings covered in class (circular shift 5 bits) to encrypt the result.

-   `operator=()` copies the salt and the password\_hash.

-   `operator==()` returns true if the compared credential structs have identical password\_hash values.

-   `operator<<` reads salt and password\_hash from a file stream.

-   `operator>>` writes salt and password\_hash to a file stream.

-   The password\_hash is stored internally as an unsigned long but represented externally as a hex number.

HINT: You need to know how `std::hex` can be applied to input and output streams. See above.

HINT: The salt is printed in 10 character wide field.

#### `write_hashtable()` (25 points)

Implement the `write_hashtable()` function which creates a hash table that holds usernames and associated credentials. The function reads usernames and passwords from cin, creates a credential object by first setting the salt by applying `set_salt()` to the username and then the password\_hash by applying `set_hash()` to the password. Then it inserts a pair struct holding the username and the credentials object into the hash table. When cin has been exhausted, the hash table content is written to a file called "passwd.txt". You do this using iterators supplied by the `std::unordered_map` class. See <https://www.cplusplus.com> for details.

HINT: The username is printed in a 10 character wide field. The overloaded credentials output operator is used to print the credentials information. You must check that the output file could be opened for writing and report an error if not.

#### `read_hashtable()` (10 points)

Implement the `read_hashtable()` function which reads usernames and associated credentials from the "passwd.txt" file and inserts a pair struct into the given hash table. You must check that the input file could be opened for reading and report an error if not.

#### `main()` (15 points)

Implement the parts of the main function that checks for command line arguments, instantiates a hash table in the form of an `std::unordered_map`, and executes calls to `write_hashtable()` and `read_hashtable()` as appropriate. Program execution should be possible as shown below.

Command line option "-create" causes Prog4 to execute `write_hashtable()` and thereby produce the passwd.txt file that contains usernames and login credentials.

Command line option "-check" causes Prog4 to execute `read_hashtable()` which checks login credentials read from passwd.txt against those computed for data read from stdin.

Optional command line option "-load Z" where Z is a float greater than 0.0 and less than or equal to 1.0 (default value). This option sets the max\_load\_fraction for the hash table which controls when it is resized. See `std::unordered_map` for details.

#### Verbose mode (25 points)

Add an optional command line option "-verbose" that makes the program print the following details of its execution. Hash table resizing: size (hash table buckets in use), capacity (max bucket count), and load (fraction of buckets in use). Hash table content: buckets and their data.

HINT: See `std::unordered_map` for how to iterate bucket data lists using bucket iterators with `unordered_map::begin(size_type n)` and `unordered_map::end(size_type n)`.

    unix> cat logins1.txt
    gshort8    Mw<50pI0
    phinton2   udY+8l6z
    swolf2     Y3)+rRgu
    therring10 X}i8N(P5
    orivers6   B{DhZ83B
    mcarter6   h<g9PE!N
    qcaldwel23 8wCy6)-W
    vcox92     2$yZy?AK
    dgraham3   N@J2WW!w
    ehoffman34 5Ie%uI@r

    unix> ./Prog4 -create < logins1.txt

    unix> cat passwd.txt
    ehoffman34 l0i7m5sGqkj fdbef7f7fe000061
    dgraham3   k7d2g1wDrng cddbb6ffcddfbf66
    vcox92     m3i1h2xDugf deffefefdf000055
    qcaldwel23 h3c5k7wEpjf ff76f5fefffef864
    mcarter6   l3c3k5tGsjf afe8fdefbff00055
    orivers6   n2c7l2uGuif 9fafdeffdfefdf65
    phinton2   g0c7k7xCngf e0defef7f800005d
    therring10 k0g3i1xHogi fc5ad3fffe5b0068
    swolf2     j7i5m2uHukk ebce776debdf0058
    gshort8    n3b8i4rHqgl efffbdeff000005b

    unix> ./Prog4 -create -verbose < logins1.txt
    ** S =    0 N =    0 : load = 0.00
    ** S =    1 N =    2 : load = 0.50
    ** S =    2 N =    2 : load = 1.00
    ** S =    3 N =    5 : load = 0.60
    ** S =    4 N =    5 : load = 0.80
    ** S =    5 N =    5 : load = 1.00
    ** S =    6 N =   11 : load = 0.55
    ** S =    7 N =   11 : load = 0.64
    ** S =    8 N =   11 : load = 0.73
    ** S =    9 N =   11 : load = 0.82
    ** S =   10 N =   11 : load = 0.91

         0    2 mcarter6 orivers6
         1    1 swolf2
         2    2 vcox92 qcaldwel23
         3    0
         4    0
         5    1 gshort8
         6    0
         7    1 ehoffman34
         8    0
         9    2 phinton2 therring10
        10    1 dgraham3

    unix> ./Prog4 -create -load 0.5 -verbose < logins1.txt
    ** S =    0 N =    0 : load = 0.00
    ** S =    1 N =    2 : load = 0.50
    ** S =    2 N =    5 : load = 0.40
    ** S =    3 N =   11 : load = 0.27
    ** S =    4 N =   11 : load = 0.36
    ** S =    5 N =   11 : load = 0.45
    ** S =    6 N =   23 : load = 0.26
    ** S =    7 N =   23 : load = 0.30
    ** S =    8 N =   23 : load = 0.35
    ** S =    9 N =   23 : load = 0.39
    ** S =   10 N =   23 : load = 0.43

         0    0
         1    0
         2    1 orivers6
         3    0
         4    0
         5    2 dgraham3 mcarter6
         6    1 vcox92
         7    0
         8    0
         9    1 gshort8
        10    0
        11    1 ehoffman34
        12    1 phinton2
        13    0
        14    0
        15    1 qcaldwel23
        16    0
        17    0
        18    1 therring10
        19    1 swolf2
        20    0
        21    0
        22    0

    unix> cat login1X.txt
    fshort8    Mw<50pI0 <-- username: gshort8
    phinton2   udY+8l6z
    swolf2     Y3)+rRgu
    therring10 X}i8N(P5
    orivers6   B{DhZ83B
    mcarter6   h<g9PE*N <-- password: h<g9PE!N
    qcaldwel23 8wCy6)-W
    vcox92     2$yZy?AK
    dgraham3   N@J2WW!w
    ehofeman34 5Ie%uI@r <-- username: ehoffman34

    unix> ./Prog4 -check [-load Z] [-verbose] < logins1X.txt
    fshort8    bad username
    phinton2   access granted
    swolf2     access granted
    therring10 access granted
    orivers6   access granted
    mcarter6   bad password
    qcaldwel23 access granted
    vcox92     access granted
    dgraham3   access granted
    ehofeman34 bad username

#### Generating Data

You can generate more data with longer or shorter passwords using the Logins program. You can corrupt random usernames and passwords using the Corrupt program.

    unix> ./Logins 6 20 > logins2.txt

    unix> cat logins2.txt
    okennedy9  50@r2j4e6ND7QKohE2}e
    yhewitt27  0noFnSmMiF0O!a#PCXRl
    cberg81    h2s8#3Jyh4Of@XKqCd1g
    ylivings2  LQ9VKa61S8u$0KC1iNoD
    dbush8     wrBz8N?cosFy0s1Pa#mP
    jmorton74  q9oN6g<fsBM6ionjvKFk

    unix> ./Corrupt < logins2.txt
    okemnedy9  50@r2j4e6ND7QKohE2}e <-- username
    yhewitt27  0noFnSmMiF0O!a#PCXRl
    cberg81    h2s8#3Jyh4Of@XKqCd1g
    ylivings2  LQ9VKa61S8u$0KC1iNoD
    dbush8     wrBz8N?cosFy0s1Pa#mP
    jmorton74  q9*N6g<fsBM6ionjvKFk <-- password

### Grade Rubric (125) points

-   25: credentials: constructors, `operator==()`

-   10: credentials: input and output operators

-   25: write\_hashtable: create hashtable, write passwd.txt

-   10: read\_hashtable: read passwd.txt, recreate hashtable

-   15: main: command line parsing and error reporting

-   15: prog: check mode including usage and output

-   25: prog: verbose mode including usage and output

Last updated 2023-09-27 23:06:19 -0400
