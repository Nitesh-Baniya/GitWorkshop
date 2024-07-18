/*
    Lab 8
    Understanding the Concept of Console and File Input/Output
    2.  Write a program to create a user-defined manipulator that will format the output by
        setting the width, precision, and fill character at the same time by passing arguments.
*/
#include <iostream>
#include <iomanip>
using namespace std;

// Custom manipulator
class CustomManipulator
{
public:
    CustomManipulator(int w, int p, char f) : width(w), precision(p), fill(f) {}

    friend ostream &operator<<(ostream &os, const CustomManipulator &cm);

private:
    int width;
    int precision;
    char fill;
};
ostream &operator<<(ostream &os, const CustomManipulator &cm)
    {
        os << setw(cm.width) << setprecision(cm.precision) << setfill(cm.fill) << fixed;
        return os;
    }

// Factory function to create the custom manipulator
CustomManipulator customFormat(int width, int precision, char fill)
{
    return CustomManipulator(width, precision, fill);
}

int main()
{
    double num = 123.456789;

    // Using the custom manipulator
    cout << customFormat(10, 3, '*') << num << endl;
    cout << customFormat(15, 5, '#') << num << endl;
    cout << customFormat(8, 2, '-') << num << endl;

    return 0;
}
