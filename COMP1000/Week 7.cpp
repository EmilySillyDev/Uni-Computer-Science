#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

// Abstracted function to get seperate CSV strings out of a whole one
// Only returns a vector of strings, so no type information is inferred
// Instead, I'll just apply it after using the function
std::vector<std::string> getCSVData(std::string csv) {
    std::string itemBuffer;
    std::vector<std::string> itemList;

    for (char& c: csv) {
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
    return itemList;
}

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
        std::vector<std::string> itemList = getCSVData(lineBuffer);

        std::cout << "Name: " << itemList[0] << ", ";
        std::cout << "Age: " << itemList[1] << ", ";
        std::cout << "City: " << itemList[2] << std::endl;
    }

    csv.close();
}

typedef struct {
    std::string key;
    std::string value;
} KVPair;

typedef std::vector<KVPair> JSONInfo;

JSONInfo interpretJSON(std::string jsonLine) {
    std::vector<KVPair> buffer;

    if (jsonLine.size() < 2)
        return buffer;

    // Remove brackets
    jsonLine.erase(0, 1);
    jsonLine.erase(jsonLine.size() - 1);

    char c;
    std::string strBuffer;
    std::string nameBuffer;

    std::vector<std::string> readStrings;
    bool readingString = false;

    for (char &c : jsonLine) {
        switch (c) {
            case ':':
                break;

            case '"':
                readingString = !readingString;
                break;

            case ',':                
                break;

            case ' ':
                break;

            default:
                strBuffer += c;
        }
    }

    return buffer;
}


void task2() {
    std::ifstream json("COMP1000/Week 7/jsonLikeInfo.txt");

    if (!json.is_open()) {
        std::cerr << "There was a problem opening 'csvInfo.csv'" << std::endl;

        if (json.fail()) {
            std::cerr << "Errors: " << std::strerror(errno) << std::endl;
        }

        return;
    }

    char c;
    int bufferCount = 0;
    std::vector<std::string> buffer;
    std::vector<JSONInfo> values;
    
    while (json.get(c)) {
        if (c == '{') bufferCount += 1;

        int index = bufferCount - 1;
        if (index < 0) continue;
        if (buffer.size() < bufferCount) buffer.push_back(std::string(""));
        buffer[index] += c;

        if (c == '}') {
            JSONInfo pairs = interpretJSON(buffer[index]);
            values.push_back(pairs);
            buffer[index] = "";
            bufferCount -= 1;
        } 
    }

    for (JSONInfo &s : values){
        for (KVPair &kv : s) {
            std::cout << kv.key << " | " << kv.value << std::endl;
        }
    }

    json.close();
}

int main() {
    // task1();
    task2();
    return 0;
}