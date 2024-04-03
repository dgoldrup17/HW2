# Floating Point Overflow Detector

## Introduction

This C++ program is designed to detect potential floating-point overflow in a given loop bound and loop counter values. It utilizes the IEEE-754 floating-point representation to analyze the bit patterns of the input values and determine if overflow is likely to occur.

## Implementation

### Dependencies
- `iostream`: Input/output stream handling.
- `bitset`: Allows manipulation of bits in a fixed-size sequence.
- `sstream`: String stream processing.
- `cmath`: Provides mathematical functions.

### Functions
- `floatToBinary`: Converts a floating-point number to its IEEE-754 binary representation.
- `parseScientificNotation`: Parses floating-point input in scientific notation. It converts the scientific notation to a floating point value in order for the user to be able to input a value in scientific notation.
- `calculateThreshold`: Calculates the threshold for potential overflow based on the difference between exponents of the loop bound and loop counter values. It also checks to see if either loopbound or loop counter (increment) is at the threshold for floating point number to lose precision causing overflow.

### Main Functionality
- The program takes two command-line arguments representing the loop bound and loop counter.
- It converts the input values to their IEEE-754 binary representations and displays them.
- The threshold for potential overflow is calculated based on the difference between exponents.
- If overflow is detected, a warning message along with the overflow threshold value is displayed.

## Usage

### Compilation
Compile the program using a C++ compiler. For example:
g++ -I ./ *.cpp -- Used this command in the file that has the program: on Terminal: 1. cd Documents 2. cd HW2 3. g++ -I ./ *.cpp 
Then execute with this: ./a.out 1e+08 1.0 --- (can use other inputs for loop bound and loop counter as command line arguments)
