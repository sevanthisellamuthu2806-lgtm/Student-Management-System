#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Student {
    int id;
    string name;
    int age;
    string course;
};

// Add Student
void addStudent() {
    Student s;

    cout << "\nEnter Student ID: ";
    cin >> s.id;

    cin.ignore();

    cout << "Enter Student Name: ";
    getline(cin, s.name);

    cout << "Enter Age: ";
    cin >> s.age;

    cin.ignore();

    cout << "Enter Course: ";
    getline(cin, s.course);

    ofstream file("students.txt", ios::app);

    if (file.is_open()) {
        file << s.id << "|" << s.name << "|" 
             << s.age << "|" << s.course << endl;

        file.close();

        cout << "\nStudent added successfully!\n";
    } else {
        cout << "\nUnable to open file.\n";
    }
}

// Display Students
void displayStudents() {
    ifstream file("students.txt");

    if (!file.is_open()) {
        cout << "\nNo student records found.\n";
        return;
    }

    Student s;
    string line;

    cout << "\n========== Student Records ==========\n";

    while (getline(file, line)) {
        size_t p1 = line.find("|");
        size_t p2 = line.find("|", p1 + 1);
        size_t p3 = line.find("|", p2 + 1);

        if (p1 == string::npos || p2 == string::npos || p3 == string::npos)
            continue;

        s.id = stoi(line.substr(0, p1));
        s.name = line.substr(p1 + 1, p2 - p1 - 1);
        s.age = stoi(line.substr(p2 + 1, p3 - p2 - 1));
        s.course = line.substr(p3 + 1);

        cout << "ID     : " << s.id << endl;
        cout << "Name   : " << s.name << endl;
        cout << "Age    : " << s.age << endl;
        cout << "Course : " << s.course << endl;
        cout << "-------------------------------------\n";
    }

    file.close();
}

// Update Student
void updateStudent() {
    int searchId;

    cout << "\nEnter Student ID to update: ";
    cin >> searchId;

    ifstream file("students.txt");
    ofstream temp("temp.txt");

    if (!file.is_open()) {
        cout << "\nNo student records found.\n";
        return;
    }

    string line;
    bool found = false;

    while (getline(file, line)) {
        size_t p1 = line.find("|");
        size_t p2 = line.find("|", p1 + 1);
        size_t p3 = line.find("|", p2 + 1);

        if (p1 == string::npos || p2 == string::npos || p3 == string::npos)
            continue;

        int id = stoi(line.substr(0, p1));

        if (id == searchId) {
            Student s;
            s.id = id;

            cin.ignore();

            cout << "Enter New Name: ";
            getline(cin, s.name);

            cout << "Enter New Age: ";
            cin >> s.age;

            cin.ignore();

            cout << "Enter New Course: ";
            getline(cin, s.course);

            temp << s.id << "|" << s.name << "|"
                 << s.age << "|" << s.course << endl;

            found = true;
        } else {
            temp << line << endl;
        }
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "\nStudent updated successfully!\n";
    else
        cout << "\nStudent ID not found.\n";
}

// Delete Student
void deleteStudent() {
    int searchId;

    cout << "\nEnter Student ID to delete: ";
    cin >> searchId;

    ifstream file("students.txt");
    ofstream temp("temp.txt");

    if (!file.is_open()) {
        cout << "\nNo student records found.\n";
        return;
    }

    string line;
    bool found = false;

    while (getline(file, line)) {
        size_t p1 = line.find("|");

        if (p1 == string::npos)
            continue;

        int id = stoi(line.substr(0, p1));

        if (id == searchId) {
            found = true;
            continue;
        }

        temp << line << endl;
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "\nStudent deleted successfully!\n";
    else
        cout << "\nStudent ID not found.\n";
}

// Main Menu
int main() {
    int choice;

    do {
        cout << "\n====================================\n";
        cout << "     STUDENT MANAGEMENT SYSTEM\n";
        cout << "====================================\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Update Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "====================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                updateStudent();
                break;

            case 4:
                deleteStudent();
                break;

            case 5:
                cout << "\nThank you!\n";
                break;

            default:
                cout << "\nInvalid choice. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}