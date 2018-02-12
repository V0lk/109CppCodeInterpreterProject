//	Allakhverdiyev, Dmytro - dallakhv
//	Darling,Bailey - bdarling
//	Li, Wilbur - wiwili
//	CMPS109
//	MIS

// Header file for ExpressionFactory
// Inherits from Abstrct Factory
// Generates Expression objects

#ifndef _EXPRESSION_FACTORY_
#define _EXPRESSION_FACTORY_

#include "abstractFactory.h"
#include "expression.h"

using namespace std;

class ExpressionFactory : public AbstractFactory<Expression> {
	private:
		map<string,Expression*> objs; // map of Expression Objects
	public:
		ExpressionFactory(); // constructor that initializes all expressions
		Expression* getObject(string , TCPSocket*); // retrieves an expression from map, associates it with storage,parser, and socket, and returns a copy of it
		~ExpressionFactory(); // destructor
};

#endif
