//============================================================================
// Name        : HashTable.cpp
// Author      : John Watson
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <algorithm>
#include <climits>
#include <iostream>
#include <string> // atoi
#include <time.h>

#include "CSVparser.hpp"
//   search finds the first one in the vector as seen in line 107, 139 , 178, 287
using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

const unsigned int DEFAULT_SIZE = 18000;  // default table size.  the tableSize "line 74" allows to change the table size. 179 is the number of buckets the csv file will be divided out into. by changing the hash method or file

// forward declarations
double strToDouble(string str, char ch);
// We are going to hold a bid inside the node
// define a structure to hold bid information
struct Bid {    //A data structure is a group of data elements grouped together under one name. These data elements, known as members, can have different types and different lengths.
    string bidId; // unique identifier, Bid reads data as a string, so the bid ID needs to be converted to a string
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

//============================================================================
// Hash Table class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a hash table with chaining.
 */
class HashTable {

private:
    //  Define structures to hold bids
    struct Node {  //  Bid is held inside the node
        Bid bid;
        //unsigned abid;
        unsigned key; // we need a key value for the hash. unsigned is used instead of int because there cant be a negative index.
        Node* next; // node pointer to the next to implement the chaining

        Node() { // constructor has the name of the class,  this is the default constructor
            key = UINT_MAX; // Initialize Maximum value for an object of type unsigned int https://www.cplusplus.com/reference/climits/ we can test  a key to see if its been used or not
            next = nullptr; //nullptr is implicitly convertible and comparable to any pointer type;  https://www.geeksforgeeks.org/understanding-nullptr-c/
        }

        // Initialize with a bid . second constructor that takes a bid
        Node(Bid abid) : Node() { // takes a Bid called abid.  NOTE the COLON forces invoking of the default before this constructor.
            bid = abid; // the bid inside the node is going to be assinged the abid
        }

        // Initailize with a bid and a key
        Node(Bid abid, unsigned aKey) : Node(abid) { //the colon calls the second constructor giving it aBid
            key = aKey; // Run down of creating a struct with 2 paremeters bid and key passed: line 67 Node(aBid) will call second contructor, that constructor Node() on 62 will call the base defualt constructor and it checks definitions, then go back to line 63 and assign the bid then it will go to the third constructor and add the key to it.
        }
    };

    vector<Node> nodes;// This vector will hold nodes like a linked list

