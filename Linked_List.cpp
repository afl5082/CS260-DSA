//============================================================================
// Name        : LinkedList.cpp
// Author      : Your Name
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Lab 3-3 Lists and Searching
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;
//https://www.youtube.com/watch?v=psJtcFpoUdY
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
// Linked-List class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a linked-list.
 */
class LinkedList {

private:

	struct node {
		Bid bids; //holding a bid instance
		node *next; //next variable stores memory address of the struct
	};

	// alias for node pointer (memory address of node)
	typedef struct node* nodePtr;

	// defining pointer variables for memory positions in the List
	nodePtr head;
	nodePtr curr;
	nodePtr temp;
	nodePtr tail; //is this needed

	//node *head, *tail;

	//list<node> listofBids;

    // FIXME (1): Internal structure for list entries, housekeeping variables

public:
    LinkedList();
    virtual ~LinkedList();
    void Append(Bid bid);
    void Prepend(Bid bid);
    void PrintList();
    void Remove(string bidId);
    Bid Search(string bidId);
    int Size();
    void hello();
};

/**
 * Default constructor
 * set default values for head, current and temp
 */
LinkedList::LinkedList() {
    // FIXME (2): Initialize housekeeping variables
	head = NULL;
	curr = NULL;
	temp = NULL;
	tail = NULL;

}

/**
 * Destructor
 */
LinkedList::~LinkedList() {
	nodePtr n = new node;

	curr = head;
	while (curr != 0) {
		n->next = curr->next;
		delete curr;
		curr = n->next;
	}
	head = NULL;

}

/**
 * Append a new bid to the end of the list
 */
void LinkedList::Append(Bid bid) {
    // FIXME (3): Implement append logic
	// if head is not blank, current tail points to n and bid becomes new tail

		nodePtr n = new node;
		n->bids = bid;
		n->next = NULL;

	if (head == NULL){
		head = n;
		tail =n;

	}
	else {
		tail->next = n;
		tail=n;
	}



}

/**
 * Prepend a new bid to the start of the list
 */
void LinkedList::Prepend(Bid bid) {
    // FIXME (4): Implement prepend logic
	// assigning bid parameter to the head pointer and shifting bid next to current head
	nodePtr n = new node;
	n->bids = bid;
	n->next = NULL;

	if (head != NULL){
		n->next = head;
		head = n;
	}
	// if head isn't present (list is blank) assign to head
	else {
		head = n;
	}
}

/**
 * Simple output of all bids in the list
 */
void LinkedList::PrintList() {
    // FIXME (5): Implement print logic
	//iterating over until last pointer points to nothing, display all bid data for each node
	curr = head;
		while(curr->next != NULL){
			cout << curr ->bids.title << " "; //maybe &bids?
			cout << curr ->bids.bidId << " ";
			cout << curr ->bids.amount << " ";
			cout << curr ->bids.fund << endl;
			curr = curr ->next;
		}

}

/**
 * Remove a specified bid
 *
 * @param bidId The bid id to remove from the list
 */
void LinkedList::Remove(string bidId) {
    // FIXME (6): Implement remove logic
	curr = head;
	// if bidID is the first ID in the list
	if (head->bids.bidId == bidId){
		head = head->next;
		delete curr;
		return;
	}


	// iterating until last pointer points to nothing
	// when found, delete that node and return
	while(curr->next != NULL){

		if (curr->bids.bidId == bidId){

			temp->next = curr->next;
			delete curr;
			return;
		}
		temp = curr;
		curr = curr ->next;
	}
	// if while loop finishes and nothing is found, print:
	cout << "No ID Found";



}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */


Bid LinkedList::Search(string bidId) {
    // FIXME (7): Implement search logic
	// searches bidID parameter, iterates through list until last pointer points to nothing

	//creating default Bid to hold the node that is found
	Bid returnbid;
	curr = head;
	while(curr->next != NULL){
		if (curr->bids.bidId == bidId){

			returnbid = curr->bids;
		}
		curr = curr ->next;
	}


	return returnbid;

}

/**
 * Returns the current size (number of elements) in the list
 */
int LinkedList::Size() {
	//looping over pointers until final pointer points to nothing, counts iterations
	int size = 0;
	curr = head;

	while(curr->next != NULL){
			size++;
			curr = curr->next;
		}
	return size;
}


//test function
void LinkedList::hello() {
    cout << "Testing to see if this works";

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
 * Load a CSV file containing bids into a LinkedList
 *
 * @return a LinkedList containing all the bids read
 */
// *list is of pointer type
void loadBids(string csvPath, LinkedList *list) {
   cout << "Loading CSV file " << csvPath << endl;

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

      cout << "Done Loading" << endl;;
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
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98109";
    }

    clock_t ticks;

    //instance of LinkedList class
    LinkedList bidList;

    Bid bid;




    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Enter a Bid" << endl;
        cout << "  2. Load Bids" << endl;
        cout << "  3. Display All Bids" << endl;
        cout << "  4. Find Bid" << endl;
        cout << "  5. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        // test case that is not given to user
        case 0:
        	cout <<  "Is this working?";
        	bidList.hello();
        	break;

        case 1:
            bid = getBid();
            bidList.Append(bid);
            displayBid(bid);

            break;

        case 2:
            ticks = clock();

            // passing memory address of bidList
            loadBids(csvPath, &bidList);

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
            bidList.Remove(bidKey);
            cout << bidList.Size();
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
