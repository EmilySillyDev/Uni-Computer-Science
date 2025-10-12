#include <cctype>
#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <exception>
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

class MalformedJSON : public std::exception {
    protected:
        std::string errorMessage;

    public:
        MalformedJSON(const char* msg) : errorMessage(msg) {}
        const char* what() const noexcept override {
            return errorMessage.c_str();
        }
};

KVPair extractKVPair(std::vector<std::string> strings) {
    if (strings.size() != 2)
        throw MalformedJSON("Invalid amount of values for KVPair");

    KVPair pair;

    pair.key = strings[0];
    pair.value = strings[1];

    return pair;
}

JSONInfo interpretJSON(std::string jsonLine) {
    JSONInfo buffer;

    if (jsonLine.size() < 2) // Malformed JSON, like just "{"
        return buffer;

    // Remove brackets
    jsonLine.erase(0, 1);
    jsonLine.erase(jsonLine.size() - 1);

    char c;
    int idx = 0;
    std::string strBuffer;
    std::string nameBuffer;

    std::vector<std::string> readStrings;
    bool readingString = false; // Are we reading a string?
    bool readingValue = false; // Are we reading the value?

    for (char &c : jsonLine) {
        switch (c) {
            case ':': // Delimiter for names
                if (readingString) { // Don't delimit in a string.
                    strBuffer += c;
                    break;
                }

                if (strBuffer == "") { // It's empty. Malformed JSON
                    throw MalformedJSON("No index before index delimiter");
                    break;
                }

                // Add to the tape and clear the buffer
                readStrings.push_back(strBuffer);
                strBuffer = "";

                // Now we're reading the value
                readingValue = true;

                break;

            case '"':
                readingString = !readingString;

                if (!readingString) {
                    readStrings.push_back(strBuffer);
                    strBuffer = "";
                }

                break;

            case ',':
                if (readingString) { // Don't delimit in a string.
                    strBuffer += c;
                    break;
                }

                // KVPairs delimiter
                buffer.push_back(extractKVPair(readStrings));
                readStrings.clear();
                strBuffer = "";
                readingValue = false;
                break;

            case ' ':
                if (readingString) { // Don't check in a string.
                    strBuffer += c;
                    break;
                }

                if (!readingValue && strBuffer != "") {
                    throw MalformedJSON("Space found in index");
                    break;
                }

                break;

            default:
                strBuffer += c;
        }

        idx++;
    }

    buffer.push_back(extractKVPair(readStrings));

    return buffer;
}


void task2() {
    std::ifstream json("COMP1000/Week 7/jsonLikeInfo.txt");

    if (!json.is_open()) {
        std::cerr << "There was a problem opening 'jsonLikeInfo.csv'" << std::endl;

        if (json.fail()) {
            std::cerr << "Errors: " << std::strerror(errno) << std::endl;
        }

        return;
    }

    char c;
    int bufferCount = 0; // Used to check depth of JSON structure
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
        std::string output;

        for (KVPair &kv : s) {
            std::string key = kv.key;
            std::vector<std::string> csv = getCSVData(kv.value);
            std::string value = "";

            key[0] = toupper(key[0]);

            if (csv.size() == 1) {
                value = csv[0];
            } else {
                for (std::string v: csv) {
                    value += v + ", ";
                }

                value.erase(value.size() - 2);
            }
            
            output += key + ": " + value + ", ";
        }

        output.erase(output.size() - 2);
        std::cout << output << std::endl;
    }

    json.close();
}

enum class LOG_TYPE {
    INFO,
    ERROR,
    WARNING,
    UNKNOWN
};

class ApplicationLog {
    protected:
        LOG_TYPE type;
        std::string message;
        std::string timestamp;
    public:
        ApplicationLog(LOG_TYPE type, std::string message, std::string timestamp): type(type), message(message), timestamp(timestamp) {} 
        ApplicationLog(): type(LOG_TYPE::UNKNOWN), message("No message provided"), timestamp("1970-01-01") {}
        ApplicationLog(std::string input) {
            // TYPE TIMESTAMP MESSAGE
            // Type and timestamp have no spaces, so we can delimit with those

            std::string buffer;
            std::vector<std::string> logInfo;

            for (char& c: input) {
                bool readingMessage = logInfo.size() == 2; // we have the type and timestamp, we're just getting the message now

                if (c == ' ' && !readingMessage) {
                    logInfo.push_back(buffer);
                    buffer = "";
                    continue;
                }

                buffer += c;
            }

            logInfo.push_back(buffer);
            
            std::string type_s = logInfo[0];
            std::string newTimestamp = logInfo[1];
            std::string newMessage = logInfo[2];

            if (type_s == "ERROR") {
                type = LOG_TYPE::ERROR;
            } else if (type_s == "WARNING") {
                type = LOG_TYPE::WARNING;
            } else if (type_s == "INFO") {
                type = LOG_TYPE::INFO;
            } else {
                type = LOG_TYPE::UNKNOWN;
            }

            timestamp = newTimestamp;
            message = newMessage;
        }

        std::string getMessage() {return message;}
        std::string getTimestamp() {return timestamp;}
        LOG_TYPE getLogType() {return type;}
};

void task3() {
    std::ifstream logFile("COMP1000/Week 7/application.log");

    if (!logFile.is_open()) {
        std::cerr << "There was a problem opening 'application.log'" << std::endl;

        if (logFile.fail()) {
            std::cerr << "Errors: " << std::strerror(errno) << std::endl;
        }

        return;
    }

    std::vector<ApplicationLog> logs;
    std::string lineBuffer;

    while (getline(logFile, lineBuffer)) {
        ApplicationLog log(lineBuffer);
        logs.push_back(log);
    }

    logFile.close(); // Close the file, we're done reading

    int errors = 0;
    int warnings = 0;
    std::vector<ApplicationLog> total;

    for (ApplicationLog &log: logs) {
        switch (log.getLogType()) {
            case LOG_TYPE::ERROR:
                errors++;
                break;
            case LOG_TYPE::WARNING:
                warnings++;
                break;
        }

        total.push_back(log);
    }

    std::cout << "Total Errors: " << errors << std::endl;
    std::cout << "Total Warnings: " << warnings << std::endl;
    std::cout << "Lines with ERRORS or WARNINGS:" << std::endl;

    for (ApplicationLog &log: logs) {
        std::cout << log.getMessage() << std::endl;
    }
}

int main() {
    task1();
    task2();
    task3();
    return 0;
}