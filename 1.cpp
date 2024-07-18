/*
    Lab 8
    Understanding the Concept of Console and File Input/Output
    1.  Write a program to demonstrate the use of different ios flags and functions to
        format the output. Create a program to generate the bill invoice of a department store
        by using different formatting.
*/ \
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Item {
public:
    string name;
    int quantity;
    double price;

    Item(string n, int q, double p) : name(n), quantity(q), price(p) {}
};

void printInvoice(const Item items[], int numItems) {
    double total = 0.0;

    cout << left << setw(20) << "Item"
              << right << setw(10) << "Quantity"
              << right << setw(15) << "Price"
              << right << setw(20) << "Total"
              << endl;
    cout << string(65, '-') << endl;

    for (int i = 0; i < numItems; ++i) {
        double itemTotal = items[i].quantity * items[i].price;
        total += itemTotal;

        cout << left << setw(20) << items[i].name
                  << right << setw(10) << items[i].quantity
                  << right << setw(15) << fixed << setprecision(2) << items[i].price
                  << right << setw(20) << itemTotal
                  << endl;
    }

    cout << string(65, '-') << endl;
    cout << left << setw(45) << "Total Amount:"
              << right << setw(20) << fixed << setprecision(2) << total
              << endl;
}

int main() {
    Item items[] = {
        Item("Apple", 10, 0.99),
        Item("Banana", 5, 1.49),
        Item("Milk", 2, 2.99),
        Item("Bread", 1, 3.49)
    };
    int numItems = sizeof(items) / sizeof(items[0]);

    printInvoice(items, numItems);

    return 0;
}
