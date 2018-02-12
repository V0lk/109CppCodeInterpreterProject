//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Implementation file for MULT
// Multiply all parameters excluding the first one and store the results in first parameter

#include "MULT.h"

MULT::MULT(){tcpSock = NULL;}

void MULT::initialize(stringstream & ss,TCPSocket* p_tcpSock){
	tcpSock = p_tcpSock;
	count=0;
	result=0;
	string str= "";
	tmp=0;

	getline(ss,str,',');
	cleanString(str);
	name=str;
	getline(ss,str);
}

void MULT::cleanString(string line){
	line.erase(remove(line.begin(),line.end(), '\t'),line.end()); // removing tabs
	line.erase(remove(line.begin(),line.end(), '\n'),line.end()); // removing new line token
	line.erase(remove(line.begin(),line.end(), '\r'),line.end()); // removing new line token
	line.erase(remove(line.begin(),line.end(), ' '),line.end()); // removing spaces
}

Expression* MULT::clone(stringstream & ss,TCPSocket* p_tcpSock){
	MULT *mult = new MULT();
	mult->initialize(ss,p_tcpSock);
	return mult;

}

void MULT::execute(Storage* s, Parse* p){
	stringstream ss(str);
	count=0;
	if(getTarget(name, s)){
		//If true, Real
		while(getline(ss,str,',')){
			if(count==13){
				Logger::printToError("Error from MULT: invalid parameters. Please enter 1-13 commands",tcpSock);
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

			result *= tmp;	//Add into result. Loop
			count++;
		}
	}else{
		//else Numeric
		while(getline(ss,str,',')){
			if(count==13){
				Logger::printToError("Error from MULT: invalid parameters. Please enter 1-13 commands",tcpSock);
			}
			cleanString(str);
			if(s->findVariable(str)){
				if(s->getVariableType(str)=="REAL"){
					Logger::printToError("From MULT: Incompatible Type.",tcpSock);
					return;
				}else{
					tmp=s->getNumericData(str);
				}
			}else{
				tmp = strtof(str.c_str(),NULL);
			}
			result*=tmp;
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

//Gets the type of variable to be saved
bool MULT::getTarget(string name, Storage* s){
if(s->getVariableType(name)=="REAL"){return true;}
	else if(s->getVariableType(name)=="NUMERIC"){return false;}
	else{Logger::printToError("From MULT: Incompatible type.",tcpSock);
	return false;}
}

MULT::~MULT(){}
