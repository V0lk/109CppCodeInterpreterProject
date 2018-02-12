//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Implementation file for VAR
// Generates a variable in storage

#include "VAR.h"
using namespace std;

// Constructors and Destructors
// default constructor
VAR::VAR():VAR("undefined", "undefined",NULL){}

// parameterized constructor
VAR::VAR(string s,string d,TCPSocket* p_tcpSock){
	name = s;
	data = d;
	tcpSock = p_tcpSock;
}

// destructor
VAR::~VAR(){} 

// Public Functions
// clones object	
Expression* VAR::clone(stringstream & ss,TCPSocket* p_tcpSock){
	VAR* tester = new VAR();
	tester->initialize(ss,p_tcpSock);
	return tester;
}

// executes the  command
void VAR::execute(Storage* storage, Parse* p){
	if(name.front() != '$'){
		Logger::printToError("From VAR: provided variable name does not start with $", tcpSock);
		return;
	}
	storage->createDataObject(name,data);
}

// initializes cloned object
void VAR::initialize(stringstream & ss,TCPSocket* p_tcpSock){
	tcpSock = p_tcpSock;
	string str = "";
	// storage will do the final check for whether or not it is of appropriate type
	getline(ss,str, ','); // isolate variable name
	name = str;
	getline(ss,str); // get rest of data
	// comma counting is a bit strange here, because assign takes strings and there can be commas within strings
	data = str;
}
