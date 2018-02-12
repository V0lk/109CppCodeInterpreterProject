#ifndef _THREAD_BEGIN_
#define _THREAD_BEGIN_

#include "Thread.h"
#include "expression.h"
#include "TCPSocket.h"

class THREAD_BEGIN : public Expression, public Thread
{
	private:
		TCPSocket * tcpSocket;
		string data;
		Stoarage * s;
	public:
		THREAD_BEGIN(TCPSocket* p_tcpSocket);
		void * threadMainBody(void*arg);
		virtual Expression* clone(stringstream & ss,TCPSocket* p_tcpSock);
		virtual void execute(Storage*, Parse*);
		virtual void initialize(stringstream & ss,TCPSocket* p_tcpSock);
		~THREAD_BEGIN();
};
#endif
