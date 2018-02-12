//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Implementation file for Storage
// manages all data for the MIS


#include "storage.h"

//Constructors and Destructors
// constructor
Storage::Storage(TCPSocket* p_tcpSock){
	df = new DataFactory();
	tcpSock = p_tcpSock; // won't be deleted?
}
	
// destructor
Storage::~Storage(){
	for(map<string,DataType*>::iterator it = variable.begin(); it != variable.end(); it++){
		delete it->second; // frees pointers
	}
	delete df; // deletes the data factory
}

// label instructions
// insertLabel(string,int)
// inserts a label at the index
void Storage::insertLabel(string name, int index){
	if(label.count(name)){
		tcpSock->writeToSocket("ERROR LABEL: label already exists\n", strlen("ERROR LABEL: label already exists\n"));
	}else{	
		if(name.empty()){
			tcpSock->writeToSocket("ERROR LABEL: no name provided\n", strlen("ERROR LABEL: no name provided\n"));
			return;
		}
		int c = count(name.begin(),name.end(),','); // count commas
		int t = count(name.begin(),name.end(),'\\'); // count tokens
		if(c == 0 && t == 0){
			label[name] = index;
		}
		else{
			tcpSock->writeToSocket("ERROR LABEL: too many parameters (expected 1)\n",strlen("ERROR LABEL: too many parameters (expected 1)\n"));
		}
	}
}


// getIndexOf(string)
// returns the index of label name
// this assumes that findLabel was run already if JMPing
int Storage::getIndexOf(string name){
	return label[name];
}

// findLabel(string)
// checks if a label exists
bool Storage::findLabel(string name){
	if(label.count(name)){
		return true;
	}
	tcpSock->writeToSocket("ERROR Storage: label not found\n", strlen("ERROR Storage: label not found\n"));
	return false;
}


// createDataObject(string, string)
// creates a variable with proper syntax
void Storage::createDataObject(string name, string data){
	if(name[0] != '$'){ // check for $
		tcpSock->writeToSocket("ERROR Storage: not a valid variable name\n", strlen("ERROR Storage: not a valid variable name\n"));
		return;
	}
	DataType *nd = df->getObject(data,tcpSock); // create object
	if (nd != NULL){ // if created
		variable[name] = nd;
		return;
	}
	tcpSock->writeToSocket("ERROR Storage: invalid value, variable not stored\n", strlen("ERROR Storage: invalid value, variable not stored\n")); // failed because of invalid value
}

// findVariable(string)
// returns whether or not a variable exists
bool Storage::findVariable(string name){
	if(variable.count(name)){
		return true;
	}
	// not needed for a simple check?
	//Logger::printToError("From Storage: variable " + name + " not found");
	return false;
}

// getVariableType(string)
// retrieves the type of  the variable
string Storage::getVariableType(string name){
	DataType* d = variable[name];
	if(d != NULL){
		return d->getType();
	}
	else{
		tcpSock->writeToSocket("ERROR Storage: variable not found\n", strlen("ERROR Storage: variable not found\n"));
		return "UNDEFINED";
	}
}

// printStorageVariables
// prints the names of all variables in storage
void Storage::printStorageVariables(){
	for(map<string, DataType*>::iterator it = variable.begin(); it != variable.end(); ++it){
		cout << it->first  << "\n";
	}
}
	
// Type specific operations
// NUMERIC operations

// getNumericData(string name)
// gets long long from storage of variable
long long Storage::getNumericData(string name){
	DataType* d = variable[name];
	

	if(d != NULL){
		// checking for type
		if(d->getType() != "NUMERIC"){
			tcpSock->writeToSocket("ERROR Storage: variable is not of type NUMERIC\n", strlen("ERROR Storage: variable is not of type NUMERIC\n"));
			return 0; // returning something
		}
		return ((MISNumeric*)d)->getValue();
	}
	
	else{
		tcpSock->writeToSocket("ERROR Storage: NUMERIC variable does not exist\n", strlen("ERROR Storage: NUMERIC variable does not exist\n"));
	}
	
	return 0; // returning something for compiler warning
}
	
