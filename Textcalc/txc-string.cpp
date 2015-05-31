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

txc::string::string() {
	exp = std::string();
}

txc::string::~string() {
}

std::string txc::string::getExp() {
	return exp;
}

void txc::string::setExp(std::string string) {
	exp = string;
}

void txc::string::setFromInput() {
	
	char *input = new char;
	
	scanf("%[^\n]%*c", input);
	setExp(std::string(input));
	delete input;
}

void txc::string::checkBrackets() {
	
	long j = 0;
	
	for (long i = 0; i < exp.length(); i++) {
		if (exp[i] == '(') j++;
		else if (exp[i] == ')') j--;
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

void txc::string::checkSpaces() {
	for (long i = 0; i < exp.length(); i++) {
		if (exp[i] == ' ') {
			std::cout << "Spaces aren't allowed!" << "\n";
			exit(1);
		}
	}
}

auto malformed = [] (long place) {
	std::cout << "The expression is malformed at character " << place << "\n";
	exit(1);
};

void txc::string::checkForm() {
	for (long i = 0; i < exp.length()-1; i++) {
		if (strchr(MSOPERATORS, exp[i]) != 0) {
			if (strchr(AFTSOPS, exp[i+1]) != 0) continue;
			else malformed(i + 1);
		} else if (exp[i] == '!') {
			if (strchr(AFTFACT, exp[i+1]) != 0 || exp[i+1] == '\0') continue;
			else malformed(i + 1);
		} else if (exp[i] == '(') {
			if (strchr(CNUMBERS, exp[i+1]) != 0 || exp[i+1] == '(' || exp[i+1] == '-' || strchr(TRIG, exp[i+1]) != 0) continue;
			else malformed(i + 1);
		} else if (exp[i] == ')') {
			if (strchr(OPERATORS, exp[i+1]) != 0 || exp[i+1] == '\0' || exp[i+1] == ')') continue;
			else malformed(i + 1);
		} else if (strchr(CNUMBERS, exp[i]) != 0) {
			if (strchr(AFTERNUM, exp[i+1]) != 0) continue;
			else malformed(i + 1);
		} else if (exp[i] == '-') {
			if (strchr(AFTMINUS, exp[i+1]) != 0) {
				if (exp[i+1] == '-' && exp[i+2] == '-') malformed(i + 1);
				else continue;
			} else malformed(i + 1);
		} else if (strchr(TRIG, exp[i]) != 0) {
			if (strchr(AFTTRIG, exp[i+1]) != 0) continue;
			else malformed(i + 1);
		}
		if (strchr(ACCEPTED, exp[i]) == 0) malformed(i + 1);
	}
	if (exp.at(exp.length()-1) != ')' && strchr(CNUMBERS, exp.at(exp.length()-1)) == 0 && exp.at(exp.length()-1) != '!') malformed(exp.length());
}

void txc::string::xCheckForm() {
	for (long i = 0; i < exp.length()-1; i++) {
		if (strchr(MSOPERATORS, exp[i]) != 0) {
			if (strchr(XAFTSOPS, exp[i+1]) != 0) continue;
			else malformed(i + 1);
		} else if (exp[i] == '!') {
			if (strchr(AFTFACT, exp[i+1]) != 0 || exp[i+1] == '\0') continue;
			else malformed(i + 1);
		} else if (exp[i] == '(') {
			if (strchr(XCNUMBERS, exp[i+1]) != 0 || exp[i+1] == '(' || exp[i+1] == '-' || strchr(TRIG, exp[i+1]) != 0) continue;
			else malformed(i + 1);
		} else if (exp[i] == ')') {
			if (strchr(OPERATORS, exp[i+1]) != 0 || exp[i+1] == '\0' || exp[i+1] == ')') continue;
			else malformed(i + 1);
		} else if (strchr(CNUMBERS, exp[i]) != 0) {
			if (strchr(AFTERNUM, exp[i+1]) != 0) continue;
			else malformed(i + 1);
		} else if (exp[i] == '-') {
			if (strchr(XAFTMINUS, exp[i+1]) != 0) {
				if (exp[i+1] == '-' && exp[i+2] == '-') malformed(i + 1);
				else continue;
			} else malformed(i + 1);
		} else if (exp[i] == 'x') {
			if (strchr(AFTX, exp[i+1]) != 0) continue;
			else malformed(i + 1);
		} else if (strchr(TRIG, exp[i]) != 0) {
			if(strchr(XAFTTRIG, exp[i+1]) != 0) continue;
			else malformed(i + 1);
		}
		if (strchr(XACCEPTED, exp[i]) ==0) malformed(i + 1);
	}
	if (exp.at(exp.length()-1) != ')' && strchr(XCNUMBERS, exp.at(exp.length()-1)) == 0 && exp.at(exp.length()-1) != '!') malformed(exp.length());
}

void txc::string::solveEquation(double one, double two, const long passages) {
	
	txc::string equation;
	txc::vector e_vector;
	double solutionOne;
	double solutionTwo;
	double solutionThree;
	double three;
	txc::string newEquation;
	constexpr float precision = 1 / 10000;

	std::cout << "Equations are solved with the bisection method" << "\n";
	std::cout << "Please type in your equation, without spaces" << "\n";
	equation.setFromInput();
	equation.checkSpaces();
	equation.checkBrackets();
	equation.xCheckForm();
	setExp(equation.getExp());
	e_vector.populate(equation);
	e_vector.replaceX(one);
	solutionOne = e_vector.solveAll();
	if (fabs(solutionOne) < precision && isfinite(solutionOne) != 0) {
		std::cout << "The approximate solution is x=" << one << "\n";
		exit(0);
	}
	newEquation.setExp(std::string(exp));
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
			newEquation.setExp(std::string(exp));
			e_vector.populate(newEquation);
			one = txc::random(i);
			e_vector.replaceX(one);
			solutionOne = e_vector.solveAll();
			if (fabs(solutionOne) < precision && isfinite(solutionOne) != 0) {
				std::cout << "\r" << "The approximate solution is x=" << one << "\n";
				exit(0);
			}
			newEquation.setExp(std::string(exp));
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
	newEquation.setExp(std::string(exp));
	e_vector.populate(newEquation);
	e_vector.replaceX(three);
	solutionThree = e_vector.solveAll();
	if (fabs(solutionThree) < precision && isfinite(solutionThree) != 0) {
		std::cout << "\r" << "The approximate solution is x=" << three << "\n";
		exit(0);
	}
	for (int i = 0; i < passages; i++) {
		three = (one + two) / 2;
		newEquation.setExp(std::string(exp));
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