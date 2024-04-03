#include <iostream>
#include <bitset>
#include <sstream>
#include <cmath>


std::string floatToBinary(float value) {
    std::bitset<sizeof(float) * 8> bits(*reinterpret_cast<unsigned long*>(&value));
    std::ostringstream oss;
    oss << bits[31]; 
    oss << ' ';
    for (int i = 30; i >= 23; --i) // Exponent
        oss << bits[i];
    oss << ' ';
    for (int i = 22; i >= 0; --i) // Mantissa
        oss << bits[i];
    return oss.str();
}

float parseScientificNotation(const std::string& str) {
    std::istringstream iss(str);
    float value;
    iss >> value;
    return value;
}


float calculateThreshold(float loopBound, float increment) {
    int exponentLoopBound = ((*(reinterpret_cast<unsigned int*>(&loopBound)) >> 23) & 0xFF) - 127;
    int exponentIncrement = ((*(reinterpret_cast<unsigned int*>(&increment)) >> 23) & 0xFF) - 127;

    if (exponentLoopBound >= 24 || exponentIncrement >= 24) {
        return std::ldexp(1.0f, 24);
    } else {
        int exponentDiff = std::abs(exponentLoopBound - exponentIncrement);

        if (exponentDiff >= 24) {
            return std::ldexp(1.0f, 24);
        } else {
            return -1;
        }
    }
}



int main(int argc, char* argv[]) {
    std::cout << "\n";
    if (argc != 3) {
        std::cerr << "Usage: \n" << argv[0] << " loop_bound loop_counter\n";

        std::cerr << "loop_bound is a postive floating-point value" << std::endl;
        std::cerr << "loop_counter is a postive floating-point value" << std::endl;

        return 1;
    }

    float loopBound, increment;
    if (argv[1][0] >= '0' && argv[1][0] <= '9')
        loopBound = std::stof(argv[1]);
    else
        loopBound = parseScientificNotation(argv[1]);

    if (argv[2][0] >= '0' && argv[2][0] <= '9')
        increment = std::stof(argv[2]);
    else
        increment = parseScientificNotation(argv[2]);

    // Output bit representation of the values
    std::cout << "Loop bound: " << floatToBinary(loopBound) << std::endl;
    std::cout << "Loop counter: " << floatToBinary(increment) << std::endl;
    std::cout << "\n";

    float threshold = calculateThreshold(loopBound, increment);

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

