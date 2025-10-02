//  main.cpp
//  AVLStudentDB
//  Created by Md Safwan Bin Rashid on 10/1/25.

#include <iostream>
#include "AVLTree.h"
using namespace std;

int main() {
    AVLTree tree;
    int choice;

    do {
        cout << "\n=== Student Database Menu ===\n";
        cout << "1. Insert Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Save to File\n";
        cout << "6. Load from File\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int id;
            string name;
            double gpa;

            cout << "Enter Student ID: ";
            cin >> id;
            cin.ignore(); // clear buffer

            cout << "Enter Student Name: ";
            getline(cin, name);

            cout << "Enter GPA: ";
            cin >> gpa;

            Student s(id, name, gpa);
            tree.insert(s);
            cout << "Student inserted successfully!\n";

        } else if (choice == 2) {
            tree.displayInorder();

        } else if (choice == 3) {
            int id;
            cout << "Enter ID to search: ";
            cin >> id;
            Student* s = tree.search(id);
            if (s)
                cout << "Found: ID = " << s->id << ", Name = " << s->name << ", GPA = " << s->gpa << endl;
            else
                cout << "Student not found.\n";

        } else if (choice == 4) {
            int id;
            cout << "Enter ID to delete: ";
            cin >> id;
            tree.remove(id);
            cout << "Student removed (if existed).\n";

        } else if (choice == 5) {
            tree.saveToFile("students.csv");

        } else if (choice == 6) {
            tree.loadFromFile("students.csv");

        } else if (choice == 7) {
            cout << "Exiting program... \n";

        } else {
            cout << "Invalid choice, try again.\n";
        }

    } while (choice != 7); 

    return 0;
}
