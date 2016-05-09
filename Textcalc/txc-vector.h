//
//  txc-vector.h
//  Textcalc
//
//  Copyright (c) 2014 Clair Marchesani. All rights reserved.
//

#ifndef __Textcalc__txc_vector__
#define __Textcalc__txc_vector__

#include <vector>
#include "txc-string.h"

namespace txc {
	
	struct element {
		double val;											// Contains numbers
		char notval;										// Contains operators
	public:
		element();
		element(const double&, const char&);
		double getVal() const;
		char getNotVal() const;
		void setVal(const double&);
		void setNotVal(const char&);
	};
	
	class vector : public std::vector<txc::element> {
	public:
		vector();
		vector(const std::vector<txc::element>&);
		void populate(txc::string);							// Populates the vector from a string
		void negatives();									// Turns "(char) -, (double) #" into "(double) -#"
		void replaceX(const double&);						// Replaces X with the value from input
		void replaceConst();								// Replaces constants (π and e)
		int countParentheses() const;						// Returns the number of parentheses
		void singleArgOp(const long&, const double&);		// Calculates operations with single arguments
		void doubleArgOp(const long&, const double&);		// Calculates operations with two arguments
		void trig(const long&, const double&);				// Calculate trigonometric functions
		void solveBrackets();								// Solves the last set of brackets
		double solveExpression();							// Solves a bracketless expression
		double solveAll();									// Solves an expression containing brackets
	};
	
}

#endif /* defined(__Textcalc__txc_vector__) */