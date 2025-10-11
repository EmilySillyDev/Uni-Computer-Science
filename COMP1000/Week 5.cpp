#include <iostream>
#include <cmath>

int counter = 0;

int addTwoNumbers(int a, int b) {
    return a + b;
}

void swapNumbers(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

float calculateDistance(float x1, float y1, float x2, float y2) {
    return std::hypot(x2 - x1, y2 - y1);
}

void incrementCounter() {
    counter += 1;
}

void decrementCounter() {
    counter -= 1;
}

void trackFunctionCalls() {
    static int calls = 0;
    calls += 1;
    std::cout << "[trackFunctionCalls] I've been called " << calls << " times!" << std::endl;
}

int main() {
    // Task 1
    int sum1 = addTwoNumbers(1, 2);
    int sum2 = addTwoNumbers(6, 7);

    std::cout << "sum1 = " << sum1 << ", sum2 = " << sum2 << std::endl;

    // Task 2
    int num1 = 6;
    int num2 = 9;

    std::cout << "num1 = " << num1 << ", num2 = " << num2 << std::endl;
    swapNumbers(num1, num2);
    std::cout << "new num1 = " << num1 << ", new num2 = " << num2 << std::endl;

    // Task 3
    float x1, x2, y1, y2 = 0.0;

    std::cout << "Please enter point x1: ";
    std::cin >> x1;

    std::cout << "Please enter point y1: ";
    std::cin >> y1;

    std::cout << "Please enter point x2: ";
    std::cin >> x2;

    std::cout << "Please enter point y2: ";
    std::cin >> y2;

    float dist = calculateDistance(x1, y1, x2, y2);
    std::cout << "The distance between those two points is: " << dist << std::endl;

    // Task 4
    for (int i = 0; i < 5; i++) {
        incrementCounter();
    }

    std::cout << "Incremented counter 5 times, value is now: " << counter << std::endl;

    for (int i = 0; i < 3; i++) {
        decrementCounter();
    }

    std::cout << "Decremented counter 3 times, value is now: " << counter << std::endl;

    // Task 5

    std::cout << "trackFunctionCalls() has been called 0 times, so it's static variable is 0" << std::endl;

    for (int i = 0; i < 5; i++) {
        trackFunctionCalls();
    }
}