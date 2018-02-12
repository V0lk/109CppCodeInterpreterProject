//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Implementation file for DIV
// Divide the second parameter by the third and store result into the first parameter

#include "DIV.h"
DIV::DIV(){tcpSock = NULL;}
void DIV::initialize(stringstream & s, TCPSocket* p_tcpSock){
	string str="";
	getline(s,str,',');
	cleanString(str);
	name= str;
	getline(s,str);
	tcpSock = p_tcpSock;
}
void DIV::cleanString(string line){
	line.erase(remove(line.begin(),line.end(), '\t'),line.end()); // removing tabs
	line.erase(remove(line.begin(),line.end(), '\n'),line.end()); // removing new line token
	line.erase(remove(line.begin(),line.end(), '\r'),line.end()); // removing new line token
	line.erase(remove(line.begin(),line.end(), ' '),line.end()); // removing spaces
}

void DIV::execute(Storage* s, Parse* p){

stringstream ss(str);
	result=0;
	count = 0;
	if(getTarget(name, s)){
		//If true, Real
		while(getline(ss, str, ',')){
			if(count==2){
				Logger::printToError("From DIV: DIV takes no more than 2 parameters.", tcpSock);
				return;
			}
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

		// To avoid divide by 0 and 0/param1 //
		if(count==0){			
			result = tmp;
		}else{
			if(count==1 && tmp==0){			//To divide by 0
			Logger::printToError("From DIV: Illegal action divide by 0.",tcpSock);
			return;
			}		
			result= result/tmp;
		}
			count++;	//Increment counter
		}
	}else{
		//else Numeric
		while(getline(ss,str,',')){
			if(count==2){
				Logger::printToError("From DIV: DIV takes no more than 2 parameters.",tcpSock);
				return;
			}
			if(s->findVariable(str)){
				if(s->getVariableType(str)=="REAL"){
					Logger::printToError("From DIV: Incompatible Type.",tcpSock);
					return;
				}else{
					tmp=s->getNumericData(str);
				}
			}else{
				tmp = strtof(str.c_str(),NULL);
			}
		// To avoid divide by 0 and 0/param1 //
		if(count==0){			
			result = tmp;
		}else{
			if(count==1 && tmp==0){	
			Logger::printToError("From DIV: Illegal action divide by 0.",tcpSock);
			return;
			}		
			result= result/tmp;
		}
			count++;	//Increment counter
		}

	}

//Find target Variable to be saved into
	if(s->findVariable(name)){
		if(s->getVariableType(name)=="NUMERIC"){
			s->setNumericData(name,result);
		}else if(s->getVariableType(name)=="REAL"){
			s->setRealData(name,result);
		}
	}else{
		Logger::printToError("From DIV: Variable " + name +" not found.",tcpSock);
	}
}

//Creates a new DIV
Expression* DIV::clone(stringstream & ss,TCPSocket* p_tcpSock){
	DIV *div = new DIV();
	div->initialize(ss,p_tcpSock);
	return div;

}

bool DIV::getTarget(string name, Storage* s){
if(s->getVariableType(name)=="REAL"){return true;}
	else if(s->getVariableType(name)=="NUMERIC"){return false;}
	else{Logger::printToError("From DIV: Incompatible type.",tcpSock);
	return false;}
}

DIV::~DIV(){}
