//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Header file for SET_STR_CHAR
// Sets a string character at index to another char


#ifndef _SET_STR_CHAR_
#define _SET_STR_CHAR_

#include "expression.h"
using namespace std;

class SET_STR_CHAR:public Expression{
	private:
		string var1;
		string var2;
		int index;
		TCPSocket* tcpSock;
	public:
		SET_STR_CHAR();
		SET_STR_CHAR(string a, string b, int i,TCPSocket* p_tcpSock);
		virtual Expression* clone(stringstream & ss,TCPSocket* p_tcpSock);
		virtual void execute(Storage*, Parse*);
		virtual void initialize(stringstream & ss,TCPSocket* p_tcpSock);
		virtual ~SET_STR_CHAR();
};

#endif
