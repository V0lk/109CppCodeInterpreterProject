#ifndef _CONNECTION_
#define _CONNECTION_

#include "Thread.h"
#include "TCPSocket.h"

// A class representing a single connection from a client
class Connection : public Thread
{
	private:
		TCPSocket * tcpSocket;
		Connection * next_connection;
	public:
		Connection(TCPSocket* p_tcpSocket);
		void * threadMainBody(void*arg);
		void setNextConnection(Connection* connection);
		Connection * getNextConnection();
		~Connection();
};
#endif
