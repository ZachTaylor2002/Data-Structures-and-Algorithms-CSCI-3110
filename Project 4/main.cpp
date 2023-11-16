PROGRAMMER: Zach Taylor
 CSCI 3110 
 Project 4
 Program Description: This program develops a flight itinerary for the user by using classes, STL vectors and lists. The program first reads in from a file to make the vector of citites and then reads from another file to read into and create the adjacency list (using the STL list to create the Flight map) that displays the avaliable flights to and from the Origin and Destination. The information is the origins, destinations, flight numbers and the price of the total flight. 
*/ 
#include "flightMap.h"
#include <iostream>   //Preprocessor directives 
#include <fstream>
#include <algorithm>
using namespace std;
int main() {
	//Creation of the oneMap object.
	FlightMapClass oneMap;

	//Declartions of the ifstream file_object and the other_object to be used when reading data fron the file
	ifstream file_object,other_object,test_object; 

	//Opening the cities.dat file for reading and sending in the file_object into the oneMap member function 
	file_object.open("cities.dat");
	oneMap.ReadCities(file_object);

	//Opening the flight.day file for reading and sending in the other_object into the oneMap member function 
	other_object.open("flights.dat");
	oneMap.BuildMap(other_object);

	//Printing out the Flight Map using the overloaded << operator 
	//oneMap.DisplayMap();
	string first_city;
	string next_city;
	//reading from the requests file to get the flight requests 
	test_object.open("requests.dat");
	while(test_object>>first_city){
		test_object>>next_city;
		//Calling the FindPath() function and sending in the origin and destination to print out the path   
		oneMap.FindPath(first_city,next_city);
	}

	
	//closing the flie objects once done reading 
	file_object.close();
	other_object.close();
	test_object.close();
}
