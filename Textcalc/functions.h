//
//  functions.h
//  Textcalc
//
//  Copyright (c) 2014 Clair Marchesani. All rights reserved.
//

#ifndef __Textcalc__functions__
#define __Textcalc__functions__

namespace txc {
	void help(const char *);					// Shows the help
	bool samesign(double, double);		// Returns TRUE if same sign and FALSE if different sign
	double random(int);							// Generates a random number that tends to be larger for larger inputs
	void loadbar(long, long);					// Generates the loading bar
}

#endif /* defined(__Textcalc__functions__) */