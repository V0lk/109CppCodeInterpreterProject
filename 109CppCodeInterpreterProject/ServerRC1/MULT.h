//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Header file for MULT
// Multiply all parameters excluding the first one and store the results in first parameter

#ifndef _MULT_
#define _MULT_
#include "common.h"
#include "expression.h"
using namespace std;
class MULT: public Expression{
	private:
		double result;
		double tmp;
		int count;
		string str;
		string name;
		TCPSocket* tcpSock;
	public:
		MULT();		//Default Const
		MULT(stringstream & ss); //Parametrized
		void cleanString(string);
		void initialize(stringstream & ss,TCPSocket* p_tcpSock);
		void execute(Storage*, Parse*);
		Expression* clone(stringstream & ss,TCPSocket* p_tcpSock);
		bool getTarget(string, Storage*);
		~MULT();
};
#endif
