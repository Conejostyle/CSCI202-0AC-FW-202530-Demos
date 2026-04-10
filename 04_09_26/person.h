#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

class Person
{
public:
    Person() {};
    Person(const std::string &n, int a, double h)
        : name(n), age(a), height(h) {}

    void print() const
    {
        std::cout << name << " (Age: " << age << ", Height: " << height << " cm)\n";
    }
    std::string getName() { return name; };
    int getAge() { return age; };
    double getHeight() { return height; };
    friend std::ostream &operator<<(std::ostream &, const Person &);

private:
    std::string name;
    int age;
    double height; // in cm
};

std::ostream &operator<<(std::ostream &out, const Person &p)
{
    out << p.name << " (Age: " << p.age << ", Height: " << p.height << " cm)";
    return out;
}
#endif