//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Header file for MISString
// Data Type MISString

#ifndef _MISSTRING_
#define _MISSTRING_

#include "dataType.h"

class MISString : public DataType{
	private:
		string type;
		string data;
		int maxLength;
		TCPSocket* tcpSock;
	public:
		MISString();
		MISString(string s, int l, TCPSocket* p_tcpSock);
		
		// string data operations
		string getType();
		string getValue();
		void setValue(string);
		
		// string length options
		int getLength();
		
		//char getChar(int index);
		void setValueAtIndex(int, char);
		
		DataType* clone(stringstream & s, TCPSocket* p_tcpSock);
		void initialize(stringstream & s, TCPSocket* p_tcpSock);
		
		~MISString();
};

#endif
