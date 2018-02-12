//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Implementation for SLEEP
// sleeps the thread for n seconds

#include "SLEEP.h"
// constructors and destructors
// default constructor
SLEEP::SLEEP():SLEEP("0",NULL){}

// parametrized constructor
SLEEP::SLEEP(string s,TCPSocket* p_tcpSock){
	seconds = s;
	tcpSock = p_tcpSock;
}

// destructor
SLEEP::~SLEEP(){}

// Public Functions
// clones object	
Expression* SLEEP::clone(stringstream & ss,TCPSocket* p_tcpSock){
	SLEEP* sleeper = new SLEEP();
	sleeper->initialize(ss,p_tcpSock);
	return sleeper;
}

//execute()
// sleep's logic function
void SLEEP::execute(Storage* s, Parse* p){
	long time = 0;
	
	// case for variables
	if(seconds.front() == '$'){ // checking for variables
		string type = s->getVariableType(seconds);
		if(type == "NUMERIC"){
			time = (long)s->getNumericData(seconds);
		}
		else if(type == "REAL"){
			time = (long)s->getRealData(seconds);
		}
		else{
			Logger::printToError("From SLEEP: " + seconds + " is not of a numeric type",tcpSock);
		}
	}
	// case for numerics
	else{
		// check if it is a valid number
		char* p;
		time = strtol(seconds.c_str(), &p, 10);
		if(*p){
			Logger::printToError("From SLEEP: " + seconds + " is not a valid numeric",tcpSock);
			return;
		}
	}
	// sleep the thread for time seconds
	std::this_thread::sleep_for(std::chrono::seconds(time));
	
}

//initialize()
// initialization function, run by clone
void SLEEP::initialize(stringstream & ss,TCPSocket* p_tcpSock){
	tcpSock = p_tcpSock;
	string str = "";
	getline(ss,str);
	if(str.empty()){ // if nothing returned
		Logger::printToError("From SLEEP: expected 1 parameter (has 0)",tcpSock);
		return;
	}
	int n = count(str.begin(),str.end(),',');
	if(n == 0){
		seconds = str;
	}
	else{
		Logger::printToError("From SLEEP: expected 1 parameter (has more than 1)",tcpSock);
	}
	
}
