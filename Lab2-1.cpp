//============================================================================
// Name        : Lab2-2.cpp
// Author      : Shane Flaten
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU CODE
// Description : Lab 2-2 Up to Speed in C++, Part 2
//============================================================================

#include <algorithm> // THe angle brackets are system libraries, are included in the c++ runtime.
#include <iostream>
#include <time.h>

// To use the Reference the CSVParser library I include it here, notice I am including the header file.

#include "CSVparser.hpp" // This is a non-standard C++ library, or user defined library.
// this causes the program to open up the source file.

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

struct Bid {
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.title << " | " << bid.amount << " | " << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
    Bid bid;

    cout << "Enter title: ";
    cin.ignore();
    getline(cin, bid.title);

    cout << "Enter fund: ";
    cin.ignore();
    getline(cin, bid.fund);


    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    bid.amount = strToDouble(strAmount, '$');

    return bid;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
vector<Bid> loadBids(string csvPath) {   // the return is vector<Bid> ; case 2 uses this
    // ZYbooks 2.6 vector<dataType> identifier(numElements);
    vector<Bid> bids;  // constructs a vector,  also this is the value returned

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath); // this loads the csv file
    // uses the csv parser library. Ths creates an instance of it
    // and gives it the path of the file.   It will store it in a variable called file.
    cout << "THis file row count" << file.rowCount() << endl;
	// loop to read rows of a CSV file
	for (unsigned int i = 0; i < file.rowCount(); ++i) {  // This for loop iterates over the entire row count.
	    /*
	    // the rows into the parsed file structure. Once we create the file loaded it up into memory for the fore loop
        // method to create a vector without specifing size first do do this first  create a structure called Bids.
        // then make a seperate instance inside that called bid and stores the values from the file into it.
        //THen output the information in a test output, then store it on the vector,  then return the vector
        */
        // creates a data structure to hold data from each row and add to vector
        Bid bid; // local variable and temporary bid inside the for loop
        //   the use of i in the index will iterate the rows
        bid.title = file[i][0];  // in the csv file the title is the first column, I access the vector like an array
        bid.fund = file[i][19]; // in the csv file the title is the 8th column
        bid.amount = strToDouble(file[i][4], '$'); // this is a double so we will use the string to double method.
        // The strToDouble will get a value passed to it from the csv file.

        // testing debugging output statement will print to structure.
        cout << "Item " << bid.title << ". Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

        // now that bid defined, I will put it into the vector. I will use the push_back vector method
        bids.push_back(bid); // this method gets the bid that was just created.
    }
    return bids; // returns the variable name bids
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
int main(int argc, char* argv[]) { // pass the path to the file to be processed, it will take anyhting in the path

    // process command line arguments
    string csvPath;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    default:
        csvPath = "/Users/inbox-11077/CLionProjects/Lab2-1/eBid_Monthly_Sales.csv";
    }

    //  Defines a vector to hold all the bids
    // ZYbooks 2.6 vector<dataType> identifier(numElements);
    vector<Bid> theBids;

    // Define a timer variable of the time.h library
    clock_t ticks;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Enter a Bid" << endl;
        cout << "  2. Load Bids" << endl;
        cout << "  3. Display All Bids" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) { // when the user types 1,2,3 it will envoke the case statement.
        case 1:
        	cout << "Not currently implemented." << endl;

            break;
        case 2:
            //  Initializes a timer variable before loading bids
            ticks = clock();

            // The method call to load the bids
            theBids = loadBids(csvPath); // uses the loads bids method, which will need a csv path passed to it.

            //Calculates the elapsed time and display result
            ticks = clock() - ticks; //current clock ticks minus starting clock ticks
            cout << "time: " << ticks << "milliseconds" << endl;
            cout << "time: " << ticks*1.0/CLOCKS_PER_SEC << "seconds" << endl; // CLOCKS_PER_SEC part of time.h


            break;
            case 3:
                // Loop and display the bids read
                for (int i = 0; i < theBids.size(); ++i) {  // uses the variable theBids a vector and size method

                    displayBid(theBids.at(i)); // the function displayBid() gets one bid at a a time
                }
                cout << endl;

                break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
//CmakeLists.text
/*
 * CMakeLists.txt file contains a set of directives and instructions describing
 * the project's source files and targets (executable, library, or both).
 * https://www.jetbrains.com/help/clion/cmakelists-txt-file.html
 *
 cmake_minimum_required(VERSION 3.13)  # CMake version check
project(simple_example)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES main.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(simple_example ${SOURCE_FILES})
 *
 * */

//errors  I used the whole file path

/*
 * libc++abi.dylib: terminating with uncaught exception of type csv::Error: CSVparser : Failed to open eBid_Monthly_Sales_Dec_2016.csv
 * */