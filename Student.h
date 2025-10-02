//  Student.h
//  AVLStudentDB
//  Created by Md Safwan Bin Rashid on 10/1/25.

#ifndef STUDENT_H
#define STUDENT_H

#include <string>
using namespace std;

struct Student {
    int id;
    string name;
    double gpa;

    Student(int i, string n, double g) {
        id = i;
        name = n;
        gpa = g;
    }

    Student() {
        id = 0;
        name = "";
        gpa = 0.0;
    }
};

#endif
