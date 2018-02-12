#include "connection.h"
#include "expressionFactory.h"
#include "parse.h"
#include "storage.h"

// Constructor
Connection::Connection(TCPSocket *p_tcpSocket): Thread(){
	tcpSocket = p_tcpSocket;
	next_connection = NULL;
}

// Destructor
Connection::~Connection(){
	if(tcpSocket != NULL){
		delete(tcpSocket);
	}
}

// Modifiers
void Connection::setNextConnection(Connection * connection) {
	next_connection = connection;
}

Connection * Connection::getNextConnection() {
	return next_connection;
}

void* Connection::threadMainBody(void*arg){
	char inputFile[1024*32]; // half the size of max TCP
	memset(inputFile,0,1024*32);
	int read_bytes = tcpSocket->readFromSocket(inputFile,1024*32-1);
	// normal operation
	if(read_bytes > 0){
		// old client input in here

		// generate objects to be used
		Storage* s = new Storage(tcpSocket);
		Parse*p = new Parse(inputFile);
		ExpressionFactory* f = new ExpressionFactory;
		Expression* e = nullptr;

		// checking for labels
		string isLabel, labelName;
		while(p->hasNextLine() == true){
			stringstream iss(p->getLine());
			getline(iss,isLabel,' ');
			if(isLabel == "LABEL"){
				getline(iss,labelName);
				s->insertLabel(labelName,p->getIndex());
			}
			p->nextLine();
		}
	
		// rewind the parser
		p->setIndex(0); 
		//p->printCode(); // debugging test prints

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
		delete s; // delete storage
		delete p; // delete parser
		delete f; // delete expression factory
	}
	// terminate
	tcpSocket->shutDown();
	return NULL;
}