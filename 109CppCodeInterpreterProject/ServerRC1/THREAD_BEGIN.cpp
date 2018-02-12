#include "THREAD_BEGIN.h"
#include "expressionFactory.h"

// Constructor
THREAD_BEGIN::THREAD_BEGIN():THREAD_BEGIN(NULL){}

THREAD_BEGIN::THREAD_BEGIN(TCPSocket *p_tcpSocket): Thread(){
	tcpSocket = p_tcpSocket;
}

// Destructor
THREAD_BEGIN::~THREAD_BEGIN(){
	if(tcpSocket != NULL){
		delete(tcpSocket);
	}
	if(s != NULL){
		delete(s);
	}
}

Expression* THREAD_BEGIN::clone(stringstream & ss,TCPSocket* p_tcpSock){
	THREAD_BEGIN* tester = new THREAD_BEGIN();
	tester->initialize(ss,p_tcpSock);
	return tester;
}

void THREAD_BEGIN::execute(Storage* s, Parse* p){
	p->nextLine();
	string label;
	while(p->hasNextLine() == true){
		stringstream iss(p->getLine());
		getline(iss,label);
		if(label == "THREAD_END"){
			break;
		}
		this->data.append(label);
		p->nextLine();
	}
	this->s = s;
	
	this->start();
}

void THREAD_BEGIN::initialize(stringstream & ss,TCPSocket* p_tcpSock){
	tcpSock = p_tcpSock;
}

void* THREAD_BEGIN::threadMainBody(void*arg){
	// normal operation
	if(this->data.length() > 0){
		// old client input in here

		// generate objects to be used
		// Storage* s = new Storage(tcpSocket);
		Parse*p = new Parse(this->data);
		ExpressionFactory* f = new ExpressionFactory;
		Expression* e = nullptr;

		// normal operation
		while(p->hasNextLine() == true){
			e = f->getObject(p->getLine(),tcpSocket);
			if(e != NULL){
				e->execute(s,p);
				delete e;
			}
			p->nextLine();
		}	

		// free pointers
		delete p; // delete parser
		delete f; // delete expression factory
	}
	// terminate
	tcpSocket->shutDown();
	return NULL;
}


