//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Implementation file for MISNumeric
// Data Type MISNumeric

#include "MISNumeric.h"

//Constructors and Destructors
// default constructor
MISNumeric::MISNumeric():MISNumeric(0,NULL){}

// 1 parameter constructor
MISNumeric::MISNumeric(int v, TCPSocket* p_tcpSock){
	type = "NUMERIC";
	value = v;
	tcpSock = p_tcpSock;
}

// destructor
MISNumeric::~MISNumeric(){}

// Public Functions
string MISNumeric::getType(){
	return type;
}

long long MISNumeric::getValue(){
	return value;
}

void MISNumeric::setValue(long long v){
	value = v;
}

DataType* MISNumeric::clone(stringstream & s,TCPSocket* p_tcpSock){
	MISNumeric *temp = new MISNumeric();
	temp->initialize(s,p_tcpSock);
	if(temp->getType() == "INVALID"){ // if initialization failed
		delete temp; // delete data
		return NULL; // return
	}
	return temp;
}

void MISNumeric::initialize(stringstream & s,TCPSocket* p_tcpSock){
	tcpSock = p_tcpSock;
	string t = "";
	getline(s, t, ',');
	value = stoll(t);
}
