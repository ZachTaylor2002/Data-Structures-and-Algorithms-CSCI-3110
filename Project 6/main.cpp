/*
 PROGRAMMER: Zach Taylor
 Program Description: This program to creates a concordance for a text file using advanced topics such as binary search trees and recursion.
*/
#include "bst.h"
#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
set<string> visited_words;
void InsertNewEntry(BinarySearchTree &, string&, int);
void UpdatedEntry(BinarySearchTree &, string&, int);
void PrintWords(treeItemType&);
int main() {
  string one_line;
  BinarySearchTree oneTree;
  ifstream file_object;
  string file_name;
  int count = 0;
  cout << "This program will read a file and create a list of word frequency "
          "and line numbers."
       << endl;
  cout << endl;
  cout << "Please enter the name of the file to read: ";
  cin >> file_name;
  file_object.open(file_name);
  if (!file_object) {
    cout << file_name << " is an invalid file name." << endl;
  }
  while (getline(file_object, one_line)){
    count++;
    string file_word;
    stringstream s(one_line);
		treeItemType item;
		bool success;
    while (s >> file_word) {
			
			file_word.erase(remove_if(file_word.begin(), file_word.end(),[](char c){return !isalpha(c);}),file_word.end());
			transform(file_word.begin(), file_word.end(), file_word.begin(), ::tolower);
			
      if(!file_word.empty()){
				oneTree.SearchTreeRetrieve(file_word,item,success);
				if(success){
					UpdatedEntry(oneTree,file_word,count);
				}
				else{
					InsertNewEntry(oneTree,file_word,count);
				}
			}
    }
  }
	cout<<"-------------------- -------------------- --------------------------------"<<endl;
	cout<<"     Word                 Frequency                 Occurs on Lines        "<<endl;
	cout<<"-------------------- -------------------- --------------------------------"<<endl;
  oneTree.InorderTraverse(PrintWords);
  file_object.close();
	cout<<endl;
  cout << "Thank you for using our program." << endl;
  return 0;
}

void InsertNewEntry(BinarySearchTree &oneTree, string & word, int line) {
	treeItemType newWord;
	newWord.word = word;
	newWord.frequncy = 1;
	newWord.Numbered_line.push_back(line);
	newWord.last_line_number = line;
	bool success;
	oneTree.SearchTreeInsert(newWord,success);
}

void UpdatedEntry(BinarySearchTree & tree, string& word, int line){
	bool test_condition_flag;
	keyType serachtype = word;
	treeItemType previousNode;
	tree.SearchTreeRetrieve(serachtype,previousNode,test_condition_flag);
	if(test_condition_flag){
		previousNode.frequncy++;
		previousNode.Numbered_line.push_back(line);
		previousNode.last_line_number = line;
		tree.SearchTreeDelete(serachtype,test_condition_flag);
		tree.SearchTreeInsert(previousNode,test_condition_flag);
	}
}
void PrintWords(treeItemType& information){
	if(visited_words.find(information.word) == visited_words.end()){
		cout<<setw(28)<<left<<information.word<<setw(26)<<left<<information.frequncy;
		set<int> print_line_nums;
		for(auto i = information.Numbered_line.begin(); i != information.Numbered_line.end();i++){
			int line = *i;
			if(print_line_nums.find(line)==print_line_nums.end() ){
				cout<<line;
				if(next(i) != information.Numbered_line.end()){
					cout<<", ";
				}
				print_line_nums.insert(line);
			}
		}
		cout<<endl;
		visited_words.insert(information.word);
	}
}
