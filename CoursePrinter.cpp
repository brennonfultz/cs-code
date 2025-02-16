// CoursePrinter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Brennon Fultz CS 300 Project Two

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

//course obj
struct Course {
    string courseId; // unique identifier
    string title;
    string prereq1;
    string prereq2;
    //constructors
    Course() : courseId(""), title(""), prereq1(""), prereq2("") {}

    Course(const string& courseId, const string& title, const string& prereq1, const string& prereq2)
        : courseId(courseId), title(title), prereq1(prereq1), prereq2(prereq2) {}
};

//node for BST
struct Node {
    Course course;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a course
    Node(Course aCourse) :
        Node() {
        course = aCourse;
    }
};

//BST definition
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);
    Node* removeNode(Node* node, string courseId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PostOrder();
    void PreOrder();
    void Insert(Course course);
    void Remove(string courseId);
    void Search(string courseId);

};

//Default constructor
 
BinarySearchTree::BinarySearchTree() {
    //root is equal to nullptr
    root = nullptr;
}

//Destructor
 
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
    removeNode(root, root->course.courseId);
}

//Traverse tree
void BinarySearchTree::InOrder() {
    // call inOrder function and pass root 
    inOrder(root);
}

void BinarySearchTree::PostOrder() {
    // postOrder root
    postOrder(root);
}

void BinarySearchTree::PreOrder() {
    // preOrder root
    preOrder(root);
}

/**
 * Insert a course
 */
void BinarySearchTree::Insert(Course course) {
    // if root equal to null ptr
    if (root == nullptr) {
        root = new Node(course); // root is equal to new node course
    }
    else {// else
        this->addNode(root, course); // add Node root and course
    }
}

 //Remove a course
 
void BinarySearchTree::Remove(string courseId) {
    // remove node root courseId
    removeNode(root, courseId);
}

//Search for a course

void BinarySearchTree::Search(string courseId) {
    // set current node equal to root    
    Node* cur = root;
    // keep looping downwards until bottom reached or matching courseId found
    while (cur != nullptr) {
        if (cur->course.courseId.compare(courseId) == 0) {
            // Print course details
            cout << "Course ID:" << cur->course.courseId << endl;
            cout << "Title: " << cur->course.title << endl;
            cout << "Prerequisite 1: " << cur->course.prereq1 << endl;
            cout << "Prerequisite 2: " << cur->course.prereq2 << endl;
            return;
        } // if courseId is smaller than current node then traverse left
        else if (courseId.compare(cur->course.courseId) < 0) {
            cur = cur->left;
        }
        else {// else larger so traverse right
            cur = cur->right;
        }
    }

    cout << "Course not found\n";
}


//Add node
void BinarySearchTree::addNode(Node* node, Course course) {
    // if node is larger then add to left        
    if (node != nullptr && node->course.courseId.compare(course.courseId) > 0) {
        if (node->left == nullptr) {// if no left node
            node->left = new Node(course); // this node becomes left
            return;
        }
        else {
            this->addNode(node->left, course); // else recurse down the left node
        }
    }
    // else
    else if (node != nullptr && node->course.courseId.compare(course.courseId) < 0) {
        if (node->right == nullptr) {// if no right node
            node->right = new Node(course); // this node becomes right
            return;
        }
        else {// else
            this->addNode(node->right, course); // recurse down the right node
        }
    }
}

void BinarySearchTree::inOrder(Node* node) {
    //if node is not equal to null ptr
    if (node != nullptr) {
        inOrder(node->left); // InOrder not left
        cout << node->course.courseId << " | " << node->course.title << " | " <<
            node->course.prereq1 << " | " << node->course.prereq2 << endl; // output courseId, title, prereqs
        inOrder(node->right); // InOrder right
    }
}

void BinarySearchTree::postOrder(Node* node) {
    //if node is not equal to null ptr
    if (node != nullptr) {
        postOrder(node->left); // postOrder left
        postOrder(node->right); // postOrder right
        cout << node->course.courseId << " | " << node->course.title << " | " <<
            node->course.prereq1 << " | " << node->course.prereq2 << endl; // output courseId, title, prereqs
    }
}

