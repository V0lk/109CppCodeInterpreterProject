//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Implementation file for MISNumeric
// Data Type MISNumeric


#ifndef _MISNUMERIC_
#define _MISNUMERIC_

#include "dataType.h"

class MISNumeric : public DataType{
	private:
		string type;
		long long value;
		TCPSocket* tcpSock;
	public:
		MISNumeric();
		MISNumeric(int v, TCPSocket* p_tcpSock);
		
		string getType();
		long long getValue();
		void setValue(long long v);
		
		DataType* clone(stringstream & s, TCPSocket* p_tcpSock);
		void initialize(stringstream & s, TCPSocket* p_tcpSock);
		
		~MISNumeric();
};

#endif
