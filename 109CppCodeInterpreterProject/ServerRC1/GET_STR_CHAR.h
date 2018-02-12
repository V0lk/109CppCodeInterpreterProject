#ifndef _GET_STR_CHAR_
#define _GET_STR_CHAR_

#include "expression.h"
using namespace std;

class GET_STR_CHAR:public Expression{
	private:
		string var1;
		string var2;
		int index;
		TCPSocket* tcpSock;
	public:
		GET_STR_CHAR();
		GET_STR_CHAR(string a, string b, int i,TCPSocket* p_tcpSock);
		virtual Expression* clone(stringstream & ss, TCPSocket* p_tcpSock);
		virtual void execute(Storage*, Parse*);
		virtual void initialize(stringstream & ss, TCPSocket* p_tcpSock);
		virtual ~GET_STR_CHAR();
};

#endif
