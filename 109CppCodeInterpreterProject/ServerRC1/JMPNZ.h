//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Header file for JMPNZ
// Jumps if parameter 2 is not zero

#ifndef _JMPNZ_
#define _JMPNZ_

#include "expression.h"
using namespace std;

class JMPNZ: public Expression{
	private:
		string label;
		string variable;
		TCPSocket* tcpSock;
	public:
		JMPNZ();
		JMPNZ(string l, string v,TCPSocket* p_tcpSock);
		virtual Expression* clone(stringstream & ss,TCPSocket* p_tcpSock);
		virtual void execute(Storage*, Parse*);
		virtual void initialize(stringstream & ss,TCPSocket* p_tcpSock);
		virtual ~JMPNZ();
};

#endif