// setNumericDataa(string, long long)
// sets variable name's data to new value	
void Storage::setNumericData(string name, long long value){
	DataType* d = variable[name];

	if(d != NULL){		
		if(d->getType() != "NUMERIC"){ // check type
			tcpSock->writeToSocket("ERROR Storage: variable is not of type NUMERIC\n", strlen("ERROR Storage: variable is not of type NUMERIC\n"));
			return;
		}
		((MISNumeric*)d)->setValue(value);
	}
	else{
		tcpSock->writeToSocket("ERROR Storage: NUMERIC variable does not exist\n", strlen("ERROR Storage: NUMERIC variable does not exist\n"));
	}

}
	
// REAL operations
double Storage::getRealData(string name){
	DataType* d = variable[name];
	if(d != NULL){
		if(d->getType() != "REAL"){
			tcpSock->writeToSocket("ERROR Storage: variable is not of type REAL\n", strlen("ERROR Storage: variable is not of type REAL\n"));
			return -1; // return something to survive
		}
		return ((MISReal*)d)->getValue();
	}
	else{
		tcpSock->writeToSocket("ERROR Storage: REAL variable does not exist\n", strlen("ERROR Storage: REAL variable does not exist\n"));
	}
	return -1; // return something because of compiler warnings
}

void Storage::setRealData(string name, double value){
	DataType* d = variable[name];
	if(d != NULL){
		if(d->getType() != "REAL"){
			tcpSock->writeToSocket("ERROR Storage: variable is not of type REAL\n", strlen("ERROR Storage: variable is not of type REAL\n"));
			return;
		}
		((MISReal*)d)->setValue(value);
	}
	else{
		tcpSock->writeToSocket("ERROR Storage: REAL variable does not exist\n", strlen("ERROR Storage: REAL variable does not exist\n"));
	}
	return; // compiler warning if not here
}

// CHAR operations
char Storage::getCharData(string name){
	DataType* d = variable[name];
	if(d != NULL){
		if(d->getType() != "CHAR"){
			tcpSock->writeToSocket("ERROR Storage: variable is not of type CHAR\n", strlen("ERROR Storage: variable is not of type CHAR\n"));
			return '\n';
		}
		return ((MISChar*)d)->getValue();
	}
	else{
		tcpSock->writeToSocket("ERROR Storage: CHAR variable does not exist\n", strlen("ERROR Storage: CHAR variable does not exist\n"));
	}
	return '\n'; // return something because of compiler warnings
}

void Storage::setCharData(string name, char value){
	DataType* d = variable[name];
	if(d != NULL){
		if(d->getType() != "CHAR"){
			tcpSock->writeToSocket("ERROR Storage: variable is not of type CHAR\n", strlen("ERROR Storage: variable is not of type CHAR\n"));
			return;
		}
		((MISChar*)d)->setValue(value);
	}
	else{
		tcpSock->writeToSocket("ERROR Storage: CHAR variable does not exist\n", strlen("ERROR Storage: CHAR variable does not exist\n"));
	}
}

// STRING operations
string Storage::getStringData(string name){
	DataType* d = variable[name];
	if(d != NULL){
		if(d->getType() != "STRING"){
			tcpSock->writeToSocket("ERROR Storage: variable is not of type STRING\n", strlen("ERROR Storage: variable is not of type STRING\n"));
			return "UNDEFINED";
		}
		return ((MISString*)d)->getValue(); // exists
	}
	else{ // does not exist
		tcpSock->writeToSocket("ERROR Storage: STRING variable does not exist\n", strlen("ERROR Storage: STRING variable does not exist\n"));
	}
	return "UNDEFINED"; // return something
}

int Storage::getStringLength(string name){
	DataType* d = variable[name];
	if(d != NULL){
		if(d->getType() != "STRING"){
			tcpSock->writeToSocket("ERROR Storage: variable is not of type STRING\n", strlen("ERROR Storage: variable is not of type STRING\n"));
			return 0;
		}
		return ((MISString*)d)->getLength();
	}
	else{
		tcpSock->writeToSocket("ERROR Storage: STRING variable does not exist\n", strlen("ERROR Storage: STRING variable does not exist\n"));
	}
	return 0;
}

// setStringData
void Storage::setStringData(string name, string data){
	DataType* d = variable[name];
	if(d != NULL){
		if(d->getType() != "STRING"){
			tcpSock->writeToSocket("ERROR Storage: variable is not of type STRING\n", strlen("ERROR Storage: variable is not of type STRING\n"));
			return;
		}
		((MISString*)d)->setValue(data);
	}
	else{
		tcpSock->writeToSocket("ERROR Storage: STRING variable does not exist\n", strlen("ERROR Storage: STRING variable does not exist\n"));
	}
	return;
}
