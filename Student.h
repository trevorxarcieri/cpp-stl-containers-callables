// Student.h
// Author: Trevor Arcieri
// Date: 13 June 2024
// Description: Header file defining a Student class.

#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
private:
    const std::string firstName;  // First name of the student, immutable
    const std::string lastName;   // Last name of the student, immutable
    const std::string dateOfBirth; // Date of birth, immutable
    const std::string school;      // School name, immutable
    float currentGPA;             // Current GPA, mutable

public:
    // Constructor for initializing all member variables
    Student(std::string fn, std::string ln, std::string dob, float gpa, std::string sch)
        : firstName(fn), lastName(ln), dateOfBirth(dob), currentGPA(gpa), school(sch) {}

    // Getters for all fields
    std::string getFirstName() const { return firstName; }
    std::string getLastName() const { return lastName; }
    std::string getDateOfBirth() const { return dateOfBirth; }
    std::string getSchool() const { return school; }
    float getCurrentGPA() const { return currentGPA; }

    // Setter for current GPA
    void setCurrentGPA(float gpa) { currentGPA = gpa; }

    // Comparison operators based on lexicographical order of last name then first name
    bool operator<(const Student& other) const {
        return lastName < other.lastName || (lastName == other.lastName && firstName < other.firstName);
    }

    bool operator>(const Student& other) const {
        return lastName > other.lastName || (lastName == other.lastName && firstName > other.firstName);
    }

    bool operator==(const Student& other) const {
        return lastName == other.lastName && firstName == other.firstName;
    }

    bool operator!=(const Student& other) const {
        return !(*this == other);
    }
};

#endif // STUDENT_H
