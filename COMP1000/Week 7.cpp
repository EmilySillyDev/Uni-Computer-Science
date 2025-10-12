#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

void task1() {
    std::ifstream csv("COMP1000/Week 7/csvInfo.csv");

    if (!csv.is_open()) {
        std::cerr << "There was a problem opening 'csvInfo.csv'" << std::endl;

        if (csv.fail()) {
            std::cerr << "Errors: " << std::strerror(errno) << std::endl;
        }

        return;
    }

    std::string lineBuffer;
    
    while (getline(csv, lineBuffer)) {
        std::string itemBuffer;
        std::vector<std::string> itemList;

        for (char& c: lineBuffer) {
            switch (c) {
                case ',':
                    itemList.push_back(itemBuffer);
                    itemBuffer = "";
                    break;

                case ' ': // Handle trailing spaces after commas
                    if (itemBuffer != "")
                        itemBuffer += c;

                    break;

                default:
                    itemBuffer += c;
                    break;

            }
        }

        // Last item isn't delimited (unless there's a trailing comma, which shouldn't happen)
        itemList.push_back(itemBuffer);

        std::cout << "Name: " << itemList[0] << ", ";
        std::cout << "Age: " << itemList[1] << ", ";
        std::cout << "City: " << itemList[2] << std::endl;
    }

    csv.close();
}

int main() {
    task1();

    return 0;
}