#ifndef _JMPGT_
#define _JMPGT_

#include "expression.h"
using namespace std;

class JMPGT: public Expression{
	private:
		string label;
		string var1;
		string var2;
		TCPSocket* tcpSock;
	public:
		JMPGT();
		JMPGT(string l, string v1, string v2, TCPSocket* p_tcpSock);
		virtual Expression* clone(stringstream & ss, TCPSocket* p_tcpSock);
		virtual void execute(Storage*, Parse*);
		virtual void initialize(stringstream & ss, TCPSocket* p_tcpSock);
		virtual ~JMPGT();
};

#endif
