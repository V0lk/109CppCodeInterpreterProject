// Header file for abstract DataType class

#ifndef _DATA_TYPE_
#define _DATA_TYPE_

#include "common.h"
#include "TCPSocket.h"

using namespace std;

class DataType{
	private:
		string type;
		TCPSocket* tcpSock;
		
	public:
		DataType(){};
		virtual ~DataType(){};
		
		virtual string getType() = 0; // returns the type of data
		
		virtual DataType* clone(stringstream & s, TCPSocket*) = 0; // returns a copy of data type
		virtual void initialize(stringstream & s, TCPSocket*) = 0; // initializes the data type
};

#endif
