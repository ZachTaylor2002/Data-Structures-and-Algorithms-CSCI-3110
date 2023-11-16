/* 
 PROGRAMMER: Zach Taylor
 CSCI 3110 
 Project 3
 Program Description: This program develops a flight map for the user by using classes, STL vectors and lists. The program first reads in from a file to make the vector of citites and then reads from another file to read into and create the adjacency list (using the STL list to create the Flight map) that displays to the user what flights are avaible and the information to that particular flight. The information is the origin, destination, flight number and the price of the flight
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
	ifstream file_object,other_object; 

	//Opening the cities.dat file for reading and sending in the file_object into the oneMap member function 
	file_object.open("cities.dat");
	oneMap.Read_cities(file_object);

	//Opening the flight.day file for reading and sending in the other_object into the oneMap member function 
	other_object.open("flights.dat");
	oneMap.Read_and_build_map(other_object);

	//Printing out the Flight Map using the overloaded << operator 
	cout<<oneMap;

	//closing the flie objects once done reading 
  file_object.close();
	other_object.close();
}
