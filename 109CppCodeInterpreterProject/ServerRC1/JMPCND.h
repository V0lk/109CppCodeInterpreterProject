#ifndef _JMPCND_
#define _JMPCND_

#include "expression.h"

class JMPCND: public Expression{
	private:
		string label;
		string param1;
		string param2;
	public:
		JMPCND();
		JMPCND(string, string, string);
		virtual Expression* clone(stringstream & ss);
		virtual void initialize(stringstream & ss);
		virtual ~JMPCND();
};

#endif