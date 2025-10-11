#include <iostream>

void task1() {
    int userAge = 0;
    std::cout << "Please enter your age:";
    std::cin >> userAge;

    if (userAge >= 18) {
        std::cout << "You are eligible to vote" << std::endl;
    } else {
        std::cout << "You are too young to vote" << std::endl;
    }
}

void task2() {
    int marks = 0;
    std::cout << "Please enter the amount of marks the student got:";
    std::cin >> marks;

    char grade = '?';

    if (marks >= 90) {
        grade = 'A';
    } else if (marks >= 80) {
        grade = 'B';
    } else if (marks >= 70) {
        grade = 'C';
    } else if (marks >= 60) {
        grade = 'D';
    } else {
        grade = 'F';
    }

    std::cout << "You got a Grade " << grade << std::endl;
}

void task3() {
    char inputChar;
    float num1, num2, total;

    std::cout << "Please enter the first number: ";
    std::cin >> num1;

    std::cout << "Please enter the operator (+, -, *, /): ";
    std::cin >> inputChar;

    std::cout << "Please enter the second number: ";
    std::cin >> num2;

    switch (inputChar) {
        case '+':
            total = num1 + num2;
            break;

        case '-':
            total = num1 - num2;
            break;

        case '*':
            total = num1 * num2;
            break;

        case '/':
            total = num1 / num2;
            break;

        default:
            std::cout << "Invalid operation provided!" << std::endl;
            return;
    }

    std::cout << num1 << inputChar << num2 << " = " << total << std::endl;
}

void task4() {
    int option = 0;

    while (option != 3) {
        std::cout << "1. Start Game\n2. Load Game\n3. Quit" << std::endl;
        std::cin >> option;

        switch (option) {
            case 1:
                std::cout << "Starting a new game!" << std::endl;
                break;

            case 2:
                std::cout << "Loading the game from save" << std::endl;
                break;

            case 3:
                std::cout << "Quitting the game!" << std::endl;
                break;

            default:
                std::cout << "Unknown option! Try again" << std::endl;
                break;
        }

    }
}

void task5() {
    int temp = 0;
    std::cout << "Please input a valid temperature: ";
    std::cin >> temp;

    // I was told to use nested statements
    // I didn't want to
    // I'm sorry
    
    if (temp <= 0) {
        std::cout << "It's Freezing" << std::endl;
    } else {
        if (temp <= 15) {
            std::cout << "It's Cold" << std::endl;
        } else {
            if (temp <= 30) {
                std::cout << "It's Warn" << std::endl;
            } else {
                std::cout << "It's Hot" << std::endl;
            }
        }
    }

}

int main() {
    task1();
    task2();
    task3();
    task4();
    
    return 0;
}