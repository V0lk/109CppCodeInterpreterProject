//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Header file for static logger
// global accessable simple logger

#ifndef _LOGGER
#define _LOGGER

#include "common.h"
#include "TCPSocket.h"
using namespace std;

class Logger{
	private:
	public:
		static void printToOutput(const string&, TCPSocket*);
		static void printToError(const string&, TCPSocket*);
};

#endif
