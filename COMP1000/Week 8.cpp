#include <iostream>
#include <string>
#include <vector>

class Book {
    private:
        std::string title;
        std::string author;
        float price;

    public:
        Book(std::string title, std::string author, float price): title(title), author(author), price(price) {}

        void displayInfo() {
            std::cout << "Title: " << title
                << ", Author: " << author
                << ", Price: " << price << std::endl;
        }
};

class Student {
    private:
        std::string name;
        int age;
        char grade;

    public:
        void setName(std::string name) {this->name = name;}
        void setAge(int age) {this->age = age; }
        void setGrade(char grade) {this->grade = grade;}

        std::string getName() {return name;}
        int getAge() {return age;}
        char getGrade() {return grade;}
};

class Car {
    private:
        std::string make;
        int year;

    public:
        Car(): make("Unknown"), year(0) {}
        Car(std::string make, int year): make(make), year(year) {}
        ~Car() {
            std::cout << "Your " << year << " " << make << " has been taken to the scrap yard..." << std::endl;
        }

        void displayInfo() {
            std::cout << "Car Make: " << make << ", Year: " << year << std::endl;
        }
};

class Counter {
    private:
        // Use the 'inline' keyword to allow inline definition
        inline static int count = 0;

    public:
        Counter() {
            count += 1;
        }

        ~Counter() {
            count -= 1;
        }

        static int getCount() {
            return count;
        }
};

void printCounterValue() {
    std::cout << Counter::getCount() << std::endl;
}

int main() {
    Book myBook("The C++ Programming Language", "Bjarne Stroustrup", 39.99);
    myBook.displayInfo();

    Student myStudent;
    myStudent.setName("Alice");
    myStudent.setAge(20);
    myStudent.setGrade('A');

    std::cout << "Student Name: " << myStudent.getName() << std::endl;
    std::cout << "Age: " << myStudent.getAge() << std::endl;
    std::cout << "Grade: " << myStudent.getGrade() << std::endl;

    Car defaultCar;
    Car myCar("Mini", 2002);

    defaultCar.displayInfo();
    myCar.displayInfo();

    Counter* c1 = new Counter;
    printCounterValue();

    Counter* c2 = new Counter;
    printCounterValue();

    Counter* c3 = new Counter;
    printCounterValue();

    delete c1;
    printCounterValue();

    return 0;
}