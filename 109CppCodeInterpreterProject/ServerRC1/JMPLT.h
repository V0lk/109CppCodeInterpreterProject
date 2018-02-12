#ifndef _JMPLT_
#define _JMPLT_

#include "expression.h"
using namespace std;

class JMPLT: public Expression{
	private:
		string label;
		string var1;
		string var2;
		TCPSocket* tcpSock;
	public:
		JMPLT();
		JMPLT(string l, string v1, string v2, TCPSocket* p_tcpSock);
		virtual Expression* clone(stringstream & ss, TCPSocket* p_tcpSock);
		virtual void execute(Storage*, Parse*);
		virtual void initialize(stringstream & ss, TCPSocket* p_tcpSock);
		virtual ~JMPLT();
};

#endif
