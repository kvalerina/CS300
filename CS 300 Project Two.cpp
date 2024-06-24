#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Define the structure for a course
struct Course {
    string courseId;
    string title;
    vector<string> prerequisites;
};

// Function to convert a string to lower case
string toLowerCase(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

// Function to load courses from a file
map<string, Course> loadCourses(const string& fileName) {
    map<string, Course> courses;
    ifstream file(fileName);
    string line;

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << fileName << endl;
        return courses;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string courseId, title, prereq;
        getline(ss, courseId, ',');
        getline(ss, title, ',');

        Course course;
        course.courseId = courseId;
        course.title = title;

        while (getline(ss, prereq, ',')) {
            course.prerequisites.push_back(prereq);
        }

        courses[courseId] = course;
    }

    file.close();
    return courses;
}

// Function to print the course list
void printCourseList(const map<string, Course>& courses) {
    vector<string> courseIds;
    for (const auto& entry : courses) {
        courseIds.push_back(entry.first);
    }

    sort(courseIds.begin(), courseIds.end());

    for (const auto& courseId : courseIds) {
        cout << courseId << ", " << courses.at(courseId).title << endl;
    }
}

// Function to print course information
void printCourseInfo(const map<string, Course>& courses, const string& courseId) {
    string lowerCourseId = toLowerCase(courseId);
    for (const auto& entry : courses) {
        if (toLowerCase(entry.first) == lowerCourseId) {
            cout << entry.second.courseId << ", " << entry.second.title << endl;
            if (!entry.second.prerequisites.empty()) {
                cout << "Prerequisites: ";
                for (size_t i = 0; i < entry.second.prerequisites.size(); ++i) {
                    cout << entry.second.prerequisites[i];
                    if (i < entry.second.prerequisites.size() - 1) {
                        cout << ", ";
                    }
                }
                cout << endl;
            }
            else {
                cout << "Prerequisites: None" << endl;
            }
            return;
        }
    }
    cout << "Course not found." << endl;
}

// Main function to run the program
int main() {
    map<string, Course> courses;
    int choice;
    string fileName;
    string courseId;

    while (true) {
        cout << "Welcome to the course planner." << endl;
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";
        cin >> choice;

        // Debugging statement to check the user's choice
        cout << "User selected option: " << choice << endl;

        // Clear the input buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            cout << "Enter the file name: ";
            getline(cin, fileName); // Use getline to read the file name
            cout << "Loading courses from file: " << fileName << endl; // Debugging statement
            courses = loadCourses(fileName);
            if (!courses.empty()) {
                cout << "Courses loaded successfully!" << endl;
            }
            else {
                cout << "Failed to load courses. Please check the file and try again." << endl;
            }
            break;
        case 2:
            if (!courses.empty()) {
                printCourseList(courses);
            }
            else {
                cout << "Load the data first!" << endl;
            }
            break;
        case 3:
            if (!courses.empty()) {
                cout << "What course do you want to know about? ";
                cin >> courseId;
                printCourseInfo(courses, courseId);
            }
            else {
                cout << "Load the data first!" << endl;
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
