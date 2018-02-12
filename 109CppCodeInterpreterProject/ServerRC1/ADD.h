//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Header file for ADD
// Adds all parameters excluding the first one and stores the results in the first parameter

#ifndef _ADD_
#define _ADD_

#include "common.h"
#include "expression.h"
using namespace std;

class ADD: public Expression{
private:
	double count;
	double result;
	double tmp;
	string str;
	string name;
	TCPSocket* tcpSock;

public:
	 ADD();		// const/destructors
	 //ADD(stringstream & ss); //dne
	 ~ADD();
	
	//Inherited functions
	 void initialize(stringstream & ss, TCPSocket* tcpSock);
	 void execute(Storage*, Parse*);
	 Expression* clone(stringstream & ss, TCPSocket* tcpSock);

	 //Cleans up the string
	 void cleanString(string);

	 //Gets type to be saved
	bool getTarget(string, Storage*);
	

};
#endif
