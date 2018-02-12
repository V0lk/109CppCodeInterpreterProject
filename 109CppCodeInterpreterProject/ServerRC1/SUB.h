//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Header file for SUB
// Subtracts the third parameter from the second parameter and stores the result in the first parameter

#ifndef _SUB_
#define _SUB_
#include "common.h"
#include "expression.h"
using namespace std;
//SUB target param1 param2
//	
// target=param1-param2
class SUB: public Expression{
	private:
		double param1;			//Parameters read from ss
		double param2;
		double result;			//result = param1-param2
		string name;
		string str;
		double tmp;
		int count;
		TCPSocket* tcpSock;
	public:
		SUB();				//Default constr
		SUB(stringstream& s);		//Parametrized Constructor
		void initialize(stringstream & ss,TCPSocket* p_tcpSock);		//Inherited init
		void execute(Storage*, Parse*);			//Inherited exe
		void cleanString(string);
		Expression* clone(stringstream & ss,TCPSocket* p_tcpSock);	//Inherited clone
		bool getTarget(string, Storage*);
		~SUB();				//Destructor

};
#endif
