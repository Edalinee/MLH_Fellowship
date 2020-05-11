/*
 * Name: Edaline Engmann
 * EID: ee7228
 * Project 7, CRM part 2
 * EE 312, Fall 2019
 */
#include <iostream>
#include <cassert>
#include "UTString.h"
#include "CustomerDB.h"

using namespace std;

const int default_capacity = 1;

Customer::Customer(UTString name) { // done, please do not edit
    this->bottles = 0;
    this->rattles = 0;
    this->diapers = 0;
    this->name = name;
}

CustomerDB::CustomerDB(void) { // done, please do not edit
    this->capacity = default_capacity;
    this->data = new Customer[this->capacity];
    this->length = 0;
}

int CustomerDB::size(void) { // done, please do not edit
    return this->length;
}

CustomerDB::~CustomerDB(void) { // done, please do not edit
    delete[] this->data;
}



void CustomerDB::clear(void) { // done, please do not edit
    delete[] this->data;
    this->capacity = default_capacity;
    this->data = new Customer[this->capacity];
    this->length = 0;
}

Customer& CustomerDB::operator[](int k) { // done, please do not edit
    assert(k >= 0 && k < this->length);
    return this->data[k];
}

Customer& CustomerDB::operator[](UTString name) { // not done, your effort goes here
    //if(CustomerDB::isMember(name)){
        for(int i = 0; i < length; i++){
        if(this->data[i].name == name)
        return this->data[i];
        }

   // }
  //  else {
        if( this->capacity -1  == this-> length){
            Customer* newArr  = new Customer[this->capacity * 2 ];

            //memcpy( newArr, this->data, this->capacity * sizeof(Customer) ); //need to perform a deep copy?
            for( int i =0; i < length; i++){
                newArr[i].name = data[i].name;
                newArr[i].rattles = data[i].rattles;
                newArr[i].bottles = data[i].bottles;
                newArr[i].diapers = data[i].diapers;
            }

            this->capacity = (this->capacity)*2;
            delete [] this->data;
            this->data = newArr;
        }
            //just add customer to array and return address
            Customer* newCust = new Customer(name);
            this->data[length] = *newCust;
            this->length +=1;
            delete(newCust);
            return this->data[length -1 ];




    //}



}

bool CustomerDB::isMember(UTString name) { // not done, your effort goes here
    for (int k = 0; k < size(); k++) {
        if (name == (this->data[k].name)) { //incrementing k by just one could be a problem
            return true;
        }
        return false;
    }
}
