#include <iostream>
#include <cstring>

int task1sum(int arr[], int size) {
    int sum = 0;

    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }

    return sum;
}

void task1() {
    int array[10] = {};

    for (int i = 0; i < 10; i++) {
        array[i] = i + 1;
    }

    int sum = task1sum(array, 10);
    int average = sum / 10;

    std::cout << "Sum: " << sum << " | Average: " << average << std::endl;
}

void task2() {
    std::string hello = "Hello ";
    std::string world = "World!";
    std::string concat = hello + world;

    std::cout << "String Value: " << concat << " | String Length: " << concat.length() << std::endl;

    bool stringsAreEqual = (hello == world);
    std::string equalString = stringsAreEqual ? "the same" : "different";
    std::cout << "The two start strings are " << equalString << std::endl;
}

void task3() {
    int myVar = 10;
    int* myVarPointer = &myVar;

    std::cout << "The value of the pointer is: " << *myVarPointer << std::endl;;

    *myVarPointer = 15;
    std::cout << "The new value of the pointer is: " << *myVarPointer << std::endl;
}

void task4() {
    int arr[5] = {1, 2, 3, 4, 5};

    // The value of 'arr' is the pointer to the first element
    // std::cout << *arr << std::endl; would give '1'

    for (int i = 0; i < 5; i++) {
        int* elementPointer = arr + i;
        std::cout << "Element " << i << ": " << *elementPointer << std::endl;
    }

    for (int i = 0; i < 5; i++) {
        int* elementPointer = arr + i;
        *elementPointer += 2;
        std::cout << "Modified Element " << i << ": " << *elementPointer << std::endl;
    }
}

void task5() {
    char* cString = static_cast<char*>(malloc(sizeof(char) * 20));
    std::cin.getline(cString, 20);
    std::cout << cString << " (Size: " << strlen(cString) << ")" << std::endl;
    free(cString);
}

int main() {
    task1();
    task2();
    task3();
    task4();
    task5();

    return 0;
}