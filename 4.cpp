/*
    Lab 8
    Understanding the Concept of Console and File Input/Output
    4.  Write a program that stores the information about students (name, student id, department, and address)
        in a structure and then transfers the information to a file in your directory. Finally, retrieve the
        information from your file and print it in the proper format on your output screen.
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Student
{
    string name;
    int studentId;
    string department;
    string address;
};

void writeStudentInfoToFile(const Student &student, const string &filename)
{
    ofstream outFile(filename, ios::app);
    if (!outFile)
    {
        cerr << "Error opening file for writing." << endl;
        return;
    }
    outFile << student.name << endl;
    outFile << student.studentId << endl;
    outFile << student.department << endl;
    outFile << student.address << endl;
    outFile.close();
}

void readStudentInfoFromFile(const string &filename)
{
    ifstream inFile(filename);
    if (!inFile)
    {
        cerr << "Error opening file for reading." << endl;
        return;
    }

    Student student;
    while (getline(inFile, student.name))
    {
        inFile >> student.studentId;
        inFile.ignore(); // to ignore the newline character after studentId
        getline(inFile, student.department);
        getline(inFile, student.address);

        cout << "Name: " << student.name << endl;
        cout << "Student ID: " << student.studentId << endl;
        cout << "Department: " << student.department << endl;
        cout << "Address: " << student.address << endl;
        cout << "-----------------------------" << endl;
    }

    inFile.close();
}

int main()
{
    string filename = "students.txt";

    int numStudents;
    cout << "Enter the number of students: ";
    cin >> numStudents;
    cin.ignore();
    for (int i = 0; i < numStudents; ++i)
    {
        Student student;
        cout << "Enter information for student " << (i + 1) << ":" << endl;
        cout << "Name: ";
        getline(cin, student.name);
        cout << "Student ID: ";
        cin >> student.studentId;
        cin.ignore();
        cout << "Department: ";
        getline(cin, student.department);
        cout << "Address: ";
        getline(cin, student.address);

        writeStudentInfoToFile(student, filename);
    }

    cout << "\nReading student information from the file:" << endl;
    readStudentInfoFromFile(filename);

    return 0;
}
