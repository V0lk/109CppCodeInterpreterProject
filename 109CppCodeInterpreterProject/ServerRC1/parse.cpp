//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Implementation file for Parse
// Takes an input file and stores it into a vector for easy referencing

#include "parse.h"

//Constructor
//Creates the Obj's vector and populates it from file
Parse::Parse(string infile){
	string line="";	//string to read lines
	stringstream ss(infile);
	int i =0;
	while(getline(ss,line)){
		
		// cleaning up tokens
		line.erase(remove(line.begin(),line.end(), '\t'),line.end()); // removing tabs
		line.erase(remove(line.begin(),line.end(), '\n'),line.end()); // removing new line token
		line.erase(remove(line.begin(),line.end(), '\r'),line.end()); // removing new line token
		
    	this->code.push_back(line);		//Get current line, push it on vector
    	line="";
    	i++;
	}
	
	index = 0;			//if index is -1, we are at the beginning
	size = code.size() - 1; // size = vector size -1, 
	// if vector size = 7, vector only goes from 0-6, so vector[7] gives seg.fault
}


// Public Functions

//getSize()
// returns the size of the vector
int Parse::getSize(){
	return size;
}

//hasNextLine()
// checks if there is a next line in the vector
bool Parse::hasNextLine(){
	if(index > size){
		return false;
	}
	else{
		return true;
	}
}

//setIndex(int)
// moves the index to variable
void Parse::setIndex(int curr){
	if(curr > size){
		cout << "invalid index" << endl;
		return;
	}
	else{
		index = curr;
		return;
	}
}

//getIndex()
// returns the current index
int Parse::getIndex(){
	return index;
}

//nextLine()
// moves the index up one for the next line
void Parse::nextLine(){
	index++;
}

//getLine()
// returns the line from index
string Parse::getLine(){
	return code[index];
}

//printCode()
// prints the entire code
void Parse::printCode(){
	for(vector<string>::iterator i = code.begin(); i!= code.end(); i++){
		cout << *i << endl;
	}
}
