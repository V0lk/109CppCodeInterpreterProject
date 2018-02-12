#ifndef _JMPLTE_
#define _JMPLTE_

#include "expression.h"
using namespace std;

class JMPLTE: public Expression{
	private:
		string label;
		string var1;
		string var2;
		TCPSocket* tcpSock;
	public:
		JMPLTE();
		JMPLTE(string l, string v1, string v2,TCPSocket* p_tcpSock);
		virtual Expression* clone(stringstream & ss,TCPSocket* p_tcpSock);
		virtual void execute(Storage*, Parse*);
		virtual void initialize(stringstream & ss,TCPSocket* p_tcpSock);
		virtual ~JMPLTE();
};

#endif
