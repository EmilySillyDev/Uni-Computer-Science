#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

void task1() {
    std::ofstream myFile("taskOutput/myFile.txt");

    if (!myFile.is_open()) {
        std::cerr << "There was a problem creating 'myFile.txt'" << std::endl;

        if (myFile.fail()) {
            std::cerr << "Errors: " << std::strerror(errno) << std::endl;
        }

        return;
    }

    myFile << "My Epic File" << std::endl << std::endl;

    myFile << "Here's a bunch of numbers!" << std::endl;

    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            myFile << std::left << std::setw(6) << (10 * y) + x + 1;
        }
        
        myFile << std::endl;
    }

    myFile << std::endl;

    myFile << "Here's pi to 5 decimal places: " << std::setprecision(6) << M_PI << std::endl;
    myFile << "Here's tau to 8 decimal places: " << std::setprecision(9) << M_PI * 2 << std::endl;

    myFile.close();
}

int digitToNumber(char c) {
    if (isdigit(c)) {
        // If it's a digit, offset the byte's value by that of the '0' char
        // This will give the value as an int, due to how chars are layed out
        return c - '0'; 
    }

    // It failed
    return -1;
}

void printIntVector(std::vector<int>& nums) {
    std::cout << "Here's all the numbers: ";

    for (const int& i: nums) {
        std::cout << i << ", ";
    }

    std::cout << "and... nothing else!" << std::endl;
}

void readInts(std::string &currentLine) {
    int numbuf = 0;
    bool empty = true;
    std::vector<int> numbers;
    
    for (char& c: currentLine) {
        int digit = digitToNumber(c);

        if (digit == -1) {
            // Given digit isn't a number, add buffer to vector if numbuf isn't empty
            if (empty) continue;
            numbers.push_back(numbuf);
            numbuf = 0;
            empty = true;
        } else {
            numbuf = (numbuf * 10) + digit;
            empty = false;
        }
    }

    // If there's no end character, just double check for anything in the buffer
    // If there's something, push it to the vector
    if (!empty) {
        numbers.push_back(numbuf);
        numbuf = 0;
        empty = true;
    }

    printIntVector(numbers);
}

void task2() {
    std::string currentLine;
    std::ifstream myFile("COMP1000/Week 6/Task2.txt");

    if (!myFile.is_open()) {
        std::cerr << "There was a problem creating 'myFile.txt'" << std::endl;

        if (myFile.fail()) {
            std::cerr << "Errors: " << std::strerror(errno) << std::endl;
        }

        return;
    }

    while (std::getline(myFile, currentLine)) {
        std::cout << currentLine << std::endl;

        // Does line start with 'positive ints:'?
        // If so, manually handle each of them
        if (currentLine.rfind("positive ints:", 0) == 0) {
            readInts(currentLine);
        }
    }

    myFile.close();
}

int main() {
    task1();
    task2();

    return 0;
}