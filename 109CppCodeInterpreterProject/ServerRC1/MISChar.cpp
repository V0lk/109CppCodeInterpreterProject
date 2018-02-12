//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Implementation file for MISCHAR
// Data Type MISCHAR


#include "MISChar.h"

MISChar::MISChar():MISChar('\n', NULL){}

MISChar::MISChar(char c, TCPSocket* p_tcpSock){
	type = "CHAR";
	value = c;
	tcpSock = p_tcpSock;
}

		
string MISChar::getType(){
	return type;
}
char MISChar::getValue(){
	return value;
}
void MISChar::setValue(char c){
	value = c;
}
		
DataType* MISChar::clone(stringstream & s, TCPSocket* p_tcpSock){
	MISChar *temp = new MISChar(); // can we just do new parameterized constructor?
	temp->initialize(s, p_tcpSock); // initialize
	if(temp->getType() == "INVALID"){ // if initialization failed
		delete temp; // delete data
		return NULL; // return
	}
	return temp;
}
void MISChar::initialize(stringstream & s, TCPSocket* p_tcpSock){
	tcpSock = p_tcpSock;
	string str;
	getline(s,str); // get the entire line
	if ( str.front() == '\'' ) {
		str.erase( 0, 1 ); // erase the first character
		str.erase( str.size() - 1 ); // erase the last character
	
	
		// check for special characters
		if(str == "\n"){ // new line
			value = '\n';
			return;
		}
		if(str == "\t"){ // tab
			value = '\t';
			return;
		}
		if(str == "\r"){ // new line
			value = '\r'; 
			return;
		}
		
		if(str.size() != 1){
			tcpSock->writeToSocket("ERROR MISChar: invalid char\n", strlen("ERROR MISChar: invalid char\n"));
			type = "INVALID"; // set type to invalid
			return;
		}
		// the only element left is here
		value = str[0];
	}
	else{
		type = "INVALID"; // set type to invalid
		tcpSock->writeToSocket("ERROR MISChar: invalid char\n", strlen("ERROR MISChar: invalid char\n"));
		return;
	}
}
		
MISChar::~MISChar(){}
