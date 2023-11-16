//Zach Taylor
//CSCI 3110
//Project One
//This Program reads from the grades.dat data file and stores this information in an array of structures and then print out the array of structs then ask the user for a class ID. It then repeats until we have a valid class id and then prints all of the information for that student. After that it sorts and prints the students in Alphabetic order along with the appropriate information for the student. 
#include <iostream> 
#include <fstream>                //Preprocessor Directives
#include <iomanip>       
#include <string>
#include "type.h"
using namespace std;                        //using namespace std

int read_file(ifstream&,StudentType []);    //read file function prototype that accepts the file stream and array of structs 
void print_info(StudentType [],int);        //print info  function prototype that accepts an array of structs and integer variable
bool checking_class_id(StudentType [],int,string); //checking class id function prototype that accepts an array of structs, string variable and an integer variable
void find_print_student(StudentType [],string,int); //find print student function prototype that accepts the array of structs a string variable and an integer variable
void sort_classmates(StudentType [],int); //sort classmates function prototype that accepts the array of structs and an integer variable

int main() {

	
	bool test;                         //boolean variable "test" to be what the checking_class_id will return
	ifstream file_object;               //declaring the file_object so that we can use preform file operations
	string file_name = "grades.dat";       //Preparing to read from the file 
	const int MAX_SIZE = 30;               //Setting up the array of Structs 
	StudentType roster[MAX_SIZE];          //declaring the array of structs named roster which currently has a MAX_SIZE of 30
	int student_counter;                  //student counter to record the number of students in the file
	string class_number;                  //class number variable to read in the class number from the user
	file_object.open(file_name);          //Opening the file for reading 

	
	student_counter = read_file(file_object,roster);  //calling the read_file function and sending in the file_object stream and the array of structs (roster) to be filled with the student info and then returning 
	print_info(roster,student_counter);//calling the print info function so we can display 
	cout<<endl; //printing new line character
	cout<<"Enter a valid class ID:";      //Prompting the user to enter a class ID for the student
	getline(cin,class_number);                           
	test=checking_class_id(roster,student_counter,class_number);        //calling the checking class id function and returning a boolean reult 
	while(test==0){                    //Input validation loop that sees if we got a valid class id. if test is equal to zero (false) then we will keep asking the user until we finally get a correct class id
		cout<<endl;
		cout<<"Enter a valid class ID:";
		getline(cin,class_number);
		test=checking_class_id(roster,student_counter,class_number);
	}
	
	//Once we finally get a valid class ID we can then call the find_print_student function to print out the information for that indivdual student
	find_print_student(roster,class_number,student_counter);
	//Once we print out the information for the indivdual student we can now sort the students in ABC order
	cout<<"sorting student records by name...."<<endl;
	sort_classmates(roster,student_counter);  //calling the sort_classmates function and passing in the roster array and the amount of students. In this function I used a bubble sorting array to sort the names of the students 
	print_info(roster,student_counter);  //calling the print_info function to print out the final information of the students in ABC order
	file_object.close(); //closing the file
  return 0;  //return zero back to main once everything has been executed 
}


