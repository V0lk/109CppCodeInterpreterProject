#ifndef _JMPGTE_
#define _JMPGTE_

#include "expression.h"
using namespace std;

class JMPGTE: public Expression{
	private:
		string label;
		string var1;
		string var2;
		TCPSocket* tcpSock;
	public:
		JMPGTE();
		JMPGTE(string l, string v1, string v2, TCPSocket* p_tcpSock);
		virtual Expression* clone(stringstream & ss, TCPSocket* p_tcpSock);
		virtual void execute(Storage*, Parse*);
		virtual void initialize(stringstream & ss, TCPSocket* p_tcpSock);
		virtual ~JMPGTE();
};

#endif