void BinarySearchTree::preOrder(Node* node) {
    //if node is not equal to null ptr
    if (node != nullptr) {
        cout << node->course.courseId << " | " << node->course.title << " | " <<
            node->course.prereq1 << " | " << node->course.prereq2 << endl; // output courseId, title, prereqs
        preOrder(node->left); // preOrder left
        preOrder(node->right); // preOrder right
    }
}

Node* BinarySearchTree::removeNode(Node* node, string courseId) {
    if (node == nullptr) { // if node is null return node
        return node;
    } // else if node less than courseId
    else if (courseId.compare(node->course.courseId) < 0) {
        node->left = removeNode(node->left, courseId); // call method on left side
    }
    else if (courseId.compare(node->course.courseId) > 0) { // else if node greater than courseId
        node->right = removeNode(node->right, courseId); // call method on right side
    }
    else { // else match found
        if (node->left == nullptr && node->right == nullptr) {
            delete node; // if leaf node delete leaf
            node = nullptr;
        } // else if node has only left child
        else if (node->left != nullptr && node->right == nullptr) {
            Node* tmp = node; // temp holds node
            node = node->left;
            delete tmp; // child node replaces parent
            tmp = nullptr;
        } // else if node only has right child
        else if (node->right != nullptr && node->left == nullptr) {
            Node* tmp = node; // temp holds node
            node = node->right; // child node replaces parent
            delete tmp;
            tmp = nullptr;
        }
        else { // else if has both children
            Node* tmp = node->right; // temp holds right node
            while (tmp->left != nullptr) { // find minimum right node
                tmp = tmp->left;
            }
            node->course = tmp->course; // minimum right node becomes parent
            node->right = removeNode(node->right, tmp->course.courseId);
        }
    }
    return node;
}

void loadCourses(BinarySearchTree& bst, const string& filename) {
    ifstream file(filename); // Open file
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) { // read line from file
        size_t pos1 = 0, pos2 = 0, pos3 = 0;

        // pull data from line
        pos1 = line.find(',', pos2);
        string courseId = line.substr(pos2, pos1 - pos2);

        pos2 = pos1 + 1;
        pos1 = line.find(',', pos2);
        string courseTitle = line.substr(pos2, pos1 - pos2);

        pos2 = pos1 + 1;
        pos1 = line.find(',', pos2);
        string prereq1 = line.substr(pos2, pos1 - pos2);

        pos2 = pos1 + 1;
        pos1 = line.find(',', pos2);
        string prereq2 = line.substr(pos2, pos1 - pos2);

        // create Course obj and add to bst
        Course course(courseId, courseTitle, prereq1, prereq2);
        bst.Insert(course);
    }

    file.close(); // Close file
    cout << "Courses loaded.\n";
}


int main() {

    int choice = 0;
    string filename;
    string courseToFind;

    //initialize bst
    BinarySearchTree bst;
    Course course;

    while (choice != 9) { //loop for menu
        cout << "Welcome to the course planner. Enter a number:\n"; //menu options
        cout << "1. Load course data.\n";
        cout << "2. Print course list.\n";
        cout << "3. Print course.\n";
        cout << "9. Exit.\n"; //exit condition

        cout << "Enter your choice: ";
        cin >> choice; //input is choice

        switch (choice) { //switch statement of choices
        case 1:
            cout << "Enter filename:\n"; //take filenam input 
            cin >> filename;
            loadCourses(bst, filename); //call method to load csv
            break;
        case 2:
            cout << "Printing courses...\n"; //print courses in order
            bst.InOrder();
            break;
        case 3:
            cout << "Enter course ID: \n";
            cin >> courseToFind;
            bst.Search(courseToFind);
            break;
        case 9:
            cout << "Exiting the course planner. Goodbye!\n"; //close program
            return 0;
        default:
            cout << "Invalid input\n"; //handle other inputs 
        }
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
