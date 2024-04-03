#include <iostream>
#include <bitset>
#include <sstream>
#include <cmath>

// Function to convert a floating-point number to its IEEE-754 bit representation
std::string floatToBinary(float value) {
    std::bitset<sizeof(float) * 8> bits(*reinterpret_cast<unsigned long*>(&value));
    std::ostringstream oss;
    oss << bits[31]; // Sign bit
    oss << ' ';
    for (int i = 30; i >= 23; --i) // Exponent
        oss << bits[i];
    oss << ' ';
    for (int i = 22; i >= 0; --i) // Mantissa
        oss << bits[i];
    return oss.str();
}
// Function to parse floating-point input in scientific notation
float parseScientificNotation(const std::string& str) {
    std::istringstream iss(str);
    float value;
    iss >> value;
    return value;
}



//float calculateThreshold(float loopBound, float increment) {
    // If either the loop bound or the increment is greater than or equal to 2^24, return 2^24
  //  if (loopBound >= std::ldexp(1.0f, 24) || increment >= std::ldexp(1.0f, 24)) {
    //    return std::ldexp(1.0f, 24); // Set the exponent to 24 to represent 2^24
    //} else {
      //  return -1; // No overflow
    //}
//}

float calculateThreshold(float loopBound, float increment) {
    // Extract the exponent bits and subtract the bias to obtain the actual exponent
    int exponentLoopBound = ((*(reinterpret_cast<unsigned int*>(&loopBound)) >> 23) & 0xFF) - 127;
    int exponentIncrement = ((*(reinterpret_cast<unsigned int*>(&increment)) >> 23) & 0xFF) - 127;

    // Check if either exponent is 24 or more
    if (exponentLoopBound >= 24 || exponentIncrement >= 24) {
        // If either exponent is 24 or more, return the value of 2^24 as the overflow threshold
        return std::ldexp(1.0f, 24);
    } else {
        // Calculate the difference between the exponents of loopBound and increment
        int exponentDiff = std::abs(exponentLoopBound - exponentIncrement);

        // Check if the difference between the exponents is 24 or more
        if (exponentDiff >= 24) {
            // If the difference between the exponents is 24 or more,
            // return the value of 2^24 as the overflow threshold
            return std::ldexp(1.0f, 24);
        } else {
            // Otherwise, return -1 to indicate no overflow
            return -1;
        }
    }
}





int main(int argc, char* argv[]) {
    std::cout << "\n";
    // Check if correct number of arguments are provided
    if (argc != 3) {
        std::cerr << "Usage: \n" << argv[0] << " loop_bound loop_counter\n";

        std::cerr << "loop_bound is a postive floating-point value" << std::endl;
        std::cerr << "loop_counter is a postive floating-point value" << std::endl;

        return 1;
    }

    // Parse command-line arguments
    float loopBound, increment;
    if (argv[1][0] >= '0' && argv[1][0] <= '9')
        loopBound = std::stof(argv[1]);
    else
        loopBound = parseScientificNotation(argv[1]);

    if (argv[2][0] >= '0' && argv[2][0] <= '9')
        increment = std::stof(argv[2]);
    else
        increment = parseScientificNotation(argv[2]);

    // Output IEEE-formatted bit representation of the values
    std::cout << "Loop bound: " << floatToBinary(loopBound) << std::endl;
    std::cout << "Loop counter: " << floatToBinary(increment) << std::endl;
    std::cout << "\n";

    float threshold = calculateThreshold(loopBound, increment);

    // Check for overflow
    if (threshold == -1) {
        std::cout << "There is no overflow!" << std::endl;
    } else {
       std::cout << "Warning: Possible overflow!" << std::endl;
        float threshold = calculateThreshold(loopBound, increment);
        std::cout << "Overflow threshold:" << std::endl;
        std::cout << "\t" << threshold << std::endl;
        std::cout << "\t" << floatToBinary(threshold) << std::endl;
    }
    return 0;
}

