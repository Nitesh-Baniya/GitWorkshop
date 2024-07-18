/*
    Lab 8
    Understanding the Concept of Console and File Input/Output
    5.  Write a program for transaction processing that write and read object randomly to and from
        a random access file so that user can add, update, delete and display the account information
        (account-number, last-name, first-name, total-balance).
*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

struct Account {
    int accountNumber;
    string lastName;
    string firstName;
    double totalBalance;
};

void displayMenu() {
    cout << "\n1. Add Account" << endl;
    cout << "2. Update Account" << endl;
    cout << "3. Delete Account" << endl;
    cout << "4. Display Account" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
}

void addAccount(fstream &file) {
    Account account;
    cout << "Enter account number: ";
    cin >> account.accountNumber;
    cin.ignore();
    cout << "Enter last name: ";
    getline(cin, account.lastName);
    cout << "Enter first name: ";
    getline(cin, account.firstName);
    cout << "Enter total balance: ";
    cin >> account.totalBalance;

    file.seekp(0, ios::end); // Move to the end of the file
    file << account.accountNumber << ' ' << account.lastName << ' ' << account.firstName << ' ' << account.totalBalance << endl;
}

void updateAccount(fstream &file) {
    int accountNumber;
    cout << "Enter account number to update: ";
    cin >> accountNumber;

    file.clear(); // Clear EOF flag
    file.seekg(0, ios::beg); // Move to the beginning of the file
    Account account;
    bool found = false;
    streampos pos;

    while (file >> account.accountNumber >> account.lastName >> account.firstName >> account.totalBalance) {
        if (account.accountNumber == accountNumber) {
            found = true;
            pos = file.tellg();
            break;
        }
    }

    if (found) {
        cout << "Enter last name: ";
        cin.ignore();
        getline(cin, account.lastName);
        cout << "Enter first name: ";
        getline(cin, account.firstName);
        cout << "Enter total balance: ";
        cin >> account.totalBalance;

        file.clear(); // Clear EOF flag
        file.seekp(pos - streamoff(sizeof(Account))); // Move to the position of the account
        file << account.accountNumber << ' ' << account.lastName << ' ' << account.firstName << ' ' << account.totalBalance << endl;
    } else {
        cout << "Account not found." << endl;
    }
}

void deleteAccount(fstream &file) {
    int accountNumber;
    cout << "Enter account number to delete: ";
    cin >> accountNumber;

    fstream tempFile("temp.txt", ios::out);
    file.clear();
    file.seekg(0, ios::beg);

    Account account;
    while (file >> account.accountNumber >> account.lastName >> account.firstName >> account.totalBalance) {
        if (account.accountNumber != accountNumber) {
            tempFile << account.accountNumber << ' ' << account.lastName << ' ' << account.firstName << ' ' << account.totalBalance << endl;
        }
    }

    file.close();
    tempFile.close();
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    file.open("accounts.txt", ios::in | ios::out);
}

void displayAccount(fstream &file) {
    int accountNumber;
    cout << "Enter account number to display: ";
    cin >> accountNumber;

    file.clear();
    file.seekg(0, ios::beg);

    Account account;
    bool found = false;
    while (file >> account.accountNumber >> account.lastName >> account.firstName >> account.totalBalance) {
        if (account.accountNumber == accountNumber) {
            found = true;
            break;
        }
    }

    if (found) {
        cout << "Account Number: " << account.accountNumber << endl;
        cout << "Last Name: " << account.lastName << endl;
        cout << "First Name: " << account.firstName << endl;
        cout << "Total Balance: $" << fixed << setprecision(2) << account.totalBalance << endl;
    } else {
        cout << "Account not found." << endl;
    }
}

int main() {
    fstream file("accounts.txt", ios::in | ios::out | ios::app);

    if (!file) {
        cerr << "File could not be opened." << endl;
        return 1;
    }

    int choice;
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addAccount(file);
                break;
            case 2:
                updateAccount(file);
                break;
            case 3:
                deleteAccount(file);
                break;
            case 4:
                displayAccount(file);
                break;
            case 5:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 5);

    file.close();
    return 0;
}
