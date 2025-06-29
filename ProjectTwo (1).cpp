// CoursePlanner.cpp
// Name: Casey Farmer
// Date: 06/19/2025
// Course: CS-300
// 7-1 Project Two - Assignment

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include <string>

using namespace std;

// Structure to hold course information
struct Course {
    string courseNumber;
    string name;
    vector<string> prerequisites;
};

// Helper function to trim whitespace from strings
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    size_t last = str.find_last_not_of(" \t\r\n");
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
}

// Function to load course data from file into a map
void loadDataStructure(map<string, Course>& courses, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string courseNumber, name, prerequisite;

        getline(ss, courseNumber, ',');
        getline(ss, name, ',');

        Course course;
        course.courseNumber = trim(courseNumber);
        course.name = trim(name);

        while (getline(ss, prerequisite, ',')) {
            course.prerequisites.push_back(trim(prerequisite));
        }

        // Store course using uppercase course number
        transform(course.courseNumber.begin(), course.courseNumber.end(), course.courseNumber.begin(), ::toupper);
        courses[course.courseNumber] = course;
    }

    file.close();
    cout << "Data loaded successfully." << endl;
}

// Function to print all courses in alphanumeric order
void printCourseList(const map<string, Course>& courses) {
    for (const auto& pair : courses) {
        cout << pair.second.courseNumber << ", " << pair.second.name << endl;
    }
}

// Function to print a specific course and its prerequisites
void printCourse(const map<string, Course>& courses, const string& courseNumber) {
    auto it = courses.find(courseNumber);
    if (it != courses.end()) {
        cout << it->second.courseNumber << ", " << it->second.name << endl;
        if (!it->second.prerequisites.empty()) {
            cout << "Prerequisites: ";
            for (const auto& prereq : it->second.prerequisites) {
                cout << prereq << " ";
            }
            cout << endl;
        } else {
            cout << "Prerequisites: None" << endl;
        }
    } else {
        cout << "Course not found." << endl;
    }
}

int main() {
    map<string, Course> courses;
    int choice;
    string filename, courseNumber;

    while (true) {
        cout << "\nWelcome to the course planner." << endl;
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the filename to load: ";
                cin >> filename;
                loadDataStructure(courses, filename);
                break;
            case 2:
                if (courses.empty()) {
                    cout << "Please load data first using option 1." << endl;
                } else {
                    printCourseList(courses);
                }
                break;
            case 3:
                if (courses.empty()) {
                    cout << "Please load data first using option 1." << endl;
                } else {
                    cout << "What course do you want to know about? ";
                    cin >> courseNumber;
                    transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);
                    printCourse(courses, courseNumber);
                }
                break;
            case 9:
                cout << "Thank you for using the course planner!" << endl;
                return 0;
            default:
                cout << choice << " is not a valid option." << endl;
        }
    }

    return 0;
}
