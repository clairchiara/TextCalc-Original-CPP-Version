//
//  functions.cpp
//  Textcalc
//
//  Copyright (c) 2014 Clair Marchesani. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include "functions.h"

void txc::help(const char* argument) {
	std::cout << "Usage: " << argument << " [--help | -e | -q (-s # #) (-p #)]" << "\n\n"
		<< "-e" << "\t\t" << "expression solving mode" << "\n"
		<< "-q" << "\t\t" << "equation solving mode (default passages = 500,000" << "\n"
		<< "-s # #" << "\t\t" << "(After -q) custom starting values" << "\n"
		<< "-p #" << "\t\t" << "(After -q or -s) custom number of passages" << "\n"
		<< "-h" << "\t\t" << "help" << "\n\n"
		<< "Default mode requires a space between each number, operator and bracket." << "\n"
		<< "Expression and equation solving modes do not accept spaces" << "\n\n"
		<< "Operators:" << "\n"
		<< "# + #" << "\t" << "addition" << "\n" << "# - #" << "\t" << "subtraction" << "\n"
		<< "# * #" << "\t" << "multiplication" << "\n" << "# / #" << "\t" << "division" << "\n"
		<< "# ^ #" << "\t" << "power" << "\n"<< "# r #" << "\t" << "root" << "\n"
		<< "# % #" << "\t" << "remainder" << "\n" << "# !" << "\t" << "exponential" << "\n"
		<< "s #" << "\t" << "sin" << "\n" << "c #" << "\t" << "cos" << "\n" << "t #" << "\t" << "tan" << "\n";
}

bool txc::samesign(const double a, const double b) {
	return (a >= 0 && b >= 0)  || (a < 0 && b < 0);
}

double txc::random(const int m) {
	
	double a = rand() % 11;
	
	return (rand() % 2 == 0) ? a * ( 0.0012 * m * m) : -a * ( 0.0012 * m * m);
}

void txc::loadbar(const long x, const long n) {
	if (x != n && x % (n / 100 + 1) != 0 && x != 1) return;
	printf("\r");
	fflush(stdout);
	
	float ratio = (float) x / (float) n;
	int c = ratio * 20;
	
	std::cout << std::setw(3) << (int) (ratio * 100) << "% [";
	for (int x = 0; x < c; x++) std::cout << "=";
	for (int x = c; x < 20; x++) std::cout << " ";
	std::cout << "]";
}