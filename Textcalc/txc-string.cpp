//
//  txc-string.cpp
//  Textcalc
//
//  Copyright (c) 2014 Clair Marchesani. All rights reserved.
//

#include <iostream>
#include <math.h>
#include "definitions.h"
#include "txc-string.h"
#include "txc-vector.h"

txc::string::string() {}

txc::string::string(const std::string& s) : std::string(s) {}

txc::string::string(const char* c) : std::string(c) {}

txc::string txc::string::newFromInput() {
	char *input = new char;
	scanf("%[^\n]%*c", input);
	txc::string s(input);
	delete input;
	return s;
}

void txc::string::checkBrackets() const {
	
	long j = 0;
	
	for (long i = 0; i < length(); i++) {
		if (at(i) == '(') j++;
		else if (at(i) == ')') j--;
		if (j < 0) {
			std::cout << "Bad brackets!" << "\n";
			exit(1);
		}
	}
	if (j != 0) {
		std::cout << "Bad brackets!" << "\n";
		exit(1);
	}
}

void txc::string::checkSpaces() const {
	for (long i = 0; i < length(); i++) {
		if (at(i) == ' ') {
			std::cout << "Spaces aren't allowed!" << "\n";
			exit(1);
		}
	}
}

auto malformed = [] (long place) {
	std::cout << "The expression is malformed at character " << place << "\n";
	exit(1);
};

void txc::string::checkForm() const {
	for (long i = 0; i < length()-1; i++) {
		if (strchr(MSOPERATORS, at(i)) != 0) {
			if (strchr(AFTSOPS, at(i+1)) != 0) continue;
			else malformed(i + 1);
		} else if (at(i) == '!') {
			if (strchr(AFTFACT, at(i+1)) != 0 || at(i+1) == '\0') continue;
			else malformed(i + 1);
		} else if (at(i) == '(') {
			if (strchr(CNUMBERS, at(i+1)) != 0 || at(i+1) == '(' || at(i+1) == '-' || strchr(TRIG, at(i+1)) != 0) continue;
			else malformed(i + 1);
		} else if (at(i) == ')') {
			if (strchr(OPERATORS, at(i+1)) != 0 || at(i+1) == '\0' || at(i+1) == ')') continue;
			else malformed(i + 1);
		} else if (strchr(CNUMBERS, at(i)) != 0) {
			if (strchr(AFTERNUM, at(i+1)) != 0) continue;
			else malformed(i + 1);
		} else if (at(i) == '-') {
			if (strchr(AFTMINUS, at(i+1)) != 0) {
				if (at(i+1) == '-' && at(i+2) == '-') malformed(i + 1);
				else continue;
			} else malformed(i + 1);
		} else if (strchr(TRIG, at(i)) != 0) {
			if (strchr(AFTTRIG, at(i+1)) != 0) continue;
			else malformed(i + 1);
		}
		if (strchr(ACCEPTED, at(i)) == 0) malformed(i + 1);
	}
	if (at(length()-1) != ')' && strchr(CNUMBERS, at(length()-1)) == 0 && at(length()-1) != '!') malformed(length());
}

void txc::string::xCheckForm() const {
	for (long i = 0; i < length()-1; i++) {
		if (strchr(MSOPERATORS, at(i)) != 0) {
			if (strchr(XAFTSOPS, at(i+1)) != 0) continue;
			else malformed(i + 1);
		} else if (at(i) == '!') {
			if (strchr(AFTFACT, at(i+1)) != 0 || at(i+1) == '\0') continue;
			else malformed(i + 1);
		} else if (at(i) == '(') {
			if (strchr(XCNUMBERS, at(i+1)) != 0 || at(i+1) == '(' || at(i+1) == '-' || strchr(TRIG, at(i+1)) != 0) continue;
			else malformed(i + 1);
		} else if (at(i) == ')') {
			if (strchr(OPERATORS, at(i+1)) != 0 || at(i+1) == '\0' || at(i+1) == ')') continue;
			else malformed(i + 1);
		} else if (strchr(CNUMBERS, at(i)) != 0) {
			if (strchr(AFTERNUM, at(i+1)) != 0) continue;
			else malformed(i + 1);
		} else if (at(i) == '-') {
			if (strchr(XAFTMINUS, at(i+1)) != 0) {
				if (at(i+1) == '-' && at(i+2) == '-') malformed(i + 1);
				else continue;
			} else malformed(i + 1);
		} else if (at(i) == 'x') {
			if (strchr(AFTX, at(i+1)) != 0) continue;
			else malformed(i + 1);
		} else if (strchr(TRIG, at(i)) != 0) {
			if(strchr(XAFTTRIG, at(i+1)) != 0) continue;
			else malformed(i + 1);
		}
		if (strchr(XACCEPTED, at(i)) ==0) malformed(i + 1);
	}
	if (at(length()-1) != ')' && strchr(XCNUMBERS, at(length()-1)) == 0 && at(length()-1) != '!') malformed(length());
}

