//  AVLTree.h
//  AVLStudentDB
//  Created by Md Safwan Bin Rashid on 10/1/25.

#ifndef AVLTREE_H
#define AVLTREE_H

#include "AVLNode.h"
#include <iostream>
#include <fstream> // for ifstream, ofstream
#include <sstream> // loading CSV
using namespace std;

class AVLTree {
private:
    AVLNode* root;
    
    int height(AVLNode* node) {
            if (node == nullptr) return 0;
            return node->height;
        }

    int getBalance(AVLNode* node) {
            if (node == nullptr) return 0;
            return height(node->left) - height(node->right);
        }

    int max(int a, int b) {
            return (a > b) ? a : b;
        }
    
        AVLNode* rightRotate(AVLNode* y) {
            AVLNode* x = y->left;
            AVLNode* T2 = x->right;

            // Perform rotation
            x->right = y;
            y->left = T2;

            // Update heights
            y->height = max(height(y->left), height(y->right)) + 1;
            x->height = max(height(x->left), height(x->right)) + 1;

            // Return new root
            return x;
        }

        // Left Rotation
        AVLNode* leftRotate(AVLNode* x) {
            AVLNode* y = x->right;
            AVLNode* T2 = y->left;

            // Perform rotation
            y->left = x;
            x->right = T2;

            // Update heights
            x->height = max(height(x->left), height(x->right)) + 1;
            y->height = max(height(y->left), height(y->right)) + 1;

            // Return new root
            return y;
        }

    AVLNode* insertNode(AVLNode* node, Student s) {
        // 1. Normal BST insert
        if (node == nullptr)
            return new AVLNode(s);

        if (s.id < node->data.id)
            node->left = insertNode(node->left, s);
        else if (s.id > node->data.id)
            node->right = insertNode(node->right, s);
        else
            return node; // Duplicate IDs not allowed

        // 2. Update height
        node->height = 1 + max(height(node->left), height(node->right));

        // 3. Get balance factor
        int balance = getBalance(node);

        // 4. Balance the tree

        // Left Left
        if (balance > 1 && s.id < node->left->data.id)
            return rightRotate(node);

        // Right Right
        if (balance < -1 && s.id > node->right->data.id)
            return leftRotate(node);

        // Left Right
        if (balance > 1 && s.id > node->left->data.id) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left
        if (balance < -1 && s.id < node->right->data.id) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        // return unchanged node
        return node;
    }
    
    void inorder(AVLNode* node) {
        if (node == nullptr) return;
        inorder(node->left);
        cout << "ID: " << node->data.id
             << ", Name: " << node->data.name
             << ", GPA: " << node->data.gpa << endl;
        inorder(node->right);
    }
    
    AVLNode* searchNode(AVLNode* node, int id) {
        if (node == nullptr || node->data.id == id)
            return node;

        if (id < node->data.id)
            return searchNode(node->left, id);
        else
            return searchNode(node->right, id);
    }
    
    AVLNode* minValueNode(AVLNode* node) {
        AVLNode* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    AVLNode* deleteNode(AVLNode* root, int id) {
        if (root == nullptr) return root;

        // Normal BST delete
        if (id < root->data.id)
            root->left = deleteNode(root->left, id);
        else if (id > root->data.id)
            root->right = deleteNode(root->right, id);
        else {
            // Node found
            if (root->left == nullptr || root->right == nullptr) {
                AVLNode* temp = root->left ? root->left : root->right;
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }
                delete temp;
            } else {
                AVLNode* temp = minValueNode(root->right);
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data.id);
            }
        }

        // If tree had only one node
        if (root == nullptr)
            return root;

        // Update height
        root->height = 1 + max(height(root->left), height(root->right));

        // Balance
        int balance = getBalance(root);

        // Left Left
        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        // Left Right
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // Right Right
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        // Right Left
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    void saveInorder(AVLNode* node, ofstream& file) {
        if (!node) return;
        saveInorder(node->left, file);
        file << node->data.id << "," << node->data.name << "," << node->data.gpa << "\n";
        saveInorder(node->right, file);
    }


public:
    AVLTree() {
        root = nullptr;
    }
    
    void insert(Student s) {
        root = insertNode(root, s);
    }

    void displayInorder() {
        cout << "\n--- Student Records (Inorder Traversal) ---\n";
        inorder(root);
        cout << "------------------------------------------\n";
    }
    
    Student* search(int id) {
        AVLNode* result = searchNode(root, id);
        if (result != nullptr)
            return &result->data;
        return nullptr;
    }
    
    void remove(int id) {
        root = deleteNode(root, id);
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file for saving.\n";
            return;
        }
        saveInorder(root, file);
        file.close();
        cout << "Data saved to " << filename << endl;
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file for loading.\n";
            return;
        }
        root = nullptr; // reset
        int id;
        string name;
        double gpa;
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            getline(ss, token, ',');
            id = stoi(token);
            getline(ss, name, ',');
            getline(ss, token, ',');
            gpa = stod(token);
            insert(Student(id, name, gpa));
        }
        file.close();
        cout << "Data loaded from " << filename << endl;
    }

};

#endif

