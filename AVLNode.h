//  AVLNode.h
//  AVLStudentDB
//  Created by Md Safwan Bin Rashid on 10/1/25.

#ifndef AVLNODE_H
#define AVLNODE_H

#include "Student.h"

struct AVLNode {
    Student data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(Student s) {
        data = s;
        left = right = nullptr;
        height = 1;
    }
};

#endif