void txc::string::solveEquation(double one, double two, const long passages) {
	
	txc::string equation;
	txc::string exp;
	txc::vector e_vector;
	double solutionOne;
	double solutionTwo;
	double solutionThree;
	double three;
	txc::string newEquation;
	constexpr float precision = 1 / 10000;

	std::cout << "Equations are solved with the bisection method" << "\n";
	std::cout << "Please type in your equation, without spaces" << "\n";
	equation = txc::string::newFromInput();
	equation.checkSpaces();
	equation.checkBrackets();
	equation.xCheckForm();
	exp = equation;
	e_vector.populate(equation);
	e_vector.replaceX(one);
	solutionOne = e_vector.solveAll();
	if (fabs(solutionOne) < precision && isfinite(solutionOne) != 0) {
		std::cout << "The approximate solution is x=" << one << "\n";
		exit(0);
	}
	newEquation = exp;
	e_vector.populate(newEquation);
	e_vector.replaceX(two);
	solutionTwo = e_vector.solveAll();
	if (fabs(solutionTwo) < precision && isfinite(solutionTwo) != 0) {
		std::cout << "The approximate solution is x=" << two << "\n";
		exit(0);
	}
	if (txc::samesign(solutionOne, solutionTwo)) {
		
		int i =1;

		while (txc::samesign(solutionOne, solutionTwo)) {
			newEquation = exp;
			e_vector.populate(newEquation);
			one = txc::random(i);
			e_vector.replaceX(one);
			solutionOne = e_vector.solveAll();
			if (fabs(solutionOne) < precision && isfinite(solutionOne) != 0) {
				std::cout << "\r" << "The approximate solution is x=" << one << "\n";
				exit(0);
			}
			newEquation = exp;
			e_vector.populate(newEquation);
			two = txc::random(i);
			e_vector.replaceX(two);
			solutionTwo = e_vector.solveAll();
			if (fabs(solutionTwo) < precision && isfinite(solutionTwo) != 0) {
				std::cout << "\r" << "The approximate solution is x=" << two << "\n";
				exit(0);
			}
			txc::loadbar(i, passages);
			if (i > passages) {
				std::cout << "\r" << "Solution not found          \n";
				exit(0);
			}
			i++;
		}
	}
	three = (one + two) / 2;
	newEquation = exp;
	e_vector.populate(newEquation);
	e_vector.replaceX(three);
	solutionThree = e_vector.solveAll();
	if (fabs(solutionThree) < precision && isfinite(solutionThree) != 0) {
		std::cout << "\r" << "The approximate solution is x=" << three << "\n";
		exit(0);
	}
	for (int i = 0; i < passages; i++) {
		three = (one + two) / 2;
		newEquation = exp;
		e_vector.populate(newEquation);
		e_vector.replaceX(three);
		solutionThree = e_vector.solveAll();
		if (fabs(solutionThree) == 0 && isfinite(solutionThree) != 0) {
			std::cout << "\r" << "The approximate solution is x=" << three << "\n";
			exit(0);
		}
		txc::samesign(solutionTwo, solutionThree) ? two = three : one = three;
		txc::loadbar(i, passages);
	}
	if (isfinite(solutionThree) != 0 && fabs(solutionThree) < 0.1) {
		std::cout << "\r" << "After " << passages << " passages the closest solution is x=" << three << "\n";
	} else std::cout << "\r" << "Solution not found          \n";
	exit(0);
}