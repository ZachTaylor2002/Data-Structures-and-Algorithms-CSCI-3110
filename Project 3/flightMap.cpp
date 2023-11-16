#include "flightMap.h"
#include <fstream>         
#include <string>      //Pre-Processor directives
#include <iostream> 
#include <vector>     
#include <list>
#include <algorithm>
#include <iomanip>
//Constructor of the FlightMapClass that sets the number of cites to zero and the flight_map pointer to Null
FlightMapClass::FlightMapClass(){
	number_of_cities = 0;
	flight_map = NULL;
}
//Deconstructor of the FlightMapClass that de-allocated 
FlightMapClass::~FlightMapClass(){
	delete[] flight_map;
}
//Getter method of the FlightMaoClass that returns how many number of cities we are dealing with
int FlightMapClass::Get_num() const{
	return number_of_cities;
}
//Read_cities FlightMapClass member function
//Pre-Condition: The member function of the FlightMapClass takes in the ifstream file_object and reads in the cities to create the vector of citites array.
//Post-Condition: Creates the STL vector of cities read in from the file 
void FlightMapClass::Read_cities(ifstream &file_object){
	//declaring string variables of city_num and city_names to be used in reading from the file
	string city_num;
	string city_names;

	//Reading in the first line from the file (cities.dat) which includes the string amount of the number of cities
	getline(file_object,city_num);

	//conversion of the string of number of cities to an integer
	number_of_cities = stoi(city_num);

	//using the STL vector member function reserve to reserve the number of spaces for each city that we read in
	vector_of_cities.reserve(number_of_cities);

	//Reading from the file to get the different names of the cities and to push back to the vector of cities once we have read one city
	while(getline(file_object, city_names)){
		vector_of_cities.push_back(city_names);
	}

	//Using the sort member function to sort the names of the cities in Alphabetical order starting with the beginning of the vector to the end of the vector of cities. 
	sort(vector_of_cities.begin(),vector_of_cities.end());
	//Testing purpose
	/*vector<string>::iterator it;
	for(it=vector_of_cities.begin();it!=vector_of_cities.end();it++){
		cout<<*it<<endl;
	}*/
}
//Read_and_build_map FlightMapClass member function that takes in a file object
//Pre-condition: This function reads in from the (flight.dat) data file 
//Post-condition: The Flight Map (adjaceny list) is created 
void FlightMapClass::Read_and_build_map(ifstream & file_object){
	//Allocation of the list of flightRec for the number of cities 
	flight_map = new list<flightRec> [number_of_cities]; 
	
	//Declaring temporary variables to hold the information that is read from the file
	int flight_number,price;
	string origin,destination;

	//Declaration of a struct of One_flight
	flightRec One_flight;

	//Reading from the file and storing the information into the approiate variables
	while(file_object>>flight_number>>origin>>destination>>price){
		
		//Then storing the information into the One_flight struct 
		One_flight.flightNum = flight_number;
		One_flight.origin = origin;
		One_flight.destination = destination;
		One_flight.price = price;

		//Using the for loop to iterate through the vector of cities until we find one that correlates with the same orgin as the One_flight struct 
		for(int index = 0;index<number_of_cities;index++){
			
			//Once we find one that matched, we can then push back the information for that flight into the list of flight map creating the adjacency list of Flight Map
			if(vector_of_cities[index] == One_flight.origin){
				flight_map[index].push_back(One_flight);
			}
		}
		//Using the ignore method to ignore characters
		file_object.ignore(100,'\n');
	}
	return;
}
//Overloading the << operator of the FlightMapClass to display the information of the FlightMap 
//Pre-Condition: This function takes in the ostream operator and the FlightMapClass object
//Post-Condition: Prints and displays the FlightMap for the user to see the different types of flights and the information for that flight
ostream & operator << (ostream & os, const FlightMapClass & rhs){
	
	//Printing of the header for the Flight information that has the sub-titles for each category for the flight information
  os<<left<<setw(24)<<"       Origin "<<setw(15)<<"Destination"<<setw(9)<<"Flight"<<"Price"<<endl;
  os<<"======================================================"<<endl;
	os<<endl;

	//For loop to iterate through the number of cities 
  for(int index=0; index<rhs.number_of_cities; index++){

		//Declaration of the itr iterator so that we can iterate through the list of flightRec 
    list<flightRec>::iterator itr;
		
		//Sorting the information in Alphabetical order
		rhs.flight_map[index].sort();

		//Printing of the From and To using the set width function and the vector of cities that contain the origins of all the flights
    os<<" From "<<rhs.vector_of_cities[index]<<setw(18-rhs.vector_of_cities[index].length())<<" to: ";

		//Integer counter varaible used to keep track if we need to have a new_line or not
    int counter = 0;

		//For loop to iterate through the entire flight_map 
    for(itr = rhs.flight_map[index].begin(); itr != rhs.flight_map[index].end(); itr++){
			
			//If the iterator does not equal to being (meaning its not the first one in the flight_map) we can setw accordingly 
      if(itr != rhs.flight_map[index].begin()){
        os<<setw(24)<<left<<"";
				os<<setw(15)<<itr->destination;
        os<<setw(9)<<itr->flightNum;
        os<<"$"<<itr->price<<endl;
      }
			//else then this is the first row of information in the list then we can spaceout and setw accordingly 		
			else{
        os<<setw(15)<<itr->destination;
        os<<setw(9)<<itr->flightNum;
        os<<"$"<<itr->price<<endl;
				//Increment counter since it is not the first one in the row
				counter++;
			}
			
        }
				//If the counter is equal to zero meaing that there was nothing in the first row (so no information) then we can insert a new line 
      if(counter == 0){
        os<<endl;
      }
    }
	//Returning os
    return os;
}
