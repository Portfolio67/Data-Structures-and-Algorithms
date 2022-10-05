/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

//============================================================================
// Name        : LinkedList.cpp
// Author      : Shane Flaten
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU CODE
// Description : Lab 3-3 Lists and Searching
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    /* Bid() - default constructor is auto called when
     * a new instance of something , ex. class or struct*/
    Bid() {
        amount = 0.0;
    }
};

//============================================================================
// Linked-List class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a linked-list.
 */
class LinkedList {

private:
    //Internal structure for list entries, housekeeping variables.
    /*
     * With use of the internal node structure  (needs a pointer ans stores data) struct
     * Head pointer start of list and a next pointer chains the nodes together .
     * the end is a tail
     * */
    struct Node {
        Bid bid ;
        /*data value stored is either string bidId, title, fund, amount.
         * Bid is the data structure bid is the  member name.
         * Node* is a  pointer,  next is a node pointer   */
        Node* next;

        /*Default constructor Node( )  next is the node variable.
         * Every time a node instance is created the default constructor is called and auto
         * initilize the next pointer "null" with  null pointer */
        Node() {
            next = nullptr;
        }
        Node(Bid abid) {
            bid = abid;
            next =nullptr;
        }
    }*head, *tail;
    /* part of the linkedList class, this class contains the head pointer.
     * The goal is to initlize as null. because when a new instance of linked list
     * its empty and not pointing at anything.
     * THE LINKED LIST STORES NODES
     * Append,
     * */
    int size = 0;
public:
    LinkedList();
    virtual ~LinkedList();
    void Append(Bid bid);
    void Prepend(Bid bid);
    void PrintList();
    void Remove(string bidId);
    Bid Search(string bidId);
    int Size();
};

/**
 * Default constructor
 */
LinkedList::LinkedList() {
    // Initialize housekeeping variables
    head = nullptr;
}

/**
 * Destructor
 */
LinkedList::~LinkedList() {
}

/**
 * Append a new bid to the end of the list
 */
void LinkedList::Append(Bid bid) {
    //  Implementing  logic that appends
    Node* node = new Node(bid);

    if (head == nullptr){
        head = node;
        tail = node;
    }
    else {
        if (tail != nullptr) {
            tail->next = node;
        }

    }
    // new node is always node;
    tail = node;
    size++;
}

/**
 * Prepend a new bid to the start of the list
 */
void LinkedList::Prepend(Bid bid) {
    //  Implement prepend logic
    Node* node = new Node(bid);

    if (head != nullptr){
        node->next = head;
    }
    head = node;

    size++;
}

/**
 * Simple output of all bids in the list
 */
void LinkedList::PrintList() {
    //  Implement print logic
    Node* current = head;

    //loop over each node looking for a match
    while (current != nullptr) {
        cout << current->bid.bidId << ": " << current->bid.title << " ! " <<
             current->bid.amount << " ! " << current->bid.fund << endl;
        current = current->next;
    }
}

/**
 * Remove a specified bid
 *
 * @param bidId The bid id to remove from the list
 */
void LinkedList::Remove(string bidId) {
    //  Implement remove logic
    if (head != nullptr){
        if (head->bid.bidId.compare(bidId) == 0) {
            Node* tempNode = head->next;
            delete head;
            head = nullptr;

        }

    }

    Node*  current = head;
    while (current->next != nullptr){
        if (current->next->bid.bidId.compare(bidId) == 0){
            Node* tempNode = current->next;

            delete tempNode;
            size++;
            return;
        }
        current = current->next;
    }
}

/**
 * Search for the specified bidId
 * LINEAR SEARCH ALGO.
 * @param bidId The bid id to search for
 */
Bid LinkedList::Search(string bidId) {
    // Implement search logic
    Node*  current = head;
    while (current != nullptr){
        if (current->bid.bidId.compare(bidId) ==0){
            return current->bid;
        }
        current = current->next;
    }
}

/**
 * Returns the current size (number of elements) in the list
 */
int LinkedList::Size() {
    return size;
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount
         << " | " << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
    Bid bid; //

    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);

    cout << "Enter title: ";
    getline(cin, bid.title);

    cout << "Enter fund: ";
    cin >> bid.fund;

    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    bid.amount = strToDouble(strAmount, '$');

    return bid;
}

/**
 * Load a CSV file containing bids into a LinkedList
 *
 * @return a LinkedList containing all the bids read
 */
void loadBids(string csvPath, LinkedList *list) {
   // cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++) {

            // initialize a bid using data from current row (i)
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            cout << bid.bidId << ": " << bid.title << " | " << bid.fund << " | " << bid.amount << endl;

            // add this bid to the end
            list->Append(bid);
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
 *
 * @param arg[1] path to CSV file to load from (optional)
 * @param arg[2] the bid Id to use when searching the list (optional)
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
        case 2:
            csvPath = argv[1];
            bidKey = "98109";
            break;
        case 3:
            csvPath = argv[1];
            bidKey = argv[2];
            break;
        default:
            csvPath = "/Users/inbox-11077/CLionProjects/Final/Lab3-2 copy/eBid_Monthly_Sales_unOrganized.csv"; //  must be full path
            bidKey = "98109";  // default arg[2]
    }

    clock_t ticks;

    LinkedList bidList;

    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;    // displays menu options
        cout << "  1. Enter a Bid" << endl;
        cout << "  2. Load Bids" << endl;
        cout << "  3. Display All Bids" << endl;
        cout << "  4. Find Bid" << endl;
        cout << "  5. Remove Bid" << endl;
        cout << "  6. prepend a  Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bid = getBid();
                bidList.Append(bid);
                displayBid(bid);

                break;

            case 2:
                ticks = clock();

                loadBids(csvPath, &bidList);   // implements loads bids method

                cout << bidList.Size() << " bids read" << endl;

                ticks = clock() - ticks; // current clock ticks minus starting clock ticks
                cout << "time: " << ticks << " milliseconds" << endl;
                cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

                break;

            case 3:
                bidList.PrintList();

                break;

            case 4:
                ticks = clock();

                bid = bidList.Search(bidKey);

                ticks = clock() - ticks; // current clock ticks minus starting clock ticks

                if (!bid.bidId.empty()) {
                    displayBid(bid);
                } else {
                    cout << "Bid Id " << bidKey << " not found." << endl;
                }

                cout << "time: " << ticks << " clock ticks" << endl;
                cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

                break;

            case 5:
                ticks = clock();
                bidList.Remove(bidKey);

                ticks = clock() - ticks;

                cout << "time: " << ticks << " clock ticks" << endl;
                cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;


                break;

            case 6:
                bid = getBid();
                bidList.Prepend(bid);
                displayBid(bid);

                break;


        }
    }

    cout << "Good bye." << endl;

    return 0;
}


