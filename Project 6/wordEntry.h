#include <string>
#include <list>
using namespace std;

#ifndef WORD_H
#define WORD_H

struct wordEntry{
 
 string word;
 int frequncy;
 list<int> Numbered_line;
 int last_line_number;
 string Key() const; // returns the key value for a word entry 
};
#endif
