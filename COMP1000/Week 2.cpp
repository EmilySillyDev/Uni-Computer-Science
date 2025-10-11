#include <iostream>
#include <iomanip>

void task1() {
    for (int i = 1; i <= 10; i++) {
        std::cout << i << std::endl;
    }
}

void task2() {
    int input = 0;

    while (input > 0) {
        std::cin >> input;
        std::cout << "Typed in: " << input << std::endl;
    }
}

void task3(int height = 5) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < (y + 1); x++) {
            std::cout << "*";
        }
        std::cout << std::endl;
    }
}

void task4() {
    int input = 0;

    do {
        std::cin >> input;
        std::cout << "You typed in " << input << std::endl;
    } while (input > 0);

    std::cout << "Your number is no longer positive" << std::endl;
}

void task5(int width = 10, int height = 10) {
    for (int y = 1; y <= height; y++) {
        for (int x = 1; x <= width; x++) {
            std::cout << std::left << std::setw(5) << x * y;
        }
        std::cout << std::endl;
    }
}

int main() {
    task1();
    task2();
    task3();
    task4();
    task5();

    return 0;
}