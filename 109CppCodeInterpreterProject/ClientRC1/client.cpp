//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS Phase 2

// Client file for MIS client/server
// Handles accepting files, sending file over via TCP, and returning outputs

#include "common.h"
#include "TCPSocket.h"

// declarations
void outputToFile(char*,string);

// main body
int main(int argc, char *argv[]){
	if(argc != 4){
		std::cout<< "usage: " << argv[0] << " <server IP address> <server port> <filename>.mis \n";
		return 0;
	}
	
	// checking argument extension
	string fileext(argv[3]);
	string last = fileext.substr(fileext.length() - 4);
	if (last != ".mis"){
		std::cout<< "usage: " << argv[0] << " <server IP address> <server port> <filename>.mis \n";
		exit(1);
	}

	// getting file name
	string fullname(argv[3]);
	size_t lastindex = fullname.find_last_of(".");
	string filename = fullname.substr(0,lastindex);
	
	// delete old files, if any
	ofstream fileOUT(filename + ".out", ofstream::trunc); // open in truncate mode to delete
	fileOUT.close(); // close it
	ofstream fileERR(filename + ".err", ofstream::trunc); 
	fileERR.close();
	
	int port = atoi(argv[2]);
	TCPSocket* sock = new TCPSocket(argv[1],port);
	
	FILE* f = fopen(argv[3],"r");
	if (f!=NULL){
		fseek(f,0,2);
		long fsize=ftell(f);
		char * buffer = (char*)calloc(fsize+1,sizeof(char));
		fseek(f,0,0);
		fread(buffer,1,fsize,f);
		sock->writeToSocket(buffer,fsize);
		free(buffer);
		fclose(f);
	}
	else{
		perror("Error w/ file\n");
	}
	
	for(;;){
		char* buffer = (char*)calloc(1024,sizeof(char));
		int return_byte = sock->readFromSocketWithTimeout(buffer,1023, 60,0);
		if(return_byte == 0){
			free(buffer);
			break;
		}
		cout << buffer;
		outputToFile(buffer, filename);
		free(buffer);
	}
	
	delete sock;
}


// functions

// outputToFile()
// takes a buffer, converts it to a string, and outputs it to the proper channel
void outputToFile(char* buffer, string filename){
	string message(buffer); // since char* has a null terminator
	stringstream ss(message); // load into a buffer
	getline(ss,message,' '); // get what type of message it is
	if(message == "ERROR"){ // if it is an error, print to error file
		ofstream fileERR(filename + ".err", ios::app);
		getline(ss,message,'\0'); // up to null terminator
		fileERR << message;
		fileERR.close();
	}
	else{ // other option is output, print to output
		ofstream fileOUT(filename + ".out", ios::app);
		getline(ss,message,'\0'); // up to null terminator
		fileOUT << message;
		fileOUT.close();
	}
}
	
