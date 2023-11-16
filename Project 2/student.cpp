#include "student.h"
#include <iostream>
#include <string>
#include <iomanip>
// Regular Constructor located here
//Setting default values into the constructor
Student::Student() {
	id = "No id entered ";
	name = "No name entered";
	//Setting default values for each grade 
	for (int index = 0; index < CATEGORY_NUM; index++) {
    score[index] = 0;
  }
	total = 0;
	letterGrade = 'x';
}
// The copy constructor located here
Student::Student(const Student &s) {
  id = s.id;
  name = s.name;
	//Setting the values of the grade from copy constructor here
  for (int index = 0; index < CATEGORY_NUM; index++) {
    score[index] = s.score[index];
  }
  total = s.total;
  letterGrade = s.letterGrade;
}
// Overloaded assignment operator function
//assignment operator that will assign 
Student & Student::operator=(const Student &rhs) {
  id = rhs.id;
  name = rhs.name;
  for (int index = 0; index < CATEGORY_NUM; index++) {
    score[index] = rhs.score[index];
  }
  total = rhs.total;
  letterGrade = rhs.letterGrade;
  return (*this);
}

// The Student ID Setters and Getters functions here
string Student::getID() const { return id; }
void Student::setID(string student_id) { id = student_id; }

// The total Setters and Getters function here
void Student::ComputeTotal() {
	total = 0;
  for (int index = 0; index < CATEGORY_NUM; index++) {
    total += score[index];
	}
}

int Student::GetTotal() const {  
	return total; 
}

// The grade Setter and Getter function here
//In this function we are determing the character grade to be assigned based on the total points
void Student::ComputeGrade() {
  if (total >= 90 ) {
    letterGrade = 'A';
  	} 
	else if (total < 90 && total >= 80) {
    letterGrade  = 'B';
  	} 
	else if (total < 80 && total >= 70) {
    letterGrade = 'C';
  	} 
	else if (total < 70 && total >= 60) {
    letterGrade = 'D';
  } 
	else {
    letterGrade = 'F';
  }
}
char Student::GetGrade() const { 
	return letterGrade; 
}

// The name Setters and Getters functions here
string Student::get_Name() const { 
	return name; 
}
void Student::set_Name(string student_name) { 
	name = student_name; 
}

//Changing the score of the student based on the certain asignment.
void Student::changeScore(ScoreType scoreName, int scoreValue){
	int grade;
		for(int index = 0;index<CATEGORY_NUM;index++){
		if(score[scoreName] == score[index]){
			grade = score[index];
			break;
		}
	   grade = scoreValue;
	}
}

//getScore member function that will iterate through the score raary and  
int Student::getScore(ScoreType scoreName) const{
	 int grade;
  for(int index = 0;index<CATEGORY_NUM;index++){
		if(score[scoreName] == score[index]){
			grade = score[index];
			break;
		}
	}

	return grade;
}

//Display function  that will display information for one particular student
//This function works by calling member functions of the student class to get the information needed 
void Student::DisplayInfo() const{
	cout<<"----------------------"<<endl;
	cout<<"Name : "<<get_Name()<<endl;
	cout<<"CLA :  "<<score[CLA]<<endl;
	cout<<"OLA :  "<<score[OLA]<<endl;
	cout<<"Quiz : "<<score[QUIZ]<<endl;
	cout<<"Homework : "<<score[HOMEWORK]<<endl;
	cout<<"Exam : "<<score[EXAM]<<endl;
	cout<<"Bonus : "<<score[BONUS]<<endl;
	cout<<"-----------------------"<<endl;
	cout<<"Total Score : "<<GetTotal()<<endl;
	cout<<"Final Grade : "<<GetGrade()<<endl;
}

//Implementaion of the overloaded operator >>
//This function will tell the terminal how to treat an insertion of >> to a student class
//Such as how to implement it and what exatcly to do 
istream & operator>>(istream &myin, Student &s) {
	  myin >>s.id >> s.name;
    for (int index = 0; index < Student::CATEGORY_NUM; index++) {
      myin >> s.score[index];
    }
		s.ComputeTotal();
	  s.ComputeGrade();
  return myin;
}
//Implementaion of the overloaded operator <<
//This function will tell the terminal how to treat an insertion of >> to a student class
//Such as how to implement it and what exatcly to do 
ostream & operator<< (ostream & myout, const Student &s) {
	//Printing out the information 
  myout<<" "<<setw(9)<<s.getID()<<setw(15)<<s.get_Name()<<right;
  for (int index = 0; index < Student::CATEGORY_NUM; index++) {
		myout<<setw(10)<<s.score[index];
  }
  myout << endl;
  return myout;
}
