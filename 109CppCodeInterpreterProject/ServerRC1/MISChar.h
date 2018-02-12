//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Header file for MISCHAR
// Data Type MISCHAR


#ifndef _MISCHAR_
#define _MISCHAR_

#include "dataType.h"

class MISChar : public DataType{
	private:
		string type;
		char value;
		TCPSocket* tcpSock;
	public:
		MISChar();
		MISChar(char c, TCPSocket* p_tcpSock);
		
		string getType();
		char getValue();
		void setValue(char c);
		
		DataType* clone(stringstream & s, TCPSocket* p_tcpSock);
		void initialize(stringstream & s, TCPSocket* p_tcpSock);
		
		~MISChar();
};

#endif
