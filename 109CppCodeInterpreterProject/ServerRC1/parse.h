//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Header file for Parse
// Takes an input file and stores it into a vector for easy referencing

#ifndef _PARSE
#define _PARSE

#include "common.h"

using namespace std;
class Parse{
	private:
		vector<string> code;
		int index;		//current line
		int size;	// size of vector
	public:
		Parse(string);			//constructor
	
		int getSize();			//returns number of lines
		int getIndex();			//gets current line num
		void setIndex(int);		//changes the current index
		bool hasNextLine();		// peeks and sees if there is a next line
		string getLine();		// returns line at current index
		void nextLine();		// moves index up one
		void printCode();		//prints all code
		~Parse(){};				//destructor

};

#endif