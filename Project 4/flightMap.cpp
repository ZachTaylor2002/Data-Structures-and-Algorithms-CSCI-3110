// Implement the flightMap class defined in flightMap.h
#include "flightMap.h"
#include <algorithm>
#include <string>
#include <fstream>  //Pre-Processor directives
#include <iomanip>
#include <iostream>
#include <list>
#include <string> 
#include <vector>
#include <stack>
#include <stdbool.h>
// Constructor of the FlightMapClass that sets the number of cites to zero and
// the map pointer to Null
FlightMapClass::FlightMapClass() {
  size = 0;
  map = NULL;
}
// Deconstructor of the FlightMapClass that de-allocated
FlightMapClass::~FlightMapClass() { delete[] map; }
// Read_cities FlightMapClass member function
// Pre-Condition: The member function of the FlightMapClass takes in the
// ifstream file_object and reads in the cities to create the vector of citites
// array. Pcoutt-Condition: Creates the STL vector of cities read in from the
// file
void FlightMapClass::ReadCities(ifstream &file_object) {
  // declaring string variables of city_num and city_names to be used in reading
  // from the file
  string city_num;
  string city_names;

  // Reading in the first line from the file (cities.dat) which includes the
  // string amount of the number of cities
  getline(file_object, city_num);

  // conversion of the string of number of cities to an integer
  size = stoi(city_num);

  // using the STL vector member function reserve to reserve the number of
  // spaces for each city that we read in
  cities.reserve(size);
	visited.reserve(size);
  // Reading from the file to get the different names of the cities and to push
  // back to the vector of cities once we have read one city
  while (getline(file_object, city_names)) {
    cities.push_back(city_names);
		visited.push_back(false);
  }

  // Using the sort member function to sort the names of the cities in
  // Alphabetical order starting with the beginning of the vector to the end of
  // the vector of cities.
  sort(cities.begin(), cities.end());
  // Testing purpcoute
  /*vector<string>::iterator it;
  for(it=cities.begin();it!=cities.end();it++){
          cout<<*it<<endl;
  }*/
}
// Read_and_build_map FlightMapClass member function that takes in a file object
// Pre-condition: This function reads in from the (flight.dat) data file
// Pcoutt-condition: The Flight Map (adjaceny list) is created
void FlightMapClass::BuildMap(ifstream &file_object) {
  // Allocation of the list of flightRec for the number of cities
  map = new list<flightRec>[size];

  // Declaring temporary variables to hold the information that is read from the
  // file
  int flight_number, price;
  string origin, destination;

  // Declaration of a struct of One_flight
  flightRec One_flight;

  // Reading from the file and storing the information into the approiate
  // variables
  while (file_object >> flight_number >> origin >> destination >> price) {

    // Then storing the information into the One_flight struct
    One_flight.flightNum = flight_number;
    One_flight.origin = origin;
    One_flight.destination = destination;
    One_flight.price = price;

    // Using the for loop to iterate through the vector of cities until we find
    // one that correlates with the same orgin as the One_flight struct
    for (int index = 0; index < size; index++) {

      // Once we find one that matched, we can then push back the information
      // for that flight into the list of flight map creating the adjacency list
      // of Flight Map
      if (cities[index] == One_flight.origin) {
        map[index].push_back(One_flight);
      }
			map[index].sort();
    }
    // Using the ignore method to ignore characters
    file_object.ignore(100, '\n');
		
  }
  return;
}
void FlightMapClass::DisplayMap() {
  // Printing of the header for the Flight information that has the sub-titles
  // for each category for the flight information
  cout << left << setw(24) << "       Origin " << setw(15) << "Destination"
       << setw(9) << "Flight"
       << "Price" << endl;
  cout << "======================================================" << endl;
  cout << endl;

  // For loop to iterate through the number of cities
  for (int index = 0; index < size; index++) {

    // Declaration of the itr iterator so that we can iterate through the list
    // of flightRec
    list<flightRec>::iterator itr;

    // Sorting the information in Alphabetical order
    //map[index].sort();

    // Printing of the From and To using the set width function and the vector
    // of cities that contain the origins of all the flights
    cout << " From " << cities[index]
         << setw(18 - cities[index].length()) << " to: ";

    // Integer counter varaible used to keep track if we need to have a new_line
    // or not
    int counter = 0;

    // For loop to iterate through the entire map
    for (itr = map[index].begin(); itr != map[index].end();
         itr++) {

      // If the iterator does not equal to being (meaning its not the first one
      // in the map) we can setw accordingly
      if (itr != map[index].begin()) {
        cout << setw(24) << left << "";
        cout << setw(15) << itr->destination;
        cout << setw(9) << itr->flightNum;
        cout << "$" << itr->price << endl;
      }
      // else then this is the first row of information in the list then we can
      // spaceout and setw accordingly
      else {
        cout << setw(15) << itr->destination;
        cout << setw(9) << itr->flightNum;
        cout << "$" << itr->price << endl;
        // Increment counter since it is not the first one in the row
        counter++;
      }
    }
    // If the counter is equal to zero meaing that there was nothing in the
    // first row (so no information) then we can insert a new line
    if (counter == 0) {
      cout << endl;
    }
  }
  
}


