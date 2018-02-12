//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Implementation file for SUB
// Subtracts the third parameter from the second parameter and stores the result in the first parameter

#include "SUB.h"

SUB::SUB(){tcpSock = NULL;}
void SUB::initialize(stringstream & s,TCPSocket* p_tcpSock){
	tcpSock = p_tcpSock;
	string str="";
	getline(s,str,',');
	cleanString(str);
	name= str;
	getline(s,this->str);
}
void SUB::cleanString(string line){
	line.erase(remove(line.begin(),line.end(), '\t'),line.end()); // removing tabs
	line.erase(remove(line.begin(),line.end(), '\n'),line.end()); // removing new line token
	line.erase(remove(line.begin(),line.end(), '\r'),line.end()); // removing new line token
	line.erase(remove(line.begin(),line.end(), ' '),line.end()); // removing spaces
}
Expression* SUB::clone(stringstream & s,TCPSocket* p_tcpSock){
	SUB *sub = new SUB();
	sub->initialize(s,p_tcpSock);
	return sub;
}


void SUB::execute(Storage* s, Parse* p){
	stringstream ss(this->str);
	this->result=0;
	count = 0;
	if(getTarget(this->name, s)){
		//If true, Real
		while(getline(ss, str, ',')){
			cout<<"while"<<endl;
			if(this->count==2){
				Logger::printToError("From SUB: SUB takes no more than 2 parameters.",tcpSock);
				return;
			}
			if(s->findVariable(this->str)){	//checks to see if
											//variable exists
			if(s->getVariableType(this->str)=="REAL"){
					this->tmp=s->getRealData(this->str);	//if Real get real data
				}else{
					this->tmp=s->getNumericData(this->str);
				}
			}else{
				this->tmp = strtof(str.c_str(),NULL);
			}


		if(count==0){			//To avoid 0-tmp
			result = tmp;
		}else{		
			result= result - tmp;
			cout<<result;
		}
			count++;	//Increment counter
		}
	}else{
		//else Numeric
		while(getline(ss,this->str,',')){
			if(this->count==2){
				Logger::printToError("From SUB: SUB takes no more than 2 parameters.",tcpSock);
				return;
			}
			if(s->findVariable(this->str)){
				if(s->getVariableType(this->str)=="REAL"){
					Logger::printToError("From SUB: Incompatible Type.",tcpSock);
					return;
				}else{
					this->tmp=s->getNumericData(this->str);
				}
			}else{
				this->tmp = strtof(this->str.c_str(),NULL);
			}
		if(count==0){			//To avoid 0-tmp
			result = tmp;
		}else{		
			result= result - tmp;
			cout<<result;
		}
			count++;	//Increment counter
		}

	}

	if(s->findVariable(this->name)){
		if(s->getVariableType(this->name)=="NUMERIC"){
			s->setNumericData(this->name,this->result);
		}else if(s->getVariableType(this->name)=="REAL"){
			s->setRealData(this->name,this->result);
		}
	}
}

bool SUB::getTarget(string name, Storage* s){
	if(s->getVariableType(name)=="REAL"){return true;}
	else if(s->getVariableType(name)=="NUMERIC"){return false;}
	else{Logger::printToError("From ADD: Incompatible type.",tcpSock); return 0;}
}
SUB::~SUB(){}
