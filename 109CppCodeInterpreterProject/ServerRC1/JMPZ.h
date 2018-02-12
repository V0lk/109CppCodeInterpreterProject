//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Header file for JMPZ
// Jumps if parameter 2 is zero

#ifndef _JMPZ_
#define _JMPZ_

#include "expression.h"
using namespace std;

class JMPZ: public Expression{
	private:
		string label;
		string variable;
		TCPSocket* tcpSock;
	public:
		JMPZ();
		JMPZ(string l, string v,TCPSocket* p_tcpSock);
		virtual Expression* clone(stringstream & ss,TCPSocket* p_tcpSock);
		virtual void execute(Storage*, Parse*);
		virtual void initialize(stringstream & ss,TCPSocket* p_tcpSock);
		virtual ~JMPZ();
};

#endif