    unsigned  tableSize = DEFAULT_SIZE; // we have to be able to manage the size.   unsigned integers are well-suited for networking and systems with little memory, because unsigned integers can store more positive numbers without taking up extra memory
    unsigned int hash(int key);

public:
    HashTable();
    HashTable(unsigned size); // same as the nodes
    virtual ~HashTable();
    void Insert(Bid bid);  // this is a struct in c++
    void PrintAll(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);  // search method
};

/**
 * Default constructor
 */
HashTable::HashTable() {
    //  Initialize the structures used to hold bids
    nodes.resize(tableSize);
}

HashTable::HashTable(unsigned size) { // this first saves the table size
    this->tableSize = size;
    nodes.resize(tableSize); // there cant be call a constructor because its based on table size
}

/**
 * Destructor
 */
HashTable::~HashTable() {  // erase member function of a vector https://en.cppreference.com/w/cpp/container/vector/erase the begin method eliminates the need for an iterator
    // Implement logic to free storage when class is destroyed
    nodes.erase(nodes.begin()); // nods is the structure to erase
}

/**
 * Calculate the hash value of a given key.
 * Note that key is specifically defined as
 * unsigned int to prevent undefined results
 * of a negative list index.
 *
 * @param key The key to hash
 * @return The calculated hash
 */
unsigned int HashTable::hash(int key) {  // passing in the key value, an int using atoi,  from the file and use modulus division, and use table size in case we change the size of the table. to calculate a hash we will use the modulus operation
    //Implement logic to calculate a hash value
    return key % tableSize;  // we are retuning an unsigned int,
}

/**
 * Insert a bid
 *
 * @param bid The bid to insert
 */
void HashTable::Insert(Bid bid) {  //we are inserting a new bid which is passed here.
    // Implement logic to insert a bid
    unsigned key = hash(atoi(bid.bidId.c_str())); //THIS IS THE KEY; calls the hash method, bid.bidId is an object we want a string of Char. so we use c_str.   atoi method converts a string to int.  this goes to the hash function line 110
// when we insert a bid the first thing is to create the key so we call the hash function, we look for the bidId we need it to be a string, then we make it an integer. that gives us a key.

// try a retrieve node using the key
    Node* oldNode = &(nodes.at(key));// look for the old node using the Node at function, by giving it the key or index into the vector. the pointer just gives us the value. The adress is &(adress of operator)
    // if no entry found for this key
    if (oldNode == nullptr){
       Node* newNode = new Node(bid, key);
       nodes.insert(nodes.begin() + key, (*newNode));
    } else {
        // node was found
        if (oldNode->key == UINT_MAX){
            oldNode->key = key;
            oldNode->bid = bid;
            oldNode->next = nullptr;

        } else {
            // find the next node (last one)
            while (oldNode->next != nullptr){   // we are going to walk down the chain, if the old node is not null we go to the next one
                oldNode = oldNode->next;// we get to the
            }
            oldNode->next = new Node(bid, key);// when we have found a null, we make a new node giving it the bid and key; and it is the new end.
        }
    }
}
/**
 * Print all bids
 */
void HashTable::PrintAll(Bid bid) {
    // Implement logic to print all bids
    for (unsigned  int i = 0; i < nodes.size(); i++) {  // takes the list nodes.at(i).bidId
        cout << nodes[i].bid.bidId  << ": "  << nodes[i].bid.title  << " | "  << nodes[i].bid.amount << " | " << nodes[i].bid.fund << endl;
    }

}
/**
 * Remove a bid
 *
 * @param bidId The bid id to search for
 */
void HashTable::Remove(string bidId) {
    // Implement logic to remove a bid
    unsigned key = hash(atoi(bidId.c_str())); // call hash function to get a key
    nodes.erase(nodes.begin()) + key; // the offset is the beginning of the node plus the key index
}
/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid HashTable::Search(string bidId) { // in order to search we need to find a key   THIS is the default bid
    Bid bid;

    // Implement logic to search for and return a bid

    // calculate the key for the bid
    unsigned key = hash(atoi(bidId.c_str())); // THIS IS THE KEY ,  we find using the key parameter
    cout << "the key is : " << key << endl;

    // try and retreive node using the key
    Node* node = &(nodes.at(key)); // just a plain node and not the old old node
    // if no key entry found
    if (node == nullptr || node->key == UINT_MAX) { //fist we check if the node is a nullpointer, or if its a new unitilized node, which is an empty bid
        cout << "no key entry found." << endl;
        return bid;  // the empty bid

    }
    // if node found that matches key.      because this is a hash table there can be two nodes with the same hash.
    if (node != nullptr && node->key != UINT_MAX && node->bid.bidId.compare(bidId) == 0){ //fist we check if its a null node, then we check if its a new unitilized node.  node->bid.bidId is the found node, we check to to if the nodes id is equal to the one passed in.  If thats the case we found it
        cout << " node found that matches key." << endl;
        return node->bid;

    }

    // walk the linked list to find the match
    while (node != nullptr){    // if multiple values with the same hash
        if (node->key != UINT_MAX && node->bid.bidId.compare(bidId) == 0) { // thats a match
            return node->bid;  // if its a match we return that nodes bid
        }
        node = node->next;// if its not a match
    }
    cout << "nothing was found!!!!";

    return bid;
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
void loadBids(string csvPath, HashTable* hashTable) {
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
            hashTable->Insert(bid);  // inserts new data into hashtable a que
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
int main(int argc, char* argv[]) {   // because theres is a size and a constructor, you could add another parameter.

    // process command line arguments
    string csvPath, searchValue; // key is a key word, so we refactor in the ide to rename all at once.
    switch (argc) {
        case 2:
            csvPath = argv[1]; // pass in the path as an argument
            searchValue = "90001"; // pass in the bid key, this  is the default
            break;
        case 3:
            csvPath = argv[1];
            searchValue = argv[2];
            break;
        default:
            csvPath = "/Users/inbox-11077/CLionProjects/Lab5-2 v.1/eBid_Monthly_Sales.csv";
            searchValue = "90001";
    }

    // Define a timer variable
    clock_t ticks;  // this is for counting things

    // Define a hash table to hold all the bids
    HashTable* bidTable;  // the bid table is the hash

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

            case 1: // for loading everything
                bidTable = new HashTable();

                // Initialize a timer variable before loading bids
                ticks = clock();

                // Complete the method call to load the bids
                loadBids(csvPath, bidTable);

                // Calculate elapsed time and display result
                ticks = clock() - ticks; // current clock ticks minus starting clock ticks
                cout << "time: " << ticks << " clock ticks" << endl;
                cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
                break;

            case 2:   // prints all

                bidTable->PrintAll(bid);
                break;

            case 3: // grabs the current clock, call a search
                ticks = clock();

                bid = bidTable->Search(searchValue);

                ticks = clock() - ticks; // current clock ticks minus starting clock ticks

                if (!bid.bidId.empty()) {
                    displayBid(bid);
                } else {
                    cout << "Bid Id " << searchValue << " not found." << endl;
                }

                cout << "time: " << ticks << " clock ticks" << endl;
                cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
                break;

            case 4:  //  removes
                ticks = clock();
                bidTable->Remove(searchValue);
                ticks = clock() - ticks;
                cout << "time: " << ticks << " clock ticks" << endl;
                cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

                break;
        }
    }
    cout << "Good bye." << endl;
    return 0;
}

