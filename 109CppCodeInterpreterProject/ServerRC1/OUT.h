//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Header file for OUT
// Prints variables and constants

#ifndef _OUT_
#define _OUT_

#include "expression.h"
using namespace std;

class OUT:public Expression{
	private: 
		string data;
		TCPSocket* tcpSock;
	public:
		OUT();
		OUT(string,TCPSocket* p_tcpSock);
		virtual Expression* clone(stringstream & ss,TCPSocket* p_tcpSock);
		virtual void execute(Storage*, Parse*);
		virtual void initialize(stringstream & ss,TCPSocket* p_tcpSock);
		virtual ~OUT();
};

#endif
