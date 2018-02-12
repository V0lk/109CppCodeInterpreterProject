#ifndef _JMP_
#define _JMP_

#include "expression.h"
using namespace std;

class JMP:public Expression{
	private:
		string label;
		TCPSocket* tcpSock;
	public:
		JMP();
		JMP(string l, TCPSocket* p_tcpSock);
		virtual Expression* clone(stringstream & ss,TCPSocket* p_tcpSock);
		virtual void execute(Storage*, Parse*);
		virtual void initialize(stringstream & ss,TCPSocket* p_tcpSock);
		virtual ~JMP();
};

#endif
		
