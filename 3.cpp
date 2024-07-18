/*
    Lab 8
    Understanding the Concept of Console and File Input/Output
    3.  Write a program to overload stream operators to read a complex number and
        display the complex number in a + ib format.
*/ \
#include<iostream>
using namespace std;

class Complex
{
    
private:
    double real;
    double imag;

public:
    Complex() : real(0), imag(0) {}

    friend istream &operator>>(istream &is, Complex &c);
    friend ostream &operator<<(ostream &os, const Complex &c);
};

istream &operator>>(istream &is, Complex &c)
{
    cout << "Enter real part: ";
    is >> c.real;
    cout << "Enter imaginary part: ";
    is >> c.imag;
    return is;
}
ostream &operator<<(ostream &os, const Complex &c)
{
    os << c.real << " + " << c.imag << "i";
    return os;
}

int main()
{
    Complex c;

    cout << "Enter a complex number:" << endl;
    cin >> c;

    cout << "The complex number is: " << c << endl;

    return 0;
}
