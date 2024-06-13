// TestingSTLContainersAndCallables.cpp
// Author: Trevor Arcieri
// Date: 13 June 2024
// Description: Testing STL containers and callables for handling Student objects.

#include "Student.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

// Function object to check if a student is attending a specific school
class IsAttending {
private:
    std::string school;
public:
    IsAttending(const std::string& sch) : school(sch) {}

    bool operator()(const Student& s) const {
        return s.getSchool() == school;
    }
};

int main() {
    // Initialize students using an array
    Student studentArray[] = {
        {"John", "Doe", "1990-01-01", 3.5, "SchoolA"},
        {"Jane", "Doe", "1991-02-01", 3.7, "SchoolB"},
        {"Alice", "Johnson", "1992-03-02", 3.9, "SchoolA"},
        {"Bob", "Smith", "1989-12-13", 3.1, "SchoolC"},
        {"Charlie", "Brown", "1990-09-15", 2.8, "SchoolA"},
        {"David", "Wilson", "1993-07-23", 3.6, "SchoolD"},
        {"Eva", "Davis", "1991-08-19", 3.8, "SchoolB"},
        {"Frank", "Miller", "1992-11-11", 3.2, "SchoolE"}
    }; // All Students allocated on the stack, no need to delete later


    // Testing the functionality of the Student class
    std::cout << "\n--- Testing Student Class Functionality ---\n";

    // Display all student details
    for (const auto& student : studentArray) {
        std::cout << "Student: " << student.getFirstName() << " " << student.getLastName()
                  << ", DOB: " << student.getDateOfBirth() << ", GPA: " << student.getCurrentGPA()
                  << ", School: " << student.getSchool() << std::endl;
    }

    // Modify the GPA of the first student and display the change
    std::cout << "\nModifying GPA of the first student (John Doe) to 3.8...\n";
    studentArray[0].setCurrentGPA(3.8);  // Changing GPA
    std::cout << "Updated GPA for John Doe: " << studentArray[0].getCurrentGPA() << std::endl;
    
    // Find the student with the lowest name in lexographical order
    const Student* studentWithLowestLex = &studentArray[0]; // Start by assuming the first student has the lowest order name
    for (const auto& student : studentArray) {
        if (student < *studentWithLowestLex) {
            studentWithLowestLex = &student; // Update if the current student has a lower GPA
        }
    }

    // Print the student with the lowest name in lexographical order
    std::cout << "\nStudent with the lowest name in lexographical order (last name, first name):\n";
    std::cout << "Student: " << studentWithLowestLex->getLastName() << ", " << studentWithLowestLex->getFirstName() << std::endl;

    // Retrieve students for comparison
    const Student& johnDoe = studentArray[0];
    const Student& janeDoe = studentArray[1];

    // Testing '>'
    std::cout << "\nJohn Doe > Jane Doe (expected Yes): " << (johnDoe > janeDoe ? "Yes" : "No") << std::endl;

    // Testing '=='
    std::cout << "John Doe == Jane Doe (expected No): " << (johnDoe == janeDoe ? "Yes" : "No") << std::endl;

    // Testing '!='
    std::cout << "John Doe != Jane Doe (expected Yes): " << (johnDoe != janeDoe ? "Yes" : "No") << std::endl;


    // Testing Students attending a specific school
    std::cout << "\n--- Testing Students Attending a School ---\n";

    // Constructing vector from the array
    std::vector<Student> students(std::begin(studentArray), std::end(studentArray));

    // Using STL algorithms and lambda function to count students from a specific school
    std::string targetSchool = "SchoolA";
    auto count = std::count_if(students.begin(), students.end(), [targetSchool](const Student& s) {
        return s.getSchool() == targetSchool;  // Using lambda function with capture
    });
    std::cout << "Students attending " << targetSchool << " using STL: " << count << std::endl;

    // Using STL algorithms and function object to copy students from a specific school
    std::vector<Student> filteredStudents;
    std::copy_if(students.begin(), students.end(), std::back_inserter(filteredStudents), IsAttending(targetSchool));
    std::cout << "Copied students attending " << targetSchool << " using STL: " << filteredStudents.size() << std::endl;
    
    // Using manual iteration to count and copy students
    int manualCount = 0;
    size_t arraySize = sizeof(studentArray) / sizeof(studentArray[0]); // Calculate the number of elements in the array
    std::vector<Student> manualFilteredStudents; // Using STL vector to have variable storage size for filtered students
    for (size_t i = 0; i < arraySize; i++) {
        if (studentArray[i].getSchool() == targetSchool) {
            manualCount++;
            manualFilteredStudents.push_back(studentArray[i]);
        }
    }
    std::cout << "Students attending " << targetSchool << " using normal array with manual iteration: " << manualCount << std::endl;
    std::cout << "Copied students attending " << targetSchool << " using normal array with manual iteration: " << manualFilteredStudents.size() << std::endl;

    return 0;
}
