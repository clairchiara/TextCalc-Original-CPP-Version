//
//  txc-string.h
//  Textcalc
//
//  Copyright (c) 2014 Clair Marchesani. All rights reserved.
//

#ifndef __Textcalc__txc_string__
#define __Textcalc__txc_string__

#include <iostream>
#include <string>
#include "functions.h"

namespace txc {
	
	class string : public std::string {
	public:
		string();
		string(const std::string&);
		string(const char*);
		static txc::string newFromInput();					// Creates a new string from console input
		void checkBrackets() const;							// Checks for bracket errors
		void checkSpaces() const;							// Checks that there are no spaces
		void checkForm() const;								// Checks other well-formedness conditions
		void xCheckForm() const;							// Checks well-formedness conditions
		void solveEquation(double, double, const long&);	// Solves the equation with starting values and number of passages from the input
	};
	
}

#endif /* defined(__Textcalc__txc_string__) */