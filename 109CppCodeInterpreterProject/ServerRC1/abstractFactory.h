//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Header file for pure virtual abstract factory
// Templated pure virtual factory class


#ifndef _ABSTRACTFACTORY
#define _ABSTRACTFACTORY

#include "common.h"
#include "TCPSocket.h"

using namespace std;

template<class T>
class AbstractFactory{
	private:
		map<string,T*> objs; // map containing pointers to object T
	public:
		AbstractFactory(){}; // constructor
		virtual T* getObject(string,TCPSocket* p_tcpSock) = 0; // generate a new object of type T
		virtual ~AbstractFactory(){}; // destructor
};

#endif
