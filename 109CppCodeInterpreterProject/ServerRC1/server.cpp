#include "common.h"
#include "includes.h"

#include "garbagecollector.h"
#include "TCPServerSocket.h"

int main(int argc, char** argv){
	TCPServerSocket *tcpServerSocket = new TCPServerSocket("0.0.0.0",7777,100);
	GarbageCollector* garbageCollector = new GarbageCollector();
	tcpServerSocket->initializeSocket();
	for(;;){
		TCPSocket* tcpSocket = tcpServerSocket->getConnection();
		cout << "Incoming connection from: " << tcpSocket-> getRemoteAddress() << endl;
		if(tcpSocket ==NULL){
			cout << "Connection refused" << endl;
		}
		else{
			cout << "Connection accepted" << endl;
			garbageCollector->cleanup();
			Connection *c = new Connection(tcpSocket);
			c->start();
			garbageCollector->addConnection(c);
		}
	}
	delete(garbageCollector);
	delete(tcpServerSocket);
}
