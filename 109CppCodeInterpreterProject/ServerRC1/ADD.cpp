//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Implementation file for ADD
// Adds all parameters excluding the first one and stores the results in the first parameter

#include "ADD.h"

ADD::ADD(){tcpSock = NULL;}

void ADD::initialize(stringstream & ss, TCPSocket* p_tcpSock){
	tcpSock = p_tcpSock;
	count=0;
	result=0;
	str= "";
	tmp=0;
	getline(ss,str,',');
	cleanString(str);
	name = str;
	getline(ss,str); //Gets the remainder of the string
}

void ADD::cleanString(string line){
	line.erase(remove(line.begin(),line.end(), '\t'),line.end()); // removing tabs
	line.erase(remove(line.begin(),line.end(), '\n'),line.end()); // removing new line token
	line.erase(remove(line.begin(),line.end(), '\r'),line.end()); // removing new line token
	line.erase(remove(line.begin(),line.end(), ' '),line.end()); // removing spaces
}

bool ADD::getTarget(string name, Storage* s){
if(s->getVariableType(name)=="REAL" || s->getVariableType(name) == "NUMERIC"){return true;}
	else{Logger::printToError("From ADD: Incompatible type provided", tcpSock);
	return false;}
}

void ADD::execute(Storage* s, Parse* p){
	stringstream ss(str);
	count=0;
	if(getTarget(name, s)){
		//If true, Real
		while(getline(ss,str,',')){
			if(count==13){
				Logger::printToError("From ADD: invalid parameters count (expected 1-13)", tcpSock);
			}
			cleanString(str);
			if(s->findVariable(str)){	//checks to see if
										//variable exists
				if(s->getVariableType(str)=="REAL"){
					tmp=s->getRealData(str);	//if Real get real data
				}else{
					tmp=s->getNumericData(str);
				}
			}else{
				tmp = strtof(str.c_str(),NULL);
			}

			result += tmp;	//Add into result. Loop
			count++;
		}
	}else{
		//else Numeric
		while(getline(ss,str,',')){
			if(count==13){
				Logger::printToError("From ADD: invalid parameters count (expected 1-13)", tcpSock);
			}
			cleanString(str);
			if(s->findVariable(str)){
				if(s->getVariableType(str)=="REAL"){
					Logger::printToError("From ADD: Incompatible type provided\n", tcpSock);
					return;
				}else{
					tmp=s->getNumericData(str);
				}
			}else{
				tmp = strtof(str.c_str(),NULL);
			}
			result+=tmp;
			count++;
		}
	}

	if(s->findVariable(name)){
		if(s->getVariableType(name)=="NUMERIC"){
			s->setNumericData(name,result);
		}else if(s->getVariableType(name)=="REAL"){
			s->setRealData(name,result);
		}
	}
}

Expression* ADD::clone(stringstream & ss, TCPSocket* p_tcpSock){
	ADD* add = new ADD;
	add->initialize(ss,p_tcpSock);
	return add;

}
ADD::~ADD(){}
