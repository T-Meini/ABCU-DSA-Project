#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Course structure to hold course number, title, and prerequisites
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Function to read the course data file, validate its format, and parse course information
// into the hash table
bool readAndParseCourses(const string& filename, unordered_map<string, Course>& hashTable) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: File not found." << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);  // Create string stream from the line
        string token;
        vector<string> tokens;

        // Split the line into tokens using comma (,) as delimiter
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() < 2) {
            cout << "Error: Invalid line format." << endl;
            continue;
        }

        string courseNumber = tokens[0];
        string courseTitle = tokens[1];
        vector<string> prerequisites(tokens.begin() + 2, tokens.end());  // Extract prerequisites

        Course newCourse;
        newCourse.courseNumber = courseNumber;
        newCourse.courseTitle = courseTitle;
        newCourse.prerequisites = prerequisites;
        hashTable[courseNumber] = newCourse;  // Add course to hash table
    }

    file.close();
    return true;
}

// Function to print the course list in sorted order (alphanumeric by course number)
void printCourseList(const unordered_map<string, Course>& hashTable) {
    // Create a vector to store course information (course number and title) for sorting
    vector<pair<string, string>> courseList;
    for (const auto& pair : hashTable) {
        courseList.push_back({ pair.first, pair.second.courseTitle });
    }

    // Sort the course list based on the first element (course number)
    sort(courseList.begin(), courseList.end());

    // Print the sorted course information
    for (const auto& course : courseList) {
        const Course& currentCourse = hashTable.at(course.first); // Use at after checking existence
        cout << "Course Number: " << course.first << endl;
        cout << "Course Title: " << course.second << endl;
        cout << "-------------------------" << endl;
    }
}

// Function to display the menu for user interaction
void displayMenu() {
    cout << "Menu:" << endl;
    cout << "1. Load Data Structure" << endl;
    cout << "2. Print Course List" << endl;
    cout << "3. Print Course" << endl;
    cout << "9. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    // Declare a hash table to store courses using course number as the key and Course struct as the value
    unordered_map<string, Course> hashTable;

    int choice;
    // Loop to keep displaying the menu and processing user choices until the user exits
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            string filename;
            cout << "-------------------------" << endl;
            cout << "Enter the path of the course data file: ";
            cin >> filename;
            // Call the readAndParseCourses function to read the data from the file and populate the hash table
            if (readAndParseCourses(filename, hashTable)) {
                cout << "Data loaded successfully." << endl;
            }
            cout << "-------------------------" << endl;
            break;
        }
        case 2:
            cout << "-------------------------" << endl;
            // Call the printCourseList function to display the course information from the hash table in sorted order
            printCourseList(hashTable);
            break;
        case 3: {
            string courseNumber;
            cout << "Enter course number: ";
            cin >> courseNumber;
            // Search for the course in the hash table using the course number
            if (hashTable.find(courseNumber) != hashTable.end()) {
                cout << "-------------------------" << endl;
                cout << "Course Title: " << hashTable.at(courseNumber).courseTitle << endl;
                // Check if the course has prerequisites and print them if they exist
                if (!hashTable.at(courseNumber).prerequisites.empty()) {
                    cout << "Prerequisites:" << endl;
                    for (const string& prerequisite : hashTable.at(courseNumber).prerequisites) {
                        cout << prerequisite << endl;
                    }
                }
                else {
                    cout << "No prerequisites" << endl;
                }
                cout << "-------------------------" << endl;
            }
            else {
                cout << "Course not found." << endl;
            }
            break;
        }
        case 9:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please choose again." << endl;
        }
    } while (choice != 9);

    return 0;
}