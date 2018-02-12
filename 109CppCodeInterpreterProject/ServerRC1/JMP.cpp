//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Implementation file for JMP
// Unconditionally jumps to a label

#include "JMP.h"
using namespace std;

// Constructors and Destructors
// default constructor
JMP::JMP():JMP("",NULL){}

// parameterized constructor
JMP::JMP(string l,TCPSocket* p_tcpSock){
	label = l;
	tcpSock = p_tcpSock;
}

// destructor
JMP::~JMP(){} 

// Public Functions
// clones object	
Expression* JMP::clone(stringstream & ss,TCPSocket* p_tcpSock){
	JMP* tester = new JMP();
	tester->initialize(ss,p_tcpSock);
	return tester;
}

// executes the  command
void JMP::execute(Storage* storage, Parse* p){
	if(storage->findLabel(label)){
		p->setIndex(storage->getIndexOf(label));
	}
	else{
		Logger::printToError("From JMP: " + label + " is not a valid label", tcpSock);
	}
}

// initializes cloned object
void JMP::initialize(stringstream & ss,TCPSocket* p_tcpSock){
	tcpSock = p_tcpSock;
	string str = "";
	getline(ss,str); // get label
	
	int n = count(str.begin(),str.end(),','); // count commas
	if(n == 0){ // first comma was already parsed
		label = str;
	}
	else{
		Logger::printToError("From JMP: expected 1 parameter (has more than 1)",tcpSock);
	}

}
