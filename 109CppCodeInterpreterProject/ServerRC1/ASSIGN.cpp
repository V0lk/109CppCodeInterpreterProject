//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Implementation file for ASSIGN
// Store the second parameter into the first parameter

#include "ASSIGN.h"

// constructors and destructors
// default constructor
ASSIGN::ASSIGN():ASSIGN("undefined","undefined", NULL){}

// parameterized constructor
ASSIGN::ASSIGN(string v1, string v2, TCPSocket* p_tcpSock){
	variable1 = v1;
	variable2 = v2;
	tcpSock = p_tcpSock;
}

// destructor
ASSIGN::~ASSIGN(){}

//Public Functions

// clone()
// clones the object and initializes it 
Expression* ASSIGN::clone(stringstream& ss, TCPSocket* p_tcpSock){
	ASSIGN* assigner = new ASSIGN();
	assigner->initialize(ss, p_tcpSock);
	return assigner;
}

void ASSIGN::execute(Storage* s, Parse* p){
	if(s->findVariable(variable1) == false){
		Logger::printToError("ERROR ASSIGN: parameter 1 was not found", tcpSock);
		return;
	}
	// if the check failed and it still went through
	if(variable1 == "undefined" || variable2 == "undefined"){
		return; // output messages should have been covered by initialize
	}
	//checks if the 2nd entry is a variable
	if (variable2.front() == '$'){ 
		// check if variable exists the variable it is
		if(s->findVariable(variable2) == false){
			Logger::printToError("ERROR ASSIGN: parameter 2 was not found", tcpSock);
			return;
		}
		// if they are both strings
		if(s->getVariableType(variable1) == "STRING" && s->getVariableType(variable2) == "STRING"){
			if(s->getStringLength(variable2) > s->getStringLength(variable1)){ // if string 2 is bigger than string 1
				Logger::printToError("ERROR ASSIGN: variable2 length is bigger than variable1 size",tcpSock);
				return;
			}
		s->setStringData(variable1, s->getStringData(variable2));
		}
		// if they are both real
		else if(s->getVariableType(variable1) == "REAL" && s->getVariableType(variable2) == "REAL"){
			s->setRealData(variable1, s->getRealData(variable2));
		}
		// if they are both numeric
		else if(s->getVariableType(variable1) == "NUMERIC" && s->getVariableType(variable2) == "NUMERIC"){
			s->setNumericData(variable1, s->getNumericData(variable2));
		}	
		// if they are both char
		else if(s->getVariableType(variable1) == "CHAR" && s->getVariableType(variable2) == "CHAR"){
			s->setCharData(variable1, s->getCharData(variable2));
		}
		else{
			Logger::printToError("ERROR ASSIGN: mismatching types provided", tcpSock);
		}
		return;
	}
				
	// if is a constant
	// string needs " ",so check for that
	if(s->getVariableType(variable1) == "STRING" && variable2.front() == '"'){
		variable2.erase(0,1); // erase front "
		variable2.erase(variable2.size() - 1); // erase back "
		s->setStringData(variable1, variable2);
	}
	else if(s->getVariableType(variable1) == "NUMERIC"){
		// checking for type
		char * p; //
		strtoll(variable2.c_str(),&p,10); // stores first non long character into p
		if(*p == false){ // if p never got a non long character
			s->setNumericData(variable1, stoll(variable2));
		}
		else{
		Logger::printToError("ERROR ASSIGN: parameter 2 was not of NUMERIC type",tcpSock);
			return;
		}
			
	}
	else if(s->getVariableType(variable1) == "REAL"){
		// checking for type
		char * p; //
		strtod(variable2.c_str(),&p); // stores first non double character into p
		if(*p == false){ // if no non integers detected, continue
			s->setRealData(variable1, stod(variable2));
		}
		else{
		Logger::printToError("ERROR ASSIGN: parameter 2 was not of REAL type\n", tcpSock);
			return;
		}
	}
	// char needs ' ', so check for that
	else if(s->getVariableType(variable1) == "CHAR" && variable2.front() == '\''){
		variable2.erase(0,1); // erase front '
		variable2.erase(variable2.size() - 1); // erase back '
		if(variable2.size() == 1){ // only 1 byte in string
			s->setCharData(variable1,variable2[0]); // only option is a char
		}
		else if (variable2.size() == 2){ //if the string is 2 bytes
			if(variable2 == "\n"){
				s->setCharData(variable1,'\n');
			}
			else if(variable2 == "\r"){
				s->setCharData(variable1,'\r');
			}
			else if(variable2 == "\t"){
				s->setCharData(variable1,'\t');
			}
			else{
				Logger::printToError("ERROR ASSIGN: parameter 2 was not a valid CHAR", tcpSock);
				return;
			}
		}
		else{
			Logger::printToError("From ASSIGN: " + variable2 + "is not a valid char",tcpSock);
			return;
		}
	}
	else{
		Logger::printToError("From ASSIGN: no matching type found",tcpSock);
	}
}

// initialize()
// initializes cloned object from stringstream
void ASSIGN::initialize(stringstream & ss,TCPSocket* p_tcpSock){
	tcpSock = p_tcpSock;
	string str = "";
	getline(ss,str,','); // isolate first variable
	if(str.empty()){ // if nothing returned
		Logger::printToError("ERROR ASSIGN: expected 2 parameters (has 0)",tcpSock);
		return;
	}
	variable1 = str;
	getline(ss,str); // get rest, variable 2
	if(str.front() != '"' && str.front() != '\''){ // if the input is not a string or char, because ',' is valid
		int n = count(str.begin(),str.end(),','); // count commas
			if(n == 0){ // first comma was already parsed, so any additional means over 2 parameters
			variable2 = str;
			return;
		}
		else{
		Logger::printToError("ERROR ASSIGN: expected 2 parameters (has more than 2)\n", tcpSock);
		}
	}
	else{ // either a " or '
		if(str.front() == '"' && str.back() != '"'){ // unclosed string
			Logger::printToError("ERROR ASSIGN: STRING is missing terminator",tcpSock);
			return;
		}
		if(str.front() == '\'' && str.back() != '\''){ // unclosed char
			Logger::printToError("ERROR ASSIGN: CHAR is missing terminator",tcpSock);
			return;
		}
		if(str.size() == 1){ // case where the only character is a terminator
			Logger::printToError("ERROR ASSIGN: missing terminator",tcpSock);
		}
	variable2 = str;
	}
		
}
