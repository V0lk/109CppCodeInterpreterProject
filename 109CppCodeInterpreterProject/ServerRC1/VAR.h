//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Header file for expression VAR
// Generates variable in storage

#ifndef _VAR_
#define _VAR_

#include "expression.h"
using namespace std;

class VAR:public Expression{
	private:
		string name;
		string data;
		TCPSocket* tcpSock;
	public:
		VAR();
		VAR(string s, string d,TCPSocket* p_tcpSock);
		virtual Expression* clone(stringstream & ss,TCPSocket* p_tcpSock);
		virtual void execute(Storage*, Parse*);
		virtual void initialize(stringstream & ss,TCPSocket* p_tcpSock);
		virtual ~VAR();
};

#endif
		
