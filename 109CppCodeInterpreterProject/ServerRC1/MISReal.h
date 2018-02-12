//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Header file for MISReal
// Data Type MISReal


#ifndef _MISREAL_
#define _MISREAL_

#include "dataType.h"

class MISReal : public DataType{
	private:
		string type;
		double value;
		TCPSocket* tcpSock;
	public:
		MISReal();
		MISReal(double v, TCPSocket* p_tcpSock);
		
		string getType();
		double getValue();
		void setValue(double v);
		
		DataType* clone(stringstream & s, TCPSocket* p_tcpSock);
		void initialize(stringstream & s, TCPSocket* p_tcpSock);
		
		~MISReal();
};

#endif
