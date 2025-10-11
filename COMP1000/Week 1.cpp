#include <iostream>
#include <string>

void task1() {
    // Simple variable initialisation
    std::string name = "Emily";    
    int age = 19;
    float height = 1.8;
    char grade = 'A';
}

void task2() {
    int num1, num2;
    
    std::cin >> num1;
    std::cin >> num2;

    std::cout << num1 << " + " << num2 << " = " << num1 + num2 << "\n";
    std::cout << num1 << " - " << num2 << " = " << num1 - num2 << "\n";
    std::cout << num1 << " * " << num2 << " = " << num1 * num2 << "\n";
    std::cout << num1 << " / " << num2 << " = " << num1 / num2 << " (no type casting)\n";
    std::cout << num1 << " / " << num2 << " = " << static_cast<float>(num1) / static_cast<float>(num2) << " (static type casting)" << std::endl;

}

std::string strThing;

void task3local() {
    int num = 10;
    strThing = "Set in inner function";
}

void task3() {
    int num = 0;
    strThing = "Set in outer function";
    task3local();
    std::cout << num << ", " << strThing << std::endl;
}

void task4() {
    float implicitlyCasted = 5 / 4;

    int num1 = 5;
    int num2 = 4;

    float explicitlyCasted = static_cast<float>(num1) / static_cast<float>(num2);

    std::cout << "Implicit Cast: " << implicitlyCasted << std::endl;
    std::cout << "Explicit Cast: " << explicitlyCasted << std::endl;
}

void task5() {
    float calculation = (3 + 2) * 6 - 4;
    float calculation2 = 3 + 2 * 6 - 4;
    // (3 + 2) runs first, then is multiplied by 6
    // Then finally, 4 is removed from the total
    // This gives 26
    // If there was no brackets, it'd be 11
    std::cout << calculation << std::endl;
    std::cout << calculation2 << std::endl;
}

int main(int argc, char** argv) {

    task1();
    task2();
    task3();
    task4();
    task5();

    return 0;
}