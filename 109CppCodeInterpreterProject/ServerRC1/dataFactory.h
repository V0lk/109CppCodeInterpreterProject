//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Header file for a factory that creates DataTypes

#ifndef _DATA_FACTORY_
#define _DATA_FACTORY_

#include "abstractFactory.h"
#include "dataType.h"
using namespace std;

class DataFactory : public AbstractFactory<DataType> {
	private:
		map<string,DataType*> objs; // map of DataType Objects
	public:
		DataFactory(); // constructor that initializes all DataTypes
		DataType* getObject(string,TCPSocket*); // retrieves a DataType object from map
		~DataFactory(); // destructor
};

#endif
