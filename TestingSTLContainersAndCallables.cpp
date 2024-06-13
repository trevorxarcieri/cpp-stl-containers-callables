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
    // Initialize students using a normal array
    Student studentArray[] = {
        {"John", "Doe", "1990-01-01", 3.5, "SchoolA"},
        {"Jane", "Doe", "1991-02-01", 3.7, "SchoolB"},
        {"Alice", "Johnson", "1992-03-02", 3.9, "SchoolA"},
        {"Bob", "Smith", "1989-12-13", 3.1, "SchoolC"},
        {"Charlie", "Brown", "1990-09-15", 2.8, "SchoolA"},
        {"David", "Wilson", "1993-07-23", 3.6, "SchoolD"},
        {"Eva", "Davis", "1991-08-19", 3.8, "SchoolB"},
        {"Frank", "Miller", "1992-11-11", 3.2, "SchoolE"}
    };

    // Calculate the number of elements in the array
    size_t arraySize = sizeof(studentArray) / sizeof(studentArray[0]);

    // Constructing vector from the array
    std::vector<Student> students(std::begin(studentArray), std::end(studentArray));

    // Using STL algorithms to find and copy students from a specific school
    std::string targetSchool = "SchoolA";
    auto count = std::count_if(students.begin(), students.end(), [targetSchool](const Student& s) {
        return s.getSchool() == targetSchool;  // Using lambda function with capture
    });
    std::cout << "Students attending " << targetSchool << " using STL: " << count << std::endl;

    std::vector<Student> filteredStudents;
    std::copy_if(students.begin(), students.end(), std::back_inserter(filteredStudents), IsAttending(targetSchool));
    std::cout << "Copied students attending " << targetSchool << " using STL: " << filteredStudents.size() << std::endl;

    // Using manual iteration to count and copy students
    int manualCount = 0;
    std::vector<Student> manualFilteredStudents;
    for (size_t i = 0; i < arraySize; i++) {
        if (studentArray[i].getSchool() == targetSchool) {
            manualCount++;
            manualFilteredStudents.push_back(studentArray[i]);
        }
    }
    std::cout << "Students attending " << targetSchool << " using normal array with manual indexing: " << manualCount << std::endl;
    std::cout << "Copied students attending " << targetSchool << " using normal array with manual indexing: " << manualFilteredStudents.size() << std::endl;

    return 0;
}
