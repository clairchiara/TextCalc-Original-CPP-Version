//
//  definitions.h
//  Textcalc
//
//  Copyright (c) 2014 Clair Marchesani. All rights reserved.
//

#ifndef Textcalc_definitions_h
#define Textcalc_definitions_h

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

#endif