//Description: This function reads movies from the grades.dat file and stores them into the student_info array. 
//pre-condition: The file is ready to read from since we passed in the ifstream object and the array of student_info structs (which in main is known as the roster).
//post-condition: After this function is executed, the file would have been read from and the array of student structs will have been filled with the appropriate data and the function would have returned the actual amount of students in total.
int read_file(ifstream& file_object,StudentType student_info[]){
	int index=0;//setting an integer index variable to count the actual amount of students in the file
	//declaring a trash variable which is of type string that will read in the first line of data which is the categories
	string trash;
	getline(file_object,trash);
	//Using a while loop to read until we reach the end of file and storing each info into the approiate struct 
	while(file_object>>student_info[index].ID){
		file_object>>student_info[index].Name;
		file_object>>student_info[index].CLA;
		file_object>>student_info[index].OLA;
		file_object>>student_info[index].Quiz;
		file_object>>student_info[index].Homework;
		file_object>>student_info[index].Exam;
		file_object>>student_info[index].Bonus;
		index++;//incrementing the index variable everytime we have successfully read a student info into the struct 
	}
	return index;//returning back the amount of students in this file
}
//Description: This function takes in the array of student structs and the number of students total
//It prints out the category of the information such as the the assignements and prints out each of the student's information and points they got correlating to the category. 
void print_info(StudentType student_info[],int student_counter){
	cout<<"Here are the information of the "<<student_counter<<" students:"<<endl;
	cout<<endl;
	cout<<"ClassID "<<setw(6)<<" Name"<<setw(10)<<"       CLA "<<setw(6)<<" OLA "<<setw(6)<<"Quiz "<<setw(6)<<" Homework "<<setw(6)<<" Exam "<<setw(6)<<" Bonus "<<endl;
	cout<<endl;
	for(int index=0;index<student_counter;index++){ //For loop here to iterate through each information of the students info
		cout<<left<<setw(10)<<student_info[index].ID<<setw(12)<<student_info[index].Name<<setw(5)<<student_info[index].CLA<<setw(7)<<student_info[index].OLA<<setw(8)<<student_info[index].Quiz<<setw(7)<<student_info[index].Homework<<setw(8)<<student_info[index].Exam<<student_info[index].Bonus<<endl;
	}
}
//Description: In this function called checking_class_id we pass in the array of structs in main called roster, the class_number of the student we are trying to search for and the total number of students.
//Pre-condition: Takes in the the array of structs to determine if the class number is valid
//Post-condition: returns true or false if the class number is valid
bool checking_class_id(StudentType student_info[],int student_counter,string class_number){
	string id;
	//For loop to iterate through the entire array of structure to find if the class id enter matched one of them stored into the student_info.ID;
	for(int index=0;index<student_counter;index++){
		if(class_number == student_info[index].ID){ //If we do find one that matches we can first return true and break out of the for loop
			return true;
			break;
		}
	}
	return false; //If we didn't find one we will return false
}
//Description: this function takes in the array of roster struct, the class number, and counter and iterates through until it finds the student with the class number stores the info in the student_index_postion. Once it is found it prints out the information from the array of roster using the index that was found
//Pre-condition: Since we did a validation loop we WILL find a student with a correlation to a class number
//Post-condition: Prints out the information for that student
void find_print_student(StudentType student_info[],string class_number,int student_counter){
	int student_index_position;
	for(int count =0;count<student_counter;count++){
		if(class_number == student_info[count].ID){
			student_index_position = count;
			break;
		}
	}
	cout<<"Information for student with ID:"<<student_info[student_index_position].ID<<endl;
	cout<<"Name : "<<student_info[student_index_position].Name<<endl;
	cout<<"CLA : "<<student_info[student_index_position].CLA<<endl;
	cout<<"OLA : "<<student_info[student_index_position].OLA<<endl;
	cout<<"Quiz : "<<student_info[student_index_position].Quiz<<endl;
	cout<<"Homework : "<<student_info[student_index_position].Homework<<endl;
	cout<<"Exam : "<<student_info[student_index_position].Exam<<endl;
	cout<<"Bonus : "<<student_info[student_index_position].Bonus<<endl;
	cout<<endl;
	cout<<endl;
}
//Description: This function sorts out the array of structure using the bubble sorting 
//Pre-condition: takes in the array of structs with the names unsorted 
//Post-condition: sorts out the array of stucts with the names in ABC order and the correct info along with that student
void sort_classmates(StudentType student_info[],int student_counter){
	bool sorted = false; 
	int last = student_counter-1; //Sine arrays start a zero we must set the counter equal to it minus one so in this case zero to 16.
	StudentType holder; //declaring another Studenttype variable to hold information when sorting 
	while(!sorted){ //Using a while loop that will continue until we have everything sorted
		sorted = true;
	for(int index = 0; index<last ; index++){
		if(student_info[index].Name > student_info[index+1].Name){
			holder = student_info[index];                           //Iterating through the structs and sorting the names. 
			student_info[index] = student_info[index+1];
			student_info[index+1] = holder;
			sorted = false;
		}
	}
		last--;
	}
}
