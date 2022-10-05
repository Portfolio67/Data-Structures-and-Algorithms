//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Shane Flaten
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU CODE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <time.h>
#include "CSVparser.hpp"
#include <fstream>

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {  //this is for the eBid
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

//  Internal structure for tree node
struct Node {    // this is the tree,  the body contains the three following variables.
    Bid bid;
    Node* left;   // node pointers
    Node* right;  // the left and right are key aspects of the tree

    // Default constructor, is always needed for c++
    Node() { // in c++ you need default constructors to init variables.  The first thing when constructing a node by giving it abid, the first thing is to make a left and right node with no args. then assign the bid structure
        left = nullptr;   // part left of the node structure
        right = nullptr;   // part right of the node structure
    }
    // initialize with a bid which is the override parameter
    Node(Bid abid) : Node() { // the colon calls the second Node after calling the first
        this->bid = abid; // is a reference to the current instance

    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {  // you can search a tree with a recursive call of a while loop

private:
    Node* root; // node pointer to a node called root

    void addNode(Node* node, Bid bid);
    void inOrder(Node* node);
    Node* removeNode(Node* node, string bidId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // initialize housekeeping variables
    root = nullptr;  // part root of the node structure
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    inOrder(root);
}
/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {
    //  Implement inserting a bid into the tree
    if (root == nullptr) { // root is the top level of the tree
        root = new Node(bid); // default constructor assigns the new node from the bid. With Node there is only: no address and empty default constructor
    }
    else {
        this->addNode(root, bid); // the starting node is the root and pass the bid
    }
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) { // start reading tree from the top down
    // Implement removing a bid from the tree
    this->removeNode(root, bidId);
}

Bid BinarySearchTree::Search(string bidId) { // tree search starts at the current node pointer
    // Implement searching the tree for a bid
    //start searching from the root
    Node* current = root;

    // keep looping downwards until bottom reached or bid is found
    while (current != nullptr) {
        // if matching node return it
        if (current->bid.bidId.compare(bidId) == 0){
            return current->bid;
        }
        // if bid is smaller than current than traverse left
        if (bidId.compare(current->bid.bidId) < 0) { // compares bidId to current.  if the left hand argunment is smaller
            current = current->left; // if current is left the left pointer is the current one,  tis works its way down
        } else {
            current = current->right; // replaced current with root
        }
    }
    return current->bid; // returns the current nodes bid

}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) { // starts by going down the tree; if node is larger than the bid, add to left subtreewe are passing in the root node to start, and that root may not have any childrenadd to the right subtree,  this traverses down the whole tree
    // Implement inserting a bid into the tree
    if (node->bid.bidId.compare(bid.bidId) > 0) { // given a root and starts at the root node. Asks if the new node "node->bid.bidId" is larger than this one.  If true than this node will be the one on the left
        if (node->left == nullptr) {
            node->left = new Node(bid);
        } else {
            this->addNode(node->left, bid);
        }
    }
        // add to the right subtree
    else {
        if (node->right == nullptr) {
            node->right = new Node(bid);
        } else{
            this->addNode(node->right, bid);
        }

    }
}

void BinarySearchTree::inOrder(Node* node) { // in order traversal is all nodes left to right
    if (node != nullptr){
        inOrder(node->left);
        cout << node->bid.bidId << ": "
             << node->bid.title << " | "
             << node->bid.amount << " | "
             << node->bid.fund << endl;
        inOrder(node->right);
    }
}
//Node* removeNode(Node* node, string bidId)
Node *BinarySearchTree::removeNode(Node* node, string bidId) { // given the root to the node
    // if this node is null then return (avoid crashing)
    if (node == nullptr) {
        cout << "the NODE is null" << endl;
        return node;

    }

    // recurse down left subtree
    if (bidId.compare(node->bid.bidId) < 0){
        node->left = removeNode(node->left, bidId);
    } else if (bidId.compare(node->bid.bidId) > 0){
        node->right = removeNode(node->right, bidId);
    } else {
        // no children is this is a leaf node
        if (node->left == nullptr && node->right == nullptr){
            delete node;
            node = nullptr;
        }
            // one child to the left
        else if (node->left != nullptr && node->right == nullptr) {
            Node* temp = node;
            node = node->right;
            delete temp;
        }
            // one child to the right
        else if (node->right != nullptr && node->left == nullptr) {
            Node* temp = node;
            node = node->left;
            delete temp;
        }
            // two children
        else {
            Node* temp = node->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            node->bid = temp->bid;
            node->right = removeNode(node->right, temp->bid.bidId);
        }
        if (node == nullptr) {
            cout << node << ": is not there anymore" << endl;
        }
    }
    return node; // updates the root to null
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
         << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bst->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {  //https://www.geeksforgeeks.org/command-line-arguments-in-c-cpp/

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
        case 2:
            csvPath = argv[1];
            bidKey = "80000";
            break;
        case 3:
            csvPath = argv[1];
            bidKey = argv[2];
            break;
        default:
            csvPath = "/Users/inbox-11077/CLionProjects/Lab6-2/eBid_Monthly_Sales.csv";
            bidKey = "87332";  // this is the key the program is using  because the name of the program differs in charecter lenght, so the command line args are different in length
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;

    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                bst = new BinarySearchTree();

                // Initialize a timer variable before loading bids
                ticks = clock();

                // Complete the method call to load the bids
                loadBids(csvPath, bst);

                // Calculate elapsed time and display result
                ticks = clock() - ticks; // current clock ticks minus starting clock ticks
                cout << "time: " << ticks << " clock ticks" << endl;
                cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
                break;

            case 2:
                bst->InOrder();
                cout << "Has been removed";
                break;

            case 3:
                ticks = clock();
                cout << bidKey << endl;
                bid = bst->Search(bidKey);

                ticks = clock() - ticks; // current clock ticks minus starting clock ticks

                if (!bid.bidId.empty()) {
                    displayBid(bid);
                } else {
                    cout << "Bid Id " << bidKey << " not found." << endl;
                }

                cout << "time: " << ticks << " clock ticks" << endl;
                cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

                break;

            case 4:
                bst->Remove(bidKey);
                break;
        }
    }
    cout << "Good bye." << endl;
    return 0;
}
