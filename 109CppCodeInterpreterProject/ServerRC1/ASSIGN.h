//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Header file for ASSIGN
// Store the second parameter into the first parameter

#ifndef _ASSIGN_
#define _ASSIGN_

#include "expression.h"
using namespace std;

class ASSIGN: public Expression{
	private:
		string variable1;
		string variable2;
		TCPSocket* tcpSock;
	public:
		ASSIGN();
		ASSIGN(string v1, string v2, TCPSocket* tcpSock);
		virtual Expression* clone(stringstream & ss, TCPSocket* p_tcpSock);
		virtual void execute(Storage*, Parse*);
		virtual void initialize(stringstream & ss, TCPSocket* p_tcpSock);
		virtual ~ASSIGN();
};

#endif
