#include "type.h"
#include <iostream> //Preprocessor directives 
#include <fstream>
using namespace std;
//Overloaded < operator that returns a boolean result if the the destination on the left handed side it less that the destination on the rhs side 
bool flightRec::operator < (const flightRec & rhs) const{
	if(destination<rhs.destination){
		return true;
	}
	else{
		return false;
	}
}
//Overloaded operator that returns a boolean result if the two destinations and origins are equal. 
bool flightRec::operator == (const flightRec & rhs) const{
	if((origin == rhs.origin) && (destination == rhs.destination)){
		return true;
	}
	else{
		return false;
	}
}
//Overloading the << operator to print out the flight information 
ostream & operator << (ostream & os, const flightRec & f){
	os<<f.origin<<f.flightNum<<f.destination<<f.price;
	return os;
}
