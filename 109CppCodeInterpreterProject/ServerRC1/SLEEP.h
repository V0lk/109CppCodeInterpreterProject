//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Header file for SLEEP
// sleeps the thread for n seconds

#ifndef _SLEEP_
#define _SLEEP_

#include "expression.h"

class SLEEP:public Expression{
	private: 
		string seconds;
		TCPSocket* tcpSock;
	public:
		SLEEP();
		SLEEP(string s,TCPSocket* p_tcpSock);
		virtual Expression* clone(stringstream & ss,TCPSocket* p_tcpSock);
		virtual void execute(Storage*, Parse*);
		virtual void initialize(stringstream & ss,TCPSocket* p_tcpSock);
		virtual ~SLEEP();
};

#endif
