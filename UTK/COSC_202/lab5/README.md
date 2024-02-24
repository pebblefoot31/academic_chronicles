# COSC 202 — Lab Assignment 5

Table of Contents

-   [Getting Motivated](#_getting_motivated)
-   [Lab Submission](#_lab_submission)
-   [PPM File Format](#_ppm_file_format)
-   [Assignment Details](#_assignment_details)
    -   [The Centerpiece](#_the_centerpiece)
    -   [Read PPM Files (30 points)](#_read_ppm_files_30_points)
    -   [Write PPM Files (10 points)](#_write_ppm_files_10_points)
    -   [`gray()` (10 points)](#_gray_10_points)
    -   [`flip()` (10 points)](#_flip_10_points)
    -   [`lens()` (20 points)](#_lens_20_points)
    -   [Command Line Options](#_command_line_options)
    -   [Viewing PPMs](#_viewing_ppms)
-   [Grade Rubric](#_grade_rubric)

## Getting Motivated

In this lab, you will exercise file I/O and 2D array management in the context of digital image processing. That is, you will be reading an RGB image, apply one or more conversion steps, and then write the resulting RGB image to file.

## Lab Submission

Your tar file must contain the following files:

-   Prog5.cpp

-   Support.cpp

In order to earn points, the code must compile and produce output as described below.

## PPM File Format

Digital images are normally stored using some kind of compression such as JPEG or HEIC (Apple). We will use a simpler lossless format called PPM that has a simple ASCII header followed by RGB pixel values.

The format is covered in class, so this will be a brief summary. If you need more details, you can always look to [Wikipedia](https://en.wikipedia.org/wiki/Netpbm).

The PPM header starts with a so-called magic identifier, namely, the string "P6". This is followed by integers specifying the image width (number of columns) and the image height (number of rows) and the max data value (255 for all our images). This information should be read and written as formatted ASCII text. When reading, skip past any blanks until encountering the newline that separates the header from the data.

The image is stored using 24-bits per pixel which is broken into 3 8-bit unsigned integers for the red, green, and blue channels.

## Assignment Details

The lab5.tar file contains:

-   Prog5.cpp and Support.cpp

    -   Skeleton file that you must convert to working code.

-   Support.h

    -   Defines the content of Support.cpp

-   makefile

    -   For creating a Prog5 executable from your code

-   sprog5

    -   Solution executable

-   baboon.ppm, rocket.ppm, truck.ppm

-   Example PPM files

Implement the code as described. Do not change names of functions or variables. Do not add functions not asked for. The provided makefile must be able to compile your program.

### The Centerpiece

Prog5 is centered around the following definitions:

    struct RGB {
      RGB() { R=0, G=0, B=0; }
      uint8_t R, G, B;
    };

    class ppm {
      public:
        ppm();
        ppm(const ppm &);

        ~ppm();

        void read(const std::string &);
        void write(const std::string &);

        RGB *operator[](int);

        void set_bs(int);

        int get_Nrow() { return Nrow; }
        int get_Ncol() { return Ncol; }

      private:
        std::string magicid;

        int Nrow, Ncol;
        int maxvalue;

        int block_size;
        RGB *img;
    };

### Read PPM Files (30 points)

For 30 points, implement the code needed to read a PPM file. This includes the default constructor `ppm::ppm()` which sets the expected magic identifier to "P6" and the expected max value to 255, and the destructor `ppm::~ppm()` which frees up allocated memory. Member function `ppm::read()` opens a named file, reads the header information followed by the RGB data in `block_size` chunks (number of bytes), and then closes the file. Include error checking for succesfull file open, seeing the expected magic identifier and max value, and reading the expected amount of RGB data. The main function must instantiate and use a ppm image to read the ppm file.

### Write PPM Files (10 points)

For 10 points, implement the code needed to write a ppm file. If the input file is called `image.ppm`, the output file should be called `image_mod.ppm`.

HINT: Use string member functions `rfind()` and `insert()`.

Member function `ppm::write()` opens a correctly named output file, writes the header information followed by the RGB data. Include error checking for succesful file open. Write data to file in `block_size` chunks. The main function must be updated to call this function before exiting.

### `gray()` (10 points)

For 10 points, implement function `gray()` which converts an RGB image to its gray scale equivalent. Use the simple formula `Y=(R+G+B)/3`. Convert to float and then back to uint8\_t as needed to maintain proper gray scale values. Add the command line option handling needed to the main function to select this mode.

### `flip()` (10 points)

For 10 points, implement function `flip()` which flips an image from left-to-right. In order for this to work, implement and use overloaded `ppm::operator[]()` which returns a pointer to the first element in the i-th row allowing the caller to treat this as an array representing the row of pixels. Add the command line option handling needed to the main function to select this mode.

### `lens()` (20 points)

For 20 points, implement function `lens()` which applies the following spherical transformation which mimics the effect of placing a lens at the image center `(ci, cj)=(Nrow/2, Ncol/2)`. Make the max radius of the lens match the smaller image dimension to ensure that the lens is fully contained. That is, `rmax = min(Nrow/2,Ncol/2)`. Create a copy of the image: `ppm img_copy = img`. This requires that you implement the ppm copy constructor and have it make a deep copy of the data (allocate the needed memory and copy the RGB pixel values). With this in place, implement the below computation expressed in pseudo-code that you need to translate to `C++`:

    for each pixel (i,j) {
      (di,dj) = (i-ci, j-cj)
      r = sqrt(di**2 + dj**2)

      if (r < rmax) {
        z = sqrt(rmax**2 - r**2)
        (dzi,dzj) = (di/sqrt(di**2+z**2), dj/sqrt(dj**2+z**2))
        (bi,bj) = (1.0-1/rho)*(asin(dzi), asin(dzj))
        (ip,jp) = ((int)(i-z*tan(bi)+0.5), (int)(j-z*tan(bj)+0.5))
        img[i][j] = img_copy[ip][jp]
      }
    }

Above, `x**2` is x squared (`x*x`) and `(int)(x+0.5)` is a simplified floor function. Add the command line option handling needed to the main function to select this mode and set the value of `rho` which represents the refraction index of the lens (its ability to bend light).

### Command Line Options

The main program should accept the following command line options and print a usage error message as appropriate:

`unix> ./Prog5 [-gray] [-flip] [-lens z] [-bs nbytes] image.ppm`

That is, options gray, flip, lens and bs are all optional and can be applied together in any order. The second lens argument is a floating point number that specifies the value of rho. You must ensure that 1.0 &lt; rho ≤ 2.0. The second bs argument is an integer that specifies the block size used to read and write the ppm images. The default value should be set to 512.

See the accompanying pdf file with example output images for different command line options or use the solution executable to test outputs.

### Viewing PPMs

You might not be able to natively view PPM files with your browser or image viewer but it’s easy enough to convert it into a JPG file on the lab machines.

    unix> convert baboon.ppm baboon.jpg

## Grade Rubric

-   30: reading ppm file incl error checking

-   10: writing ppm file incl name change

-   10: convert RGB image to gray scale — incl command line option

-   10: apply left-to-right image flip — incl command line option

-   20: apply spherical lens transformation — incl command line option, ppm copy constructor

-   20: correct image output

Last updated 2023-10-13 18:47:44 -0400
