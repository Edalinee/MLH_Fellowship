/*
 * Customer Database focusing on enum types 
 * structs, pointers, and memory manipulation
 * Project 7, CRM part 2
 * EE 312, Fall 2019
 */

#include <stdio.h>
#include "UTString.h"
#include "Customer.h"
#include "CustomerDB.h"
#include <iostream>

using namespace std;

// ---- Prototypes----------
void readString(UTString&);
void readNum(int&);
void removeDatabase(UTString utString);
//---------------------------------------


CustomerDB database; //Declaring customer master 'database' to hold inventory and records or purchase

int num_bottles = 0; //Initalling all inventory items
int num_rattles = 0;
int num_diapers = 0;

// -----------------RESET METHOD ---------------------------
// I:none, O:None Goal- 
// clear the inventory and reset the customer database to empty
void reset(void) {
    database.clear();
    num_bottles = 0;
    num_rattles = 0;
    num_diapers = 0;
}
//---------------------------------------------------------

//-------------SelectInventItem function orgin---------------------------------
//I: UTString attempting to find O: pointer to the inventory record  w/ item type num
// Goal- easier to navigate thru inventory/database thru global vars
int* selectInventItem(UTString word) {
    if (word == "Bottles") {
        return &num_bottles;
    } else if (word == "Diapers") {
        return &num_diapers;
    } else if (word == "Rattles") {
        return &num_rattles;
    }

    // should not reach case based oon test cases - different in allowed invent items changes*/
    return 0;
}
//--------------------------------------------------------------------------

// -------------- SelectInventItem function--------------------------------------------
// I: UTString attempting to find, Customer add O: pointer to customer record w/ item type num
// similar to func above -> returns for specific customers/ useful for summar method  
int* selectInventItem(UTString word, Customer& cust) {
    if (word == "Bottles") {
        return &cust.bottles;
    } else if (word == "Diapers") {
        return &cust.diapers;
    } else if (word == "Rattles") {
        return &cust.rattles;
    }

    //should not reach case based on test cases
    return 0;
}
//--------------------------------------------------------------------------------------------


 //---------------------------findMax function --------------------------------
 //I: UTString to search for max of O: Pointer to customer name
 // Goal- To find the which customers have the maximum amount of the item type passed in the parameter
Customer* findMax(UTString type) {
    Customer* result = 0; //initalizing to zero in case that there is NONE of the item type passed
    int max = 0; //tracking max val 
    for (int k = 0; k < database.size(); k += 1) {
        Customer& cust = database[k]; //not too concerned on runtime on this one, simple search
        int *p = selectInventItem(type, cust);
        if (*p > max) {
            max = *p;
            result = &cust;
        }
    }

    return result;
}
//--------------------------------------------------------------------------------



//--------------------------findCustomerNumber function---------------------------------
// I: none O: number of Customers 
// Finds num of Customers while skipping the Customers that have zero items or did not make
// succesful buy ->helper function<-
int findCustomerNum() {
    //goes through customer database, counting the number of customers, not adding any duplicates
    int res = 1;
    for (int i = 1; i < database.size(); i++) {
            if (database[i].rattles != 0 || database[i].bottles != 0 || database[i].diapers != 0)
                res++;
            // If not printed earlier, then print it

        }
        return res;

}
//-----------------------------------------------------------------------------------------------


//--------------------------processPurchase method (req)--------------------------------------
//I:none O:none
// Read in a purchase from the input file, Parse data, Take num from inventory and give to customer
// If cust amount is not available in inventory -> purchase in unsuccesful
void processPurchase() {
    int itemnumber = 0;
    UTString name;
    UTString type;

    //reading the customer name, type and item number from the file
    readString(name);
    readString(type);
    readNum(itemnumber);

    if(itemnumber > 0) {
        // database[“Phil”].bottles += 5
        if (type == "Bottles") {
            if (itemnumber <= num_bottles) {
                database[name].bottles += itemnumber;
                num_bottles -= itemnumber;
            } else {
                cout << "Sorry " << name.c_str() << ", we only have " << num_bottles << " Bottles" << endl;
                //removeDatabase(name);
            }
        }

        if (type == "Diapers") {
            if (itemnumber <= num_diapers) {
                database[name].diapers += itemnumber;
                num_diapers -= itemnumber;
            } else {
                cout << "Sorry " << name.c_str() << ", we only have " << num_diapers << " Diapers" << endl;
                //removeDatabase(name);
            }
        }

        if (type == "Rattles") {
            if (itemnumber <= num_rattles) {
                database[name].rattles += itemnumber;
                num_rattles -= itemnumber;
            } else {
                cout << "Sorry " << name.c_str() << ", we only have " << num_rattles << " Rattles" << endl;
                //removeDatabase(name);
            }
        }


    }

}
//-------------------------------------------------------------------------------------------------


//-------------------------processSummarize (req)---------------------------------------------------
// I: none O:none
// Print out Summary message with remaining inventory stock after all purchases and the customers with 
// Maximum amount of each item type
void processSummarize() {

  /*  UTString p; 
    UTString a;
    UTString s;
    int p1 =0 ,a1 =0, s1 =0;
    if(findMax("Bottles")) { p = ((findMax("Bottles"))->name);  p1 = database[p].bottles;}
    if(findMax("Diapers")) { a = ((findMax("Diapers"))->name); a1 = database[a].diapers; }
    if(findMax("Rattles")) {s  = ((findMax("Rattles"))->name); s1 = database[s].rattles;} */
//thought I'd keep this in there ^^, having a lot of troubles with acessing the right customer name

    //prints out written summary
    cout << "There are " << num_bottles << " Bottles, " << num_diapers <<
    " Diapers and " <<num_rattles << " Rattles in inventory" << endl;
    cout << "we have had a total of " << database.size() << " different customers" << endl;
    UTString* name1 = new UTString("Bottles");
    if( (findMax("Bottles") != 0))
    cout << ((findMax(*name1))->name).c_str() << " has purchased the most Bottles ("
    << (database[(findMax(*name1))->name].bottles) << ") " << endl; //gotta love memory!!

    else  cout << "no one has purchased any Bottles" << endl;


    if( (findMax("Diapers") != 0))
    cout << ((findMax("Diapers"))->name).c_str() <<" has purchased the most Diapers ("
    << database[((findMax("Diapers"))->name)].diapers << ") " << endl;
    else  cout << "no one has purchased any Diapers" << endl;

    if( (findMax("Rattles") != 0)) {
        cout << ((findMax("Rattles"))->name).c_str() << " has purchased the most Rattles ("
                << (database[(findMax("Rattles"))->name].rattles)      << ")" << endl;
    }
    else  cout << "no one has purchased any Rattles" << endl;

}
//-------------------------------------------------------------------------------------------------------------



//------------------------process Inventory (req) -------------------------------------------------------------
// I: none O: none
// On Inventory Commands, adds to global varible containing customer database for each item type
void processInventory() {

    int itemnumber = 0;
    UTString type;

    //Grabbing the type of item and quantity
    readString(type);
    readNum(itemnumber);

    if(type == "Bottles") num_bottles += itemnumber;
    else if(type == "Diapers") num_diapers += itemnumber;
    else if(type == "Rattles") num_rattles += itemnumber;

}
//--------------------------------------------------------------------------------------------------------------