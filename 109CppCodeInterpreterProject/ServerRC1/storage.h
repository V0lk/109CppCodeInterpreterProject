//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Header file for Storage
// manages all data for the MIS

#ifndef _STORAGE_
#define _STORAGE_

// common includes
#include "common.h"
#include "dataType.h"
#include "dataFactory.h"
#include "TCPSocket.h"

// data type includes
#include "MISNumeric.h"
#include "MISReal.h"
#include "MISString.h"
#include "MISChar.h"

using namespace std;

class Storage{
	private:
		map<string, int> label;
		map<string, DataType*> variable;
		DataFactory *df;
		TCPSocket * tcpSock;
	public:
		// constructor destructor
		Storage(TCPSocket* p_tcpSock);
		~Storage();
		
		// label instructions
		void insertLabel(string, int); // generates a label at index
		int getIndexOf(string); // gets the index of a label
		bool findLabel(string); // checks if a label exists
		
		// generic variable functions
		void createDataObject(string, string); // creates a new object of datatype
		string getVariableType(string); // returns type of data entry
		void printStorageVariables();
		bool findVariable(string);
		
		// type specific variable functions
		// 	NUMERIC
		long long getNumericData(string);
		void setNumericData(string, long long);
		
		//  REAL
		double getRealData(string);
		void setRealData(string, double);
		
		// 	CHAR
		char getCharData(string);
		void setCharData(string, char);
		
		// STRING
		string getStringData(string);
		int getStringLength(string);
		void setStringData(string,string);
		//void setStringIndexData(char, int);
		
		
};

#endif
