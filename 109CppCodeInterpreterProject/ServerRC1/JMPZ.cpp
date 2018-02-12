//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Implementation file for JMPZ
// Jumps to specified label if parameter2 is zero

#include "JMPZ.h"
using namespace std;

//Constructors and Destructors
// default constructor
JMPZ::JMPZ():JMPZ("", "",NULL){}

// parameterized constructor
JMPZ::JMPZ(string l, string v,TCPSocket* p_tcpSock){
	label = l;
	variable = v;
	tcpSock = p_tcpSock;
}

// destructor
JMPZ::~JMPZ(){}

// Public Functions

// clone()
// clones the object
Expression* JMPZ::clone(stringstream & ss,TCPSocket* p_tcpSock){
	JMPZ* jmpzer = new JMPZ();
	jmpzer->initialize(ss,p_tcpSock);
	return jmpzer;
}

// initialize()
// initializes cloned object
void JMPZ::initialize(stringstream & ss,TCPSocket* p_tcpSock){
	// update the destination information
	tcpSock = p_tcpSock;

	string str = "";
	getline(ss,str,','); // get the label name
	label = str;
	getline(ss,str); // get the variable
	
	int n = count(str.begin(),str.end(),','); // count commas
	int p = count(str.begin(),str.end(),','); // count periods , meaning floats
	if(n == 0 && p == 0){ // first comma was already parsed, so any additional means over 2 parameters
		variable = str;
	}
	else{
		Logger::printToError("From JMPZ: expected 2 parameters (has more than 2)",tcpSock);
	}
}

// execute()
// JMPZ's logic execution
void JMPZ::execute(Storage* s, Parse* p){
	//checking parameters
	if (s->findLabel(label) == false){
		Logger::printToError("From JMPZ: " + label + " not found",tcpSock);
		return;
	}
	if(variable[0] == '$'){
		if (s->findVariable(variable) == false){
			Logger::printToError("From JMPZ: " + variable + " not found",tcpSock);
			return;
		}

		if(s->getVariableType(variable) == "NUMERIC"){
			if (s->getNumericData(variable) == 0){ // if it is equal to 0 try to jump
				p->setIndex(s->getIndexOf(label)); // if label is found, jump
				return;
			}
		} 
		else{
			Logger::printToError("From JMPZ: " + variable + " is not of numeric type",tcpSock);
			return;
		}
	
	}
	
	else{
		long long a;
		char* c;
		a = strtoll(variable.c_str(), &c, 10);
		if(*c){
			Logger::printToError("From JMPZ: " + variable + " is not a valid numeric",tcpSock);
			return;
		}
		if(a == 0){
			p->setIndex(s->getIndexOf(label)); // if label is found, jump
			return;
		}
	}
}
