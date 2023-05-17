# Mandelbrot Set Generator

This is a simple C++ program that generates an image of the Mandelbrot Set.

## Overview

The program performs the following steps:

- Defines a color palette.
- Iteratively computes the Mandelbrot Set for each pixel.
- Writes the results to a `.ppm` file.
- Outputs processing progress to the console.

## Code Details

### File Structure

- The entire program is contained in a single file.

### Constants

- `WIDTH` and `HEIGHT` set the resolution of the image.
- `MAX_ITER` is the maximum number of iterations to be done for each point.
- `PALETTE_SIZE` defines the size of the color palette.

### Color Representation

- The program uses the struct `Color` to represent colors. The color palette is defined as an array of these structs.
- The `getColor()` function is used to map a number of iterations to a color in the palette.

### Calculation of the Mandelbrot Set

- The function `value()` computes the number of iterations needed for a point to escape the Mandelbrot Set. It is used 
to determine the color of a given pixel.

### Image Creation

- The image is created as a `.ppm` file.
- The pixel values are written to the file in a nested loop that iterates over the width and height of the image.

### Progress Reporting

- The program also reports the processing progress to the console. This is calculated as a percentage of the width of 
the image that has been processed.

## Compilation and Execution
- The most automated option would be to use the provided `run.sh` script. The script will automatically build the 
program and convert the output file to a usable TIFF format and delete the PPM after conversion to save space. 
Before you run the script, make sure that VIPS library is 
installed on your system.  You can install it on Ubuntu with the following command:
```bash 
sudo apt-get install libvips
 ```
Then you can run the script using 
```bash
./run.sh
```

- You can also manually compile the program with a C++ compiler. For example, using `g++`:
```bash
g++ -o mandelbrot mandelbrot.cpp
```
Then run it:
```bash
./mandelbrot
```

## Output
- The program will output the image of the Mandelbrot Set to a file named 'output.ppm'. 
- The progress of the image processing is also reported in the console.

## Requirements
- C++ compiler
- Filesystem access to write the output file

Please note that generating high-resolution images of the Mandelbrot Set can be computationally intensive and may 
take some time, depending on the capabilities of your hardware.