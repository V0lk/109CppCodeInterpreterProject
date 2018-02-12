//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Header file for DIV
// Divide the second parameter by the third and store result into the first parameter

#ifndef _DIV_
#define _DIV_
#include "common.h"
#include "expression.h"
using namespace std;


class DIV: public Expression{
	private:
		double tmp;
		double result;
		int count;
		string str;
		string name;
		TCPSocket* tcpSock;

	public:
		DIV();	//Default Constructor
		DIV(stringstream & ss);
		void cleanString(string);
		void initialize(stringstream & ss,TCPSocket* tcpSock);
		void execute(Storage*, Parse*);
		bool getTarget(string, Storage*);
		Expression* clone(stringstream & ss,TCPSocket* tcpSock);
		~DIV();

};
#endif
