#ifndef _GARBAGE_COLLECTOR_
#define _GARBAGE_COLLECTOR_

#include "connection.h"

class GarbageCollector{
	private:
		Connection* head;
		Connection* tail;
	public:
		GarbageCollector();
		void addConnection(Connection* connection);
		void cleanup();
		void terminate();
		~GarbageCollector();
};

#endif
