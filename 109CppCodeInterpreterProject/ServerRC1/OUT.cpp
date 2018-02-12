//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Implementation file for OUT
// Prints variables and constants

#include "OUT.h"

OUT::OUT():OUT("undefined",NULL){}

OUT::OUT(string d,TCPSocket* p_tcpSock){
	data = d;
	tcpSock = p_tcpSock;
}

OUT::~OUT(){}

//Public Functions

// clone()
// clones object
Expression* OUT::clone(stringstream & ss,TCPSocket* p_tcpSock){
	OUT* outer = new OUT();
	outer->initialize(ss,p_tcpSock);
	return outer;
}

void OUT::initialize(stringstream & ss,TCPSocket* p_tcpSock){
	tcpSock = p_tcpSock;
	string str = "";
	getline(ss,str); // get the data
	data = str;
}

//execute()
// OUT's logic execution
void OUT::execute(Storage* s, Parse* p){
	string str = "";
	stringstream ss(data);
	int count = 0;
	string type;
	
	while(count < 12)  // while there are still strings and not up to the maximum output
	{
		//get line
		if(ss.peek() =='"'){
			ss.get();
			getline(ss,str,'"');
			ss.get();
		}
		else getline(ss,str,',');
		
		
		if(str.front() == '$'){// check for $, is a variable
			if(s->findVariable(str) == false){
				Logger::printToError("From OUT: " + str + " is not found",tcpSock);
			}
			else{
				type = s->getVariableType(str);
				if(type == "STRING"){
					if(s->getStringData(str).find("\\") != string::npos){
						stringstream sss(s->getStringData(str));
						string op;
						bool notfirst = false;
						while(getline(sss, op, '\\')){
							if(notfirst){
								if(op.front() == 'n')
									Logger::printToOutput("\n",tcpSock);
								else if(op.front() == 't')
									Logger::printToOutput("\t",tcpSock);
								else if(op.front() == 'r')
									Logger::printToOutput("\r",tcpSock);
								op.erase(0,1);
							}
							Logger::printToOutput(op,tcpSock);
							notfirst = true;
						}
					}
					else
						Logger::printToOutput(s->getStringData(str),tcpSock);
				}
				else if(type == "REAL"){
					Logger::printToOutput(to_string(s->getRealData(str)),tcpSock);
				}
				else if( type == "NUMERIC"){
					Logger::printToOutput(to_string(s->getNumericData(str)),tcpSock);
				}
				else if(type == "CHAR"){
					string c = " ";
					c[0] = s->getCharData(str);
					Logger::printToOutput(c,tcpSock);
				}
				else{
					Logger::printToError("From OUT: type not found",tcpSock);
				}
			}
		}	
		// else if(str.front() == '"'){ // check for string
		// // shed quotations
			// str.erase(0,1); // remove beginning quote
			// str.erase(str.size() - 1); // remove end quote
			// if(str.find("\\") != string::npos){
				// stringstream sss(str);
				// string op;
				// bool notfirst = false;
				// while(getline(sss, op, '\\')){
						// if(notfirst){
						// if(op.front() == 'n')
						// Logger::printToOutput("\n");
						// else if(op.front() == 't')
							// Logger::printToOutput("\t");
						// else if(op.front() == 'r')
							// Logger::printToOutput("\r");
						// op.erase(0,1);
					// }
					// Logger::printToOutput(op);
					// notfirst = true;
				// }
			// }
			// else Logger::printToOutput(str);
		// }
		else{
			if(str.find("\\") != string::npos){
				stringstream sss(str);
				string op;
				bool notfirst = false;
				while(getline(sss, op, '\\')){
						if(notfirst){
						if(op.front() == 'n')
						Logger::printToOutput("\n",tcpSock);
						else if(op.front() == 't')
							Logger::printToOutput("\t",tcpSock);
						else if(op.front() == 'r')
							Logger::printToOutput("\r",tcpSock);
						op.erase(0,1);
					}
					Logger::printToOutput(op,tcpSock);
					notfirst = true;
				}
			}
			else Logger::printToOutput(str,tcpSock);
		}
		count ++;
		//cout << ss.peek();
		if(ss.peek() == -1) break;
	}
	if(getline(ss,str,','))
		Logger::printToError("From OUT: too many parameters given, did not output past 12",tcpSock);
}