//This function is going through and seeing if the cityName is valid
bool FlightMapClass::CheckCity(string cityName) const {
	
	//Declaring a city_iterator to look at the beginning of the cities vector array 
	vector<string>::const_iterator city_iterator = cities.begin();
	
	//For loop to iterate through the vector of citites and when it comes up with one that matches the same as the cityName we return true and break out of the loop 
	for(city_iterator = cities.begin(); city_iterator != cities.end(); city_iterator++){
		if(*city_iterator == cityName){
			return true;
		}
	}
		//If any didn't match then we return false
		return false;
}

// Displays all of the cities function:
void FlightMapClass::DisplayAllCities() const{
	//iterator declared to iterate through the vector of cities 
	vector<string>::const_iterator it;

	//For loop to iterate through the entire vector of citites to the console
	for(it=cities.begin();it!=cities.end();it++){
		cout<<*it<<endl;
	}
}

// Marks a city as visited
// Pre-condition: city to be marked as visited is provided
// Post-condition: a city is marked as visited
void FlightMapClass::MarkVisited(int city){
	
	//Given here an int (index I assume) instead of a city name
	//We need to go to the vector of booleans and at that index mark it as True
	//True means visited in this case
	visited[city] = true;
}

//This function is going through and assiging false to the vector of boolean values
//reseting the boolean visted array to false
void FlightMapClass::UnvisitAll(){
	
	//Declaring an iterator of vector bool type
	vector<bool>::iterator iterator;
	
	//for loop to iterate throught the vector of boolean values to set them all to false
	//resetting the boolean vector 
	for(iterator = visited.begin();iterator!=visited.end();iterator++){
		*iterator = false;
	}
}

// Determines whether a city was visited
// Pre-condition: city is provided
// Post-condition: return true if city has been visited
bool FlightMapClass::IsVisited(int city) const {
	//Since we go throught the vector of cities array and get the index
	//Here we can just see if the vector of cities at that index has been visited (if visited it will have true) and return back true
	return visited[city] ; 
}

//This function 
bool FlightMapClass::GetNextCity(string fromCity, string &nextCity){
	//fromcity name figure out the corresponding index 
	int index_postion = GetCityNumber(fromCity);
	
	//Then we need to iterate through the flightmap (adjaceny list) and the boolean vector of visited to see if it has been visited or not

	//creating an alias of map[index_postion] for direct access
	list<flightRec>& lists_for_destination = map[index_postion];
	
	//declaring an iterator of list flightrec type to look at the beggining of the list_of_destination 
	list<flightRec>::iterator iter = lists_for_destination.begin();

	//For loop to itertate through the list_for_destination 
	for(;iter!=lists_for_destination.end();iter++){
		
		//checking to see if the visited array GetCityNumberfunction is true 
		if(!visited[GetCityNumber(iter->destination)]){

			//then we can hav the nextCity variable look at the next place 
			nextCity = iter->destination;

			//returning ture
			return true;
		}
	}
	//else then return false
	return false;
}

// returns the integer index corresponding to a city name
// Pre-condition: name of a city is provided
// Post-condition: returns the index number corresponding to a city name
int FlightMapClass::GetCityNumber(string cityName) const{
	//Declaring an index variable to hold the index of the city name in the citites vector
	int index = 0;
	
	//for loop to iterate through the cities vector
	for(;index<size;index++){
		
		//If the cityname at the cities[index] is equaL to the cityname,
		//then return the index 
		if(cities[index]==cityName){
			return index;
		}
	}
	//return a -1 if there was not any cityName that matched with the cities[index]
	return -1;
}


// returns the name of a city given its corresponding index
// Pre-condition: number of a city is provided
// Post-condition: returns the city's name
string FlightMapClass::GetCityName(int cityNumber) const{
	
	//returning the string of the citiies vector at the particular index 
	return cities[cityNumber];
} 



