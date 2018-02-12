//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Header file for abstract class Expression

#ifndef _EXPRESSION_
#define _EXPRESSION_

#include "common.h"
#include "storage.h"
#include "parse.h"
#include "logger.h"
#include "TCPSocket.h"

using namespace std;

class Expression{
	private:
		TCPSocket* tcpSock;
	public:
		Expression(){};
		virtual Expression* clone(stringstream & ss, TCPSocket* p_tcpSock) = 0; // creates a copy of expression
		virtual void execute(Storage* s, Parse* p) = 0; // executes an operation
		virtual void initialize(stringstream & ss, TCPSocket* p_tcpSock) = 0; // initializes expression
		virtual ~Expression(){};
};

#endif
