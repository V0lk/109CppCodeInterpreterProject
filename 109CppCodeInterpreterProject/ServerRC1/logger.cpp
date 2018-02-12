//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Implementation file for static logger
// global accessable simple logger


#include "logger.h"
#include <chrono>
#include <thread>


// prints statement to the end of *.out
void Logger::printToOutput(const string& o, TCPSocket* destinationSocket){
	string output = "OUTPUT "+o;
	const char* outputOut = output.c_str();
	destinationSocket->writeToSocket(outputOut, strlen(outputOut));
	std::this_thread::sleep_for(std::chrono::milliseconds(40));
}

// prints statement to end of *.err
void Logger::printToError(const string& e, TCPSocket* destinationSocket){
	string error = "ERROR "+e + '\n';
	const char* errOut = error.c_str();
	destinationSocket->writeToSocket(errOut, strlen(errOut));
	std::this_thread::sleep_for(std::chrono::milliseconds(40));
}
