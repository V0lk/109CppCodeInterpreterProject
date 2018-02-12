//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Implementation file for MISString
// Data Type MISString


#include "MISString.h"
using namespace std;

// constructors
// default constructor
MISString::MISString():MISString("undefined", 10, NULL){}

// parameterized constructor
MISString::MISString(string s, int l, TCPSocket* p_tcpSock){
	type = "STRING";
	tcpSock = p_tcpSock;
	if (l > 256){
		tcpSock->writeToSocket("ERROR MISString: length is greater than 256\n", strlen("ERROR MISString: length is greater than 256\n"));
	}
	maxLength = l;
	if (s.length() > maxLength){ // throws a compiler warning, but checks earlier guarantee it positive
		tcpSock->writeToSocket("ERROR MISString: string is greater than destination's size\n", strlen("ERROR MISString: string is greater than destination's size\n"));
	}
	data = s;
}

// getType()
// returns the type of string
string MISString::getType(){
	return type;
}

// 
string MISString::getValue(){
	return data;
}

void MISString::setValue(string s){
	if(s.length() > maxLength){		// throws a compiler warning, but checks earlier guarantee it positive
		tcpSock->writeToSocket("ERROR MISString: assignment length is bigger than size\n",strlen("From MISString: assignment length is bigger than size\n"));
		return;
	}
	data = s;
}

// getLength()
int MISString::getLength(){
	return maxLength;
}

void MISString::setValueAtIndex(int i, char c){
	if(i > maxLength){
		return;
	}
	else{
		data[i] = c;
	}
}
		
DataType* MISString::clone(stringstream & s, TCPSocket* p_tcpSock){
	MISString *temp = new MISString();
	temp->initialize(s,p_tcpSock);
	if(temp->getType() == "INVALID"){ // if initialization failed
		delete temp; // delete data
		return NULL; // return
	}
	return temp;
}

void MISString::initialize(stringstream & s,TCPSocket* p_tcpSock){
	tcpSock = p_tcpSock;
	// get length
	string t = "";
	getline(s, t, ',');
	int checkLength = stoi(t);
	if( checkLength > 257 || checkLength < 1 ){
		tcpSock->writeToSocket("ERROR MISString: length is invalid\n", strlen("ERROR MISString: length is invalid\n"));
		type = "INVALID";
		return;
	}
	maxLength = checkLength;
	// get data between quotes
	getline(s, t, '"'); 
	getline(s, t, '"');
	// check size
	if(t.length() > maxLength){  // throws a compiler warning, but checks earlier guarantee it positive
		tcpSock->writeToSocket("ERROR MISString: assignment length is bigger than size\n",strlen("From MISString: assignment length is bigger than size\n"));
		type = "INVALID";
		return;
	}
	data = t;
}
		
MISString::~MISString(){}
