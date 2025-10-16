#include <iostream>
#include <string>

class Vehicle {
    protected:
        std::string m_make;
        std::string m_model;

    public:
        Vehicle(std::string make, std::string model): m_make(make), m_model(model) {}
        void displayInfo() {
            std::cout << "Make: " << m_make << ", Model: " << m_model << std::endl;
        }
};

class Car: public Vehicle {
    protected:
        int m_numberOfDoors;

    public:
        Car(std::string make, std::string model, int numberOfDoors): Vehicle(make, model), m_numberOfDoors(numberOfDoors) {}
        void displayInfo() {
            std::cout << "Make: " << m_make << ", Model: " << m_model << ", No. of Doors: " << m_numberOfDoors << std::endl;
        }
};

class Bike: public Vehicle {
    protected:
        bool m_hasCarrier;

    public: 
        Bike(std::string make, std::string model, bool hasCarrier): Vehicle(make, model), m_hasCarrier(hasCarrier) {}
        void displayInfo() {
            std::string hasCarrierString = m_hasCarrier ? "True" : "False";
            std::cout << "Make: " << m_make << ", Model: " << m_model << ", Has Carrier: " << hasCarrierString << std::endl;
        }
};

class Animal {
    public:
        virtual void speak() {
            std::cout << "*indescernible animal noises*" << std::endl;
        }
};

class Dog: public Animal{
    public:
        virtual void speak() {
            std::cout << "Woof!" << std::endl;
        }
};

class Cat: public Animal {
    public:
        virtual void speak() {
            std::cout << "Meow!" << std::endl;
        }
};

class Address {
    protected:
        std::string m_street;
        std::string m_city;
        std::string m_postcode;

    public:
        Address(std::string street, std::string city, std::string postcode): m_street(street), m_city(city), m_postcode(postcode) {}
        std::string getInfo() {
            return "Address: " + m_street + ", " + m_city + " " + m_postcode;
        }
};

class Person {
    protected:
        std::string m_name;
        int m_age;
        Address m_address;
    public:
        Person(std::string name, int age, std::string street, std::string city, std::string postcode): m_name(name), m_age(age), m_address(street, city, postcode) {}
        void displayInfo() {
            std::cout << "Name: " << m_name << ", Age: " << m_age << ", " << m_address.getInfo() << std::endl;
        }
};

int main() {

    Car myCar("Mini", "One", 3);
    Bike myBike("Zontes", "Mantis125", false);

    myCar.displayInfo();
    myBike.displayInfo();

    Animal* a;
    Cat c;
    Dog d;
    a = &d;

    c.speak();
    a->speak();

    Person me("Emily", 19, "Street St.", "Citysville", "P057C0d3");
    me.displayInfo();

    return 0;
}