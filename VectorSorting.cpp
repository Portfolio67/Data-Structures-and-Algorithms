//============================================================================
// Name        : VectorSorting.cpp
// Author      : Shane Flaten
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU CODE
// Description : Vector Sorting Algorithms
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
    Bid() {
        amount = 0.0;
    }
};

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information using console (std::in)
 * @return Bid struct containing the bid info
 */
Bid getBid() {
    Bid bid;

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
 * Load a CSV file containing bids into a container
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
vector<Bid> loadBids(string csvPath) {
    cout << "Loading CSV file " << csvPath << endl;

    // Define a vector data structure to hold a collection of bids.
    vector<Bid> bids;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bids.push_back(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
    return bids;
} // vectors are safer than arrays

/**
 * Partition the vector of bids into two parts, low and high
 *
 * @param bids Address of the vector<Bid> instance to be partitioned
 * @param begin Beginning index to partition
 * @param end Ending index to partition
 */


int partition(vector<Bid>& bids, int begin, int end) {
    //return 0;  to test the quicksort()
    int low = begin;  // first condition to check is the low point that was passed
    int high = end;  // Second condition to check is the high point that was passed, it will be the ending

    // pick the middle
    int pivot = begin + (end - begin) / 2;

    bool done = false; //
    while (!done) {  //  condition for while loop to continue

        // keep incrementing low as long as its less than pivot // here we are comparing the two tiles
        while (bids.at(low).title.compare(bids.at(pivot).title) < 0) { // the condiiton does the testing, compare low title to bids high point
            ++low; // using title, start at low comparing up to pivot. if lower increment to low, until the smallest index is found
        }  // two at once this is the first half

        // keep decrementing high as long as it is less than pivot
        while (bids.at(pivot).title.compare(bids.at(high).title) < 0) {
            --high;  // upper half find its smallest half
        } // two at once this is the second half

        if (low >= high) { //after the two while loops are done we compare the  low to see if its higher than the high value.
            done = true;  //   if so exits while loop
        }
        else {
            //swap the low and high bids using built-in vector methods
            swap(bids.at(low), bids.at(high)); // were swapping the whole bid element low and high not just the title

            // After the swap will increment low and decrement high, move end points closer // passing throught the entire vector
            ++low;
            --high;
        }
    }
    return high; // returns the new highest value to be used in quicksort()
}


//Implement the quick sort logic over bid.title
/**
 * Perform a quick sort on bid title
 * Average performance: O(n log(n))
 * Worst case performance O(n^2))
 *
 * @param bids address of the vector<Bid> instance to be sorted
 * @param begin the beginning index to sort on
 * @param end the ending index to sort on
 */// method for selection sort,  must start with min or outer. needs 2 loops
void quickSort(vector<Bid>& bids, int begin, int end) { // in this case the entire vector will be passed in, zero is begin and the end of vector
    // then partition will figure out the mid point is.
    int mid = 0;

    // If zero of one bids to sort, then done
    if (begin >= end) {
        return;
    } // with partition() this keeps splitting it down until just two elements are compared for the left and right side

    // Partition bids into low and high parts and returns the midpoint. partion() is the first thing called
    mid = partition(bids, begin, end);// will be passed Bids vector, begin, and end points of vector

    // Recursivly call quicksort using midpoint value (begin to mid) using partition function
    quickSort(bids, begin, mid);  // second we call quicksort() again on the first half

    // Recursivly call quicksort using midpoint value (begin to mid)
    quickSort(bids, mid + 1, end); // call again using mid plus 1 and the end,  the second half
}

//  Implement the selection sort logic over bid.title

/**
 * Perform a selection sort on bid title
 * Average performance: O(n^2))
 * Worst case performance O(n^2))
 *
 * @param bid address of the vector<Bid>
 *            instance to be sorted
 */
void selectionSort(vector<Bid>& bids) {  // in selection sort we are not using pointers like we are in  quicksort, just the list.
    // Index to the current minimium bid
    int min; // we need to start a min pointer "start of list or outer one"

    // pos is the position within the bids that marks sorted/unsorted

    for (unsigned pos = 0; pos < bids.size();  ++pos) { // outer loop
        min = pos;  // save the min spot as zero for the first time through loop

        for (unsigned j = pos + 1; j < bids.size();  ++j) { // inner loop goes from beginning to end if min index is found then a swap is preformed.
            if (bids.at(j).title.compare(bids.at(min).title) < 0) {  // compare j1 to bids at title
                min = j; // cppreference.com  compare a class that has a method which conditions
            } // compare return conditions; if data less than arg, it returns a negative; match, return zero; if data on left, return larger number
        }//

        if (min != pos){ // this is envoked when a new min is found,
            swap(bids.at(pos), bids.at(min)); // with swap no need for temp var.
        }
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
int main(int argc, char* argv[]) { // takes arguments from the command line which is the path to csv file

    // process command line arguments
    string csvPath;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    default:
        csvPath = "/Users/inbox-11077/CLionProjects/Final/Lab4-2 copy/eBid_Monthly_Sales_unOrganized.csv";
        // argument to the path of the file
    }

    // Define a vector to hold all the bids.  This loads the whole csv file
    vector<Bid> bids;

    // Define a timer variable
    clock_t ticks;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Selection Sort All Bids" << endl;
        cout << "  4. Quick Sort All Bids" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            bids = loadBids(csvPath); // loads into a vector of bids already done and goes into a vector of Bids

            cout << bids.size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 2:
            // Loop and display the bids read
            for (int i = 0; i < bids.size(); ++i) {
                displayBid(bids[i]);
            }
            cout << endl;

            break;


            case 3:
                // Initalize timer variable before loading bids
                ticks = clock();

                // complete the  method call to load he bids
                selectionSort(bids);

                cout << bids.size() << " bids read" << endl;

                // calculate elapsed time and display result
                ticks = clock() - ticks; // current clock ticks minus starting clock ticks
                cout << "time: " << ticks << " clock ticks" << endl;
                cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

                break;

        //  Invoke the quick sort and report timing results
            case 4:
                // Initalize timer variable before laoding bids
                ticks = clock();

                // method call to load he bids
                quickSort(bids, 0, bids.size() - 1); // start and end adress passes, you dont have to sort the whole thing at once.

                cout << bids.size() << " bids read" << endl;

                // calculate elapsed time and display result
                ticks = clock() - ticks; // current clock ticks minus starting clock ticks
                cout << "time: " << ticks << " clock ticks" << endl;
                cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

                break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
