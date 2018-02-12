//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Implementation file for ExpressionFactory
// Inherits from Abstrct Factory
// Generates Expression objects

#include "expressionFactory.h"
#include "ADD.h"
#include "SUB.h"
#include "DIV.h"
#include "MULT.h"
#include "VAR.h"
#include "JMP.h"
#include "JMPZ.h"
#include "JMPNZ.h"
#include "JMPGT.h"
#include "JMPGTE.h"
#include "JMPLT.h"
#include "JMPLTE.h"
#include "SLEEP.h"
#include "OUT.h"
#include "ASSIGN.h"
#include "GET_STR_CHAR.h"
#include "SET_STR_CHAR.h"

// Constructors and Destructors
// default constructor
ExpressionFactory::ExpressionFactory(){ // initializes all possible expressions
	objs["ADD"] = new ADD;
	objs["SUB"] = new SUB;
	objs["DIV"] = new DIV;
	objs["MULT"] = new MULT;
	objs["VAR"] = new VAR;
	objs["JMP"] = new JMP;
	objs["JMPZ"] = new JMPZ;
	objs["JMPNZ"] = new JMPNZ;
	objs["JMPGT"] = new JMPGT;
	objs["JMPGTE"] = new JMPGTE;
	objs["JMPLT"] = new JMPLT;
	objs["JMPLTE"] = new JMPLTE;
	objs["SLEEP"] = new SLEEP;
	objs["OUT"] = new OUT;
	objs["ASSIGN"] = new ASSIGN;
	objs["GET_STR_CHAR"] = new GET_STR_CHAR;
	objs["SET_STR_CHAR"] = new SET_STR_CHAR;
}

// destructor
ExpressionFactory::~ExpressionFactory(){
	for(map<string,Expression*>::iterator itr = objs.begin(); itr != objs.end(); itr++){ // iterates through map
		delete itr->second; // frees the pointers
	}
}

// Public functions

//getObject(string)
// returns an object from the map matching the identifier from string s
Expression* ExpressionFactory::getObject(string s, TCPSocket* p_tcpSock){
	string name = ""; // variable for holding the name of the expression
	
	// getting the name of the object
	stringstream iss(s); // input the complete string into string stream
	getline(iss,name,' '); // puts instruction into name
	
	if ( name == "LABEL"){ // label is ignored
		return NULL;
	}
	if (name.empty()){ // empty space is ignored
		return NULL;
	}
	
	if(name == "THREAD_BEGIN"){
		
	}
	
	// checking map for object of name
	Expression* expr = objs[name];
	if ( expr != NULL) { // if object exists
		expr = expr->clone(iss,p_tcpSock); // creates a clone
		return expr; // returns a clone of the object
	}
	else{ // object not found
		p_tcpSock->writeToSocket("ERROR Expressions: invalid expression\n", strlen("ERROR Expressions: invalid expression\n"));
		return expr;
	}
}
