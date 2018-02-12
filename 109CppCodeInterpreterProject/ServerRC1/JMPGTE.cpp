//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Implementation file for JMPGTE
// Jumps to specified label if parameter2 is greater than or equal to parameter3

#include "JMPGTE.h"
using namespace std;

//Constructors and Destructors
// default constructor
JMPGTE::JMPGTE():JMPGTE("", "", "", NULL){}

// parameterized constructor
JMPGTE::JMPGTE(string l, string v1, string v2, TCPSocket* p_tcpSock){
	label = l;
	var1 = v1;
	var2 = v2;
	tcpSock = p_tcpSock;
}

// destructor
JMPGTE::~JMPGTE(){}

// Public Functions

// clone()
// clones the object
Expression* JMPGTE::clone(stringstream & ss, TCPSocket* p_tcpSock){
	JMPGTE* jmpgteer = new JMPGTE();
	jmpgteer->initialize(ss,p_tcpSock);
	return jmpgteer;
}

// initialize()
// initializes cloned object
void JMPGTE::initialize(stringstream & ss, TCPSocket* p_tcpSock){
	tcpSock = p_tcpSock;
	string str = "";
	getline(ss,str,','); // get the label name
	if(str.empty()){ // if nothing returned
		Logger::printToError("From JMPGTE: expected 3 parameters (has 0)",tcpSock);
		return;
	}
	label = str;
	
	if(ss.peek() == -1){ // if nothing returned
		Logger::printToError("From JMPGTE: expected 3 parameters (has 1)",tcpSock);
		return;
	}
	getline(ss,str,','); // get the variable
	var1 = str;
	
	if(ss.peek() == -1){ // if nothing returned
		Logger::printToError("From JMPGTE: expected 3 parameters (has 2)",tcpSock);
		return;
	}
	getline(ss,str,',');
	var2 = str;
	
	if(ss.peek() != -1){ // if something returned
		Logger::printToError("From JMPGTE: expected 3 parameters (has more)",tcpSock);
		var1 = "";
		var2 = "";
		label = "";
		return;
	}
}

// execute()
// JMPGTE's logic execution
void JMPGTE::execute(Storage* s, Parse* p){
	//checking parameters
	if (s->findLabel(label) == false){
		Logger::printToError("From JMPGTE: " + label + " not found",tcpSock);
		return;
	}
	double a = 0;
	double b = 0;
	
	if(var1[0] == '$'){
		if (s->findVariable(var1) == false){
			Logger::printToError("From JMPGTE: " + var1 + " not found",tcpSock);
			return;
		}
		if (s->getVariableType(var1) != "NUMERIC" && s->getVariableType(var1) != "REAL"){
			Logger::printToError("From JMPGTE: " + var1 + " is not of numeric type",tcpSock);
			return;
		}

		if(s->getVariableType(var1) == "NUMERIC") a = (double)s->getNumericData(var1);
		else if(s->getVariableType(var1) == "REAL") a = (double)s->getRealData(var1);
	}
	else{
		char* p;
		a = strtod(var1.c_str(), &p);
		if(*p){
			Logger::printToError("From JMPGTE: " + var1 + " is not a valid numeric",tcpSock);
			return;
		}
	}
	
	if(var2[0] == '$'){
		if (s->findVariable(var2) == false){
			Logger::printToError("From JMPGTE: " + var2 + " not found",tcpSock);
			return;
		}
		if (s->getVariableType(var2) != "NUMERIC" && s->getVariableType(var2) != "REAL"){
			Logger::printToError("From JMPGTE: " + var2 + " is not of numeric type",tcpSock);
			return;
		}
		
		if(s->getVariableType(var2) == "NUMERIC") b = (double)s->getNumericData(var2);
		else if(s->getVariableType(var2) == "REAL") b = (double)s->getRealData(var2);
	}
	else{
		char* c;
		b = strtod(var2.c_str(), &c);
		if(*c){
			Logger::printToError("From JMPGTE: " + var2 + " is not a valid numeric",tcpSock);
			return;
		}
	}
	if(a >= b) p->setIndex(s->getIndexOf(label));
}
