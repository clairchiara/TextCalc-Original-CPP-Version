//
//  txc-string.h
//  Textcalc
//
//  Copyright (c) 2014 Clair Marchesani. All rights reserved.
//

#ifndef __Textcalc__txc_string__
#define __Textcalc__txc_string__

#include <iostream>
#include "functions.h"

namespace txc {
	
	class string {
	private:
		std::string exp;
	public:
		string();
		~string();
		std::string getExp();
		void setExp(std::string);
		void setFromInput();												// Sets from the console input
		void checkBrackets();												// Checks for bracket errors
		void checkSpaces();													// Checks that there are no spaces
		void checkForm();													// Checks other well-formedness conditions
		void xCheckForm();													// Checks well-formedness conditions
		void solveEquation(double, double, const long);	// Solves the equation with starting values and number of passages from the input
	};
	
}

#endif /* defined(__Textcalc__txc_string__) */