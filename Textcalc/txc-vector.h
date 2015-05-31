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
	
	class vector;														// Forward declaration for friendship with txc::element
	
	class element {
		friend class txc::vector;
	private:
		double val;													// Contains numbers
		char notval;													// Contains operators
	public:
		element();
		element(double, char);
		~element();
		double getVal();
		char getNotVal();
		void setVal(double);
		void setNotVal(char);
	};
	
	class vector {
	private:
		std::vector<txc::element> exp;
	public:
		vector();
		~vector();
		std::vector<txc::element> getExp();
		void setExp(std::vector<txc::element>);
		void populate(txc::string);							// Populates the vector from a string
		void negatives();											// Turns "(char) -, (double) #" into "(double) -#"
		void replaceX(double);								// Replaces X with the value from input
		void replaceConst();										// Replaces constants (π and e)
		int countParentheses();								// Returns the number of parentheses
		void singleArgOp(long, double);					// Calculates operations with single arguments
		void doubleArgOp(long, double);				// Calculates operations with two arguments
		void trig(long, double);								// Calculate trigonometric functions
		void solveBrackets();									// Solves the last set of brackets
		double solveExpression();							// Solves a bracketless expression
		double solveAll();											// Solves an expression containing brackets
	};
	
}

#endif /* defined(__Textcalc__txc_vector__) */