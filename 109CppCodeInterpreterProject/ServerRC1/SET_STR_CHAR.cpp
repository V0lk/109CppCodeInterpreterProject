//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Implementation file for SET_STR_CHAR
// Sets a string character at index to another char

#include "SET_STR_CHAR.h"

SET_STR_CHAR::SET_STR_CHAR():SET_STR_CHAR("undefined","undefined",0,NULL){}

SET_STR_CHAR::SET_STR_CHAR(string a, string b, int i,TCPSocket* p_tcpSock){
	var1 = a;
	var2 = b;
	index = i;
	tcpSock = p_tcpSock;
}

Expression* SET_STR_CHAR::clone(stringstream & ss,TCPSocket* p_tcpSock){
	SET_STR_CHAR* setter = new SET_STR_CHAR();
	setter->initialize(ss,p_tcpSock);
	return setter;
}

void SET_STR_CHAR::execute(Storage* s, Parse* p){
	if(!s->findVariable(var1)){
		Logger::printToError("From GET_STR_CHAR: " + var1 + " not found",tcpSock);
		return;
	}
	if(!s->findVariable(var2)){
		Logger::printToError("From GET_STR_CHAR: " + var2 + " not found",tcpSock);
		return;
	}
	if(s->getVariableType(var1) != "STRING"){
		Logger::printToError("From GET_STR_CHAR: " + var1 + " not a string",tcpSock);
		return;
	}
	if(s->getVariableType(var2) != "CHAR"){
		Logger::printToError("From GET_STR_CHAR: " + var2 + " not a char",tcpSock);
		return;
	}
	if(index >= s->getStringLength(var1)){
		Logger::printToError("From GET_STR_CHAR: " + var1 + " character index out of range",tcpSock);
		return;
	}
	string str = s->getStringData(var1);
	str[index] = s->getCharData(var2);
	s->setStringData(var1,str);
}

void SET_STR_CHAR::initialize(stringstream & ss,TCPSocket* p_tcpSock){
	tcpSock = p_tcpSock;
	string str = "";
	getline(ss,str,','); // get first param
	if(str.empty()){ // if nothing returned
		Logger::printToError("From SET_STR_CHAR: expected 3 parameters (has 0)",tcpSock);
		return;
	}
	var1 = str;
	
	if(ss.peek() == -1){ // if nothing returned
		Logger::printToError("From SET_STR_CHAR: expected 3 parameters (has 1)",tcpSock);
		return;
	}
	getline(ss,str,','); // get the variable
	index = (int)stoi(str);
	
	if(ss.peek() == -1){ // if nothing returned
		Logger::printToError("From SET_STR_CHAR: expected 3 parameters (has 2)",tcpSock);
		return;
	}
	getline(ss,str,',');
	var2 = str;
	
	if(ss.peek() != -1){ // if something returned
		Logger::printToError("From SET_STR_CHAR: expected 3 parameters (has more)",tcpSock);
		var1 = "";
		var2 = "";
		index = 0;
		return;
	}
}

SET_STR_CHAR::~SET_STR_CHAR(){}
