//Roster.cpp header file 
//This header file contains contents of the Roster class that is used in implementing this program

#include "roster.h"  //Implemetation of the roster header file

#include <iostream>   //Pre-processor directives 
#include <string>
#include <fstream>

//Value constructor for the Roster class below
//Takes in the course name and set it to the private data member 
Roster::Roster(string courseName){
	courseName = courseName;
}

//Roster class member function of readStudentRecord
//Pre-condition:This member function takes in a string of the text-file to read from
//Post-condition: After execution of this member function we will have read from the file sucessfully and have set the private data member of class to the class name.
void Roster::readStudentRecord(string filename){
	
	int index= 0;
	string trash;            //variable declarations for this memeber function
	ifstream file_object;

	
	file_object.open(filename);            //Opening the file for reading 
	if(!file_object){                      //Testing to see if the user entered a valid file name 
		cout<<"Invalid file name"<<endl;     //warning message if the didn't 
	}
	
	getline(file_object,courseName);    //reading the first line to get the course name 
	getline(file_object,trash);    //reading the titles of the grades and storing them into a trash variable
	while(!file_object.eof()){     //Using a While loop to read information from the file into the student array of objects
		file_object>>students[index];
		index++;
	}
	studentNum = index; //After reading from the file 

	
}
//Implementation of the Roster class member function of GetStudentCount that will return the number of students from the private data member section which the user CANNOT access
int Roster::GetStudentCount() const{ 
	  return studentNum;

} 

//Implementation of the Roster class memebr funtion of getcourseName that will return the courseName from the private data member section which the user CANNOT access
string Roster::getcourseName() const{  
	  return courseName;
} 

//Implementation of the Roster class member function that will check to see if a ID is valid or not
//Pre-condition: Passing in a user entered student id.
//Post Condition: Returning a boolean result that tells whether the student ID is one in the class
bool Roster::isValid(string id) const{ 
	bool result=false; 
	//For loop to iterate through the array of student objects and it will break if a student ID matched one that the user provided 
	for(int index=0;index<studentNum;index++){
		if(id == students[index].getID()){
			result = true; //set result equal to true
			break;    //break out of the for loop
		}
	}
	return result; //return the result
}

//Implementation of the Roster class member called ShowOneStudent that will display the information on the ID that the user provided.
//Pre-condition: This member class takes in a string of the ID for a particular student
//Post-condtion: Iterates through the array of objects and finds the index for that particlar student and prints out the information for that one student
void Roster::ShowOneStudent(string id) const{
	int student_index= 0;
	//For loop to iterate through and find the index that correlates to the student in the array of objects
	for(int position=0;position<studentNum;position++){
		if(id == students[position].getID()){
			student_index = position;
			break;//breaking out once we got that index
		}
	}
	//Printing all of the information for that student
	cout<<"---------------------"<<endl;
	cout<<"Name : "<<students[student_index].get_Name()<<endl;
	cout<<"CLA : "<<students[student_index].getScore(Student::CLA)<<endl;
	cout<<"OLA : "<<students[student_index].getScore(Student::OLA)<<endl;
	cout<<"Quiz : "<<students[student_index].getScore(Student::QUIZ)<<endl;
	cout<<"Homework : "<<students[student_index].getScore(Student::HOMEWORK)<<endl;
	cout<<"Exam : "<<students[student_index].getScore(Student::EXAM)<<endl;
	cout<<"Bonus : "<<students[student_index].getScore(Student::BONUS)<<endl;
	cout<<"-----------------------"<<endl;
	cout<<"Total Score : "<<students[student_index].GetTotal()<<endl;
	cout<<"Final Grade : "<<students[student_index].GetGrade()<<endl;
}

//Implementation of the overloaded operator << 
//Pre-Condtion: This overloaded operator takes in the ostream and the Roster class
//Post-Condition: Calls the array of students objects and prints out the table for all the students
ostream & operator<< (ostream& os, const Roster& oneClass){
	for(int count = 0;count<oneClass.studentNum;count++){
		os<<oneClass.students[count];
	}
	return os;
}
