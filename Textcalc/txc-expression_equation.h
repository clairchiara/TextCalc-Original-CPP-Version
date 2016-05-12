//
//  txc-expression_equation.h
//  Textcalc
//
//  Created by Clair Marchesani on 12/05/2016.
//  Copyright © 2016 Clair Marchesani. All rights reserved.
//

#ifndef txc_expression_equation_h
#define txc_expression_equation_h

#include "txc-string.h"

constexpr char MOPERATORS[] = "+*/^%r!";									// Right-side operators without minus
constexpr char MSOPERATORS[] = "+*/^%r";									// Right-side, two arguments operators without minus
constexpr char SOPERATORS[] = "+*-/^%r";									// Right-side, two arguments operators
constexpr char OPERATORS[] = "+*-/^%r!";									// All right-side operators
constexpr char NUMBERS[] = "0123456789";
constexpr char CNUMBERS[] = "0123456789pe";									// Numbers with constants
constexpr char XNUMBERS[] = "0123456789x";									// Numbers with x
constexpr char XCNUMBERS[] = "0123456789xpe";								// Numbers with constants and x
constexpr char AFTSOPS[] = "0123456789(-pesct";								// Can come after a right-side, two-arguments operator
constexpr char XAFTSOPS[] = "0123456789(-x.pesct";							// Can come after a right-side, two-arguments operator in an equation
constexpr char AFTFACT[] = "+*-/^%r!)";										// Can come after a factorial
constexpr char AFTERNUM[] = "+*-/^%r!)0123456789.";							// Can come after a number
constexpr char AFTMINUS[] = "0123456789(-.pesct";							// Can come after a minus
constexpr char XAFTMINUS[] = "0123456789(-x.pesct";							// Can come after a minus in an equation
constexpr char ACCEPTED[] = "+*-/^%r!()0123456789.pesct";					// Accepted characters (in an expression)
constexpr char XACCEPTED[] = "+*-/^%r!()0123456789.xpesct";					// Accepted characters (in an equation)
constexpr char ORDEROFOPS[] = "!sct%^r/*-+";								// Order of operators
constexpr char AFTX[] = "+*-/^%r!)";										// Can come after x
constexpr char NUMBERSWITHPOINT[] = "0123456789.";
constexpr char TRIG[] = "sct";												// Trigonometric operators
constexpr char AFTTRIG[] = "0123456789-pe";									// Can come after a trigonometric operator
constexpr char XAFTTRIG[] = "0123456789-xpe"	;							// Can come after a trigonometric operator in an equation

namespace txc {
	
	class expression {
		std::vector<txc::element> vec;
		void checkBrackets() const;							// Checks for bracket errors
		void checkSpaces() const;							// Checks that there are no spaces
		void checkForm() const;								// Checks well-formedness conditions
		void negatives();									// Turns "(char) -, (double) #" into "(double) -#"
		void replaceConst();								// Replaces constants (π and e)
		int countParentheses() const;						// Returns the number of parentheses
		void singleArgOp(const long&, const double&);		// Calculates operations with single arguments
		void doubleArgOp(const long&, const double&);		// Calculates operations with two arguments
		void trig(const long&, const double&);				// Calculate trigonometric functions
		void solveBrackets();								// Solves the last set of brackets
		double solveExpression();							// Solves a bracketless expression
	public:
		static double random(const int&);					// Generates a random number that tends to be larger for larger inputs
		static void loadbar(const long&, const long&);		// Generates the loading bar
		expression() = delete;
		expression(const char*) {};
		virtual void solve();								// Solves the expression
	};
	
	class equation : public expression {
		void replaceX(const double&);						// Replaces X with the value from input
		void checkForm() const;								// Checks well-formedness conditions
	public:
		void solve(double, double, const long&) override;	// Solves equation with 2 starting values and n passages
	};
}

#endif /* txc_expression_equation_h */
