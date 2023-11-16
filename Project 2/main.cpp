// Author: Zach Taylor
// CSCI 3110
// Project 2
// Project Description: This program uses two different classes one class called Student and the other class called Roster. The over purpose of this program is to read from a file of students and create a class object to display the table of students and to find more information on a particular student. 

#include "student.h"
#include "roster.h"
#include <fstream>
#include <iostream>   //Pre-Processor directives 
#include <string>
#include <iomanip>
using namespace std;
int main() {

	//Variable declarations 
	int amount;           
	bool testing_id_result;   //testing_id_result variable that will hold either True or False
	string user_entered_id;  //user_entered_id variable to hold the id that we are going to look for
	string classname;        //classname variable to hold the name of the class that will be read from the file
	Roster oneRoster(" ");  //Declaration of a class called oneRoster 

	//Here we are calling functions of the Roster class to read from the file and 
	oneRoster.readStudentRecord("grades.dat"); //calling of the readStudentRecords member function of the roster class to read from the file
	amount = oneRoster.GetStudentCount(); //calling of the GetStudentsCount member function of the Roster class to return the total amount of students read from the file and into the amount variable 
	classname = oneRoster.getcourseName(); //calling of the getcourseName member function of the Roster Class to return the string of the class name into the classname variable

	//Printing out the heading for out table that will display the the information for all the students from the file
	cout<<"Here is the information for the "<<amount<<" students in Class "<<classname<<endl;
	cout<<"   "<<setw(3)<<"ClassID"<<"       "<<setw(8)<<"Name"<<"  "<<setw(8)<<"CLA"<<"       "<<setw(1)<<"OLA"<<setw(4)<<"      "<<"Quiz"<<"  "<<setw(3)<<"Homework"<<setw(8)<<"Exam"<<setw(4)<<"    "<<"Bonus"<<endl;
	cout<<endl;

	//Using the overloaded opertor of << that we defined in the roster class that prints out the information of the students 
	cout<<oneRoster<<endl;
	cout<<endl;

	//Prompting the user to enter a class ID of one of the students so that information for that one student will appear
	cout<<"Enter a valid class ID:";
	cin>>user_entered_id;

	//Calling the class member function (isValid) of the Roster class and passing in a student id to see if information exists for the id that the user entered. Storing the result in the testing_id_result 
	testing_id_result = oneRoster.isValid(user_entered_id);

	//The input validation loop below will continue until the user has entered a real student ID number 
	while(testing_id_result==0){  //While the result of the ID is False continue prompting the user for a real ID
		cout<<endl;
		cout<<"Enter a valid class ID:";
		cin>>user_entered_id;
		testing_id_result = oneRoster.isValid(user_entered_id);
	}
	//Once the user entered a real id, Display the information for that student below
	cout<<"Information for the student with ID "<<user_entered_id<<endl;
	cout<<"Here is the information for student with ID : "<<user_entered_id<<endl;

	//Calling of the Roster class member function to display information for that student. Passing in the user_entered_id since we know that the ID it is a real student in the class. 
	oneRoster.ShowOneStudent(user_entered_id);
  return 0;
}
