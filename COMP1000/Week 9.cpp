#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <map>
#include <stack>

template <class T> class Box {
    private:
        T value;
    
    public:
        Box(T value): value(value) {}
        T getValue() {return value;}
};

class Printer {
    public:
        template <class T> static void print(T value) {
            std::cout << value << std::endl;
        }

        static void print(int value) {
            std::cout << "Double of " << value << ": " << value * 2 << std::endl;
        }

        static void print(std::string value) {
            std::string upperValue = value;
            for (auto & c: upperValue) c = toupper(c);
            std::cout << "Uppercase of \"" << value << "\": " << upperValue << std::endl;
        }
};

template <class X, class Y> class Pair {
    private:
        X value1;
        Y value2;

    public:
        Pair(X value1, Y value2): value1(value1), value2(value2) {}

        void outputValues() {
            std::cout << "First = " << value1 << ", Second = " << value2 << std::endl;
        }
};

int main() {
    Box<int> intBox(10);
    Box<double> doubleBox(25.5);
    Box<std::string> stringBox("Hello");

    std::cout << "intBox: " << intBox.getValue() << std::endl;
    std::cout << "doubleBox: " << doubleBox.getValue() << std::endl;
    std::cout << "stringBox: " << stringBox.getValue() << std::endl;

    // Instead of using seperate instances, I use static methods
    // Makes my code look cleaner
    Printer::print(10.0);
    Printer::print(10);
    Printer::print(std::string("Hello, World"));

    Pair<int, std::string> intStrPair(10, "Hello, World");
    intStrPair.outputValues();

    Pair<float, char> floatCharPair(6.7, 'W');
    floatCharPair.outputValues();

    std::vector<int> myNumbers = {10, 20, 30};
    std::map<std::string, int> myFruits = {
        {"Apple", 5},
        {"Banana", 7}
    };

    std::stack<int> myInts;
    myInts.push(1);
    myInts.push(2);
    myInts.push(3);

    std::cout << "Vector: ";
    for (int &n: myNumbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    std::cout << "Map: Apple -> " << myFruits["Apple"] << ", Banana -> " << myFruits["Banana"] << std::endl;

    std::cout << "Stack pop: ";
    while (!myInts.empty()) {
        std::cout << myInts.top() << " ";
        myInts.pop();
    }

    return 0;
}