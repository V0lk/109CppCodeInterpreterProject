//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Implementation file for MISReal
// Data Type MISReal


#include "MISReal.h"
using namespace std;

//Constructors and Destructors
// default constructor
MISReal::MISReal():MISReal(0, NULL){}

// parameterized constructor
MISReal::MISReal(double v, TCPSocket* p_tcpSock){
	type = "REAL";
	value = v;
	tcpSock = p_tcpSock;
}

// destructor
MISReal::~MISReal(){}

// Public Functions

string MISReal::getType(){
	return type;
}

double MISReal::getValue(){
	return value;
}

void MISReal::setValue(double v){
	value = v;
}

DataType* MISReal::clone(stringstream & s, TCPSocket* p_tcpSock){
	MISReal *temp = new MISReal();
	temp->initialize(s, p_tcpSock);
	if(temp->getType() == "INVALID"){ // if initialization failed
		delete temp; // delete data
		return NULL; // return
	}
	return temp;
}

void MISReal::initialize(stringstream & s, TCPSocket* p_tcpSock){
	tcpSock = p_tcpSock; // update socket information
	string t = "";
	getline(s, t, ',');
	value = stod(t);
}
