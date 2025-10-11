#include <cmath>
#include <iomanip>
#include <iostream>
#include <fstream>

void task1() {
    std::ofstream myFile("myFile.txt");
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

int main() {
    task1();

    return 0;
}