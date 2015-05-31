//
//  definitions.h
//  Textcalc
//
//  Copyright (c) 2014 Clair Marchesani. All rights reserved.
//

#ifndef Textcalc_definitions_h
#define Textcalc_definitions_h

const char MOPERATORS[] = "+*/^%r!";									// Right-side operators without minus
const char MSOPERATORS[] = "+*/^%r";									// Right-side, two arguments operators without minus
const char SOPERATORS[] = "+*-/^%r";									// Right-side, two arguments operators
const char OPERATORS[] = "+*-/^%r!";										// All right-side operators
const char NUMBERS[] = "0123456789";
const char CNUMBERS[] = "0123456789pe";							// Numbers with constants
const char XNUMBERS[] = "0123456789x";								// Numbers with x
const char XCNUMBERS[] = "0123456789xpe";						// Numbers with constants and x
const char AFTSOPS[] = "0123456789(-pesct";							// Can come after a right-side, two-arguments operator
const char XAFTSOPS[] = "0123456789(-x.pesct";						// Can come after a right-side, two-arguments operator in an equation
const char AFTFACT[] = "+*-/^%r!)";											// Can come after a factorial
const char AFTERNUM[] = "+*-/^%r!)0123456789.";					// Can come after a number
const char AFTMINUS[] = "0123456789(-.pesct";						// Can come after a minus
const char XAFTMINUS[] = "0123456789(-x.pesct";					// Can come after a minus in an equation
const char ACCEPTED[] = "+*-/^%r!()0123456789.pesct";		// Accepted characters (in an expression)
const char XACCEPTED[] = "+*-/^%r!()0123456789.xpesct";	// Accepted characters (in an equation)
const char ORDEROFOPS[] = "!sct%^r/*-+";								// Order of operators
const char AFTX[] = "+*-/^%r!)";												// Can come after x
const char NUMBERSWITHPOINT[] = "0123456789.";
const char TRIG[] = "sct";															// Trigonometric operators
const char AFTTRIG[] = "0123456789-pe";								// Can come after a trigonometric operator
const char XAFTTRIG[] = "0123456789-xpe"	;							// Can come after a trigonometric operator in an equation

#endif