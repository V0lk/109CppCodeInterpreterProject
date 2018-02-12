//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Implementation of DataFactory class
// Generates new DataType objects

#include "dataFactory.h"
#include "MISNumeric.h"
#include "MISReal.h"
#include "MISString.h"
#include "MISChar.h"

// Constructors and Destructors

// default constructor
DataFactory::DataFactory(){ // initializes all possible expressions
	objs["NUMERIC"] = new MISNumeric;
	objs["REAL"] = new MISReal;
	objs["CHAR"] = new MISChar;
	objs["STRING"] = new MISString;
}

// destructor
DataFactory::~DataFactory(){
	for(map<string,DataType*>::iterator itr = objs.begin(); itr != objs.end(); itr++){ // iterates through map
		delete itr->second; // frees the pointers
	} // delete will handle the rest
}

// Public functions

// getObject(string)
// returns an object from the map
DataType* DataFactory::getObject(string s,TCPSocket* p_tcpSock){
	string name = ""; // variable for holding the name of the expression
	
	// getting the name of the object
	stringstream iss(s); // input the complete string into string stream
	getline(iss,name,','); // puts instruction into name
	
	// checking map for object of name
	DataType* data = objs[name];
	if ( data != NULL) { // if object exists
		data = data->clone(iss,p_tcpSock); // creates a clone
		return data; // returns a clone of the object
	}
	else{ 
		return data;
	}
}
