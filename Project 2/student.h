/*
 * File:	Student.h
 * 
 * Purpose: This file is a part of the 1st open lab assignment, which 
 * includes Student.h, Student.cpp, Roster.h, Roster.cpp, 
 * and main.cpp. This file gives the full definition 
 * of the class Student.
 */

#ifndef __CSCI3110_STUDENT__
#define __CSCI3110_STUDENT__

#include <string>
#include <iostream>
using namespace std;

class Student
{
	public:
		// The types of score. You can access the type or enumerators outside
		// of the Student class scope by the following expressions:
		//	Student::ScoreType              Student::CLA    
		enum ScoreType {CLA, OLA, QUIZ, HOMEWORK, EXAM, BONUS};

		// To access the class constant outside of the Student class scope:
		//	Student::CATEGORY_NUM
		static const int CATEGORY_NUM = BONUS - CLA + 1;

		// default constructor. This is necessary since we define an array 
		// of students in the class Roster
		Student( );                               //Complete

    // copy constructor
    Student(const Student & s);                //Complete

    // overloaded assignment operator
    Student& operator  = (const Student & rhs);  //complete

		//Accessor & mutator of id 
		string getID( ) const;
		void setID( string ) ;                             //complete

    // Accessor & mutator of total (score)
    void  ComputeTotal();                             //complete 
    int   GetTotal() const;

    // Accessor & mutator of letter grade
    void  ComputeGrade();                         //complete   
    char  GetGrade() const;                    

    //Accessor & mutator of letter grade
    string get_Name()const;
    void set_Name(string);                                  //complete
		//Accessor and mutator of m_score
		//ScoreType indicates which score you want to access
		void changeScore(ScoreType scoreName, int scoreValue);    //complete  
		int  getScore( ScoreType scoreName) const;    //Complete

    // This function displays information of one student, one value per row 
    // label for each value is included
    // total score and letter grade are also included
    void DisplayInfo() const;  //Complete 

    // friend function to output information (exclude total score and letter grade) of one student 
    // All information of one student is displayed on one row
    friend ostream & operator << (ostream & myout, const Student & s);    //Complete

    // friend function to data of one student from the data file
    friend istream & operator >> (istream & myin, Student & s);    //complete

		//********************************************************************
		//Add your functions here if necessary
    //like getters and setters for m_total and m_letterGrade
		//********************************************************************
     

	private:
		string		id;		// Student ID
    string    name; // Student name
		int				score[CATEGORY_NUM];
						// score[CLA] is CLA score		
						// score[OLA] is OLA score		
						// score[QUIZ] is QUIZ score		
						// score[HOMEWORK] is HOMEWORK score		
						// score[EXAM] is EXAM score		
            // score[BONUS] is Bonus score
    int     total;  //total score, which is the sum of all scores
    char    letterGrade;
};
#endif