// Determines whether a sequence of flights between two cities exists.
// Pre-condition: originCity and destinationCity are the origin and destination city. 
// Post-condition: prints out the path from origin to destination if one exists. 
void FlightMapClass::FindPath(string originCity, string destinationCity){
	
	//Printing request to fly from originCity to destinationCity to the user 
	cout<<"Request is to fly from "<<originCity<<" to "<<destinationCity<<"."<<endl;

	//Declaring a stack of integer type 
	stack<int> flightstack;

	//Declaring variables below to initialize and hold walues 
	int total_accumulator = 0;
	int first_city_index, destination_index, next_city_index;
	int top_index;
	string next_city;
	string real_city = originCity;

	//boolean success variable to hold either true or false
	bool success;
	
	UnvisitAll();//UnvisitAll function to go through the vector of bools and set back to false 
	
	//This if statement check to see if the origin city is not in the vector of cities
	//If it returns false then it does not serve it
	if(!CheckCity(originCity)){
		cout<<"Sorry, BlueSky airline does not fly from "<<originCity<<" to "<<destinationCity<<"."<<endl;
		return;
	}
		
  //Checking to see if the destination is a place that is served by the airline
	else if(!CheckCity(destinationCity)){
		cout<<"Sorry, BlueSky airline does not serve "<<destinationCity<<"."<<endl;
		return;
	}
	
	//Finding the index values of both the Origincity and destinationCity 
	//Set destination_index to the result of the GetCityNumber function
	destination_index = GetCityNumber(destinationCity);

	//Set first_city_index to the result of the GetCityNumber function 
	first_city_index = GetCityNumber(originCity);

	//Pushing back to the stack the index of the origin city
	flightstack.push(first_city_index);
	//Then calling the MarkVisited and passing in the first_city_index so that it can be marked in the vector of bools 
	MarkVisited(first_city_index);

	//While loop below to implement the depth first search of the indexes
	//Continue while the stack isn't empty and the top of the stack doesn't equal the destination index
	while(!flightstack.empty() && (flightstack.top()!=destination_index)){

		//Setting success to the result of GetNextCity function to see if there is a pathway
		success = GetNextCity(GetCityName(first_city_index),next_city);

		//If there is not anything next then pop the value from the stack so that it is not in the final stack
		if(!success){
			flightstack.pop();
			
		}
		//else then continue
		else{
			//Setting the next index to the index that is returned from the function of GetCityNumber
			next_city_index = GetCityNumber(next_city);

			//push that index onto the stack of indexes
			flightstack.push(next_city_index);

			//Once we pushed the index to the stack we can then mark it as visited
			MarkVisited(next_city_index);
			
			//Updating the originCity with the next_city 
			originCity = next_city;
		}
		//If the flightstack is empty then have the first_city_index look at the top of the stack
		if(!flightstack.empty()){
		first_city_index = flightstack.top();
		}

		//If the flightstack is empty meaning that the places were valid but no connecting flights then print out message 
		if(flightstack.empty()){
		cout<<"Sorry, BlueSky airline does not fly from "<<real_city<<" to "<<destinationCity<<"."<<endl;
		cout<<endl;
		return;
		}
	}
	//Printing out the message that the two cities are served by the airline
	//and the Flight itinerary 
	cout<<"Bluesky airline serves between these two cites."<<endl;
	cout<<"The Flight itinerary is:"<<endl;
	cout<<"Flight#         From            To               Cost"<<endl;

	//Declaring an deque of string to hold the string of names of the citites 
	deque<string> copy_flightstack;

	//While loop to iterate until the flightstack is empty 
	while(!flightstack.empty()){
		
		//Setting the top_index to the flight stack's top
		top_index = flightstack.top();

		//Popping it off if the stack
		flightstack.pop();

		//Then have the deque of strings to collect the names of the cites by using the GetCityName function with the number from the orginal flightstack
		copy_flightstack.push_front(GetCityName(top_index));
	}
	//Once we are done with collecting the names then iterate through entire deque of strings (copy_flightstack)
	for(int index = 0;index<copy_flightstack.size()-1;++index)
	{
		//set the string origin variable to index of the copy_flightstack of strings
		string origin = copy_flightstack[index] ;

		//setting the destinations of the copy_flightstack with index+1
		string destination = copy_flightstack[index+1];

		//Declaring an iterator to look at the start of the map of list FlightRec
		list<flightRec>::iterator iterator = map[GetCityNumber(origin)].begin();

		//For loop to iterate through the map of flightrec type so that we can printin out the information corresponding to the flight
		for(;iterator!=map[GetCityNumber(origin)].end(); ++iterator)
		{
			//Checking to see if the destination is equal to the destination that we are trying to look for 
			if(iterator->destination == destination)
			{
				//If the destination is the same the we can print out all oof the information coressponding to that flight 
				cout<<left<<setw(16)<<iterator->flightNum<<setw(16)<<left<<iterator->origin<<setw(17)<<iterator->destination<<"$"<< iterator->price<<endl;
				//Have the total_accumulator take in the total amounts 
				total_accumulator += iterator->price;
			}
		}
	}
	//Printing out the total at the end 
	cout<<right<<setw(50)<<"Total:    $"<<total_accumulator<<endl;
	cout<<endl;
}
