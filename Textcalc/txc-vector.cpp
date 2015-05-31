//
//  txc-vector.cpp
//  Textcalc
//
//  Copyright (c) 2014 Clair Marchesani. All rights reserved.
//

#include <math.h>
#include "definitions.h"
#include "txc-vector.h"

txc::element::element() {
	val = NULL;
	notval = '\0';
}

txc::element::element(double a, char b) {
	val = a;
	notval = b;
}

txc::element::~element() {
}

double txc::element::getVal() {
	return val;
}

char txc::element::getNotVal() {
	return notval;
}

void txc::element::setVal(double number) {
	val = number;
}

void txc::element::setNotVal(char oper) {
	notval = oper;
}

txc::vector::vector() {
	exp = std::vector<txc::element>();
}

txc::vector::~vector() {
}

std::vector<txc::element>txc::vector::getExp() {
	return exp;
}

void txc::vector::setExp(std::vector<txc::element> input) {
	exp = input;
}

void txc::vector::populate(txc::string expression) {
	
	txc::element number;
	txc::element character;
	int remainingLength = (int)expression.getExp().length();
	
	exp.clear();
	while (remainingLength != 0) {
		if (strchr(NUMBERSWITHPOINT, expression.getExp()[0]) != 0) {
			number.val = atof(expression.getExp().c_str());
			long cut = expression.getExp().find_first_not_of(NUMBERSWITHPOINT);
			expression.setExp(expression.getExp().erase(0, cut));
			exp.push_back(number);
			remainingLength = (int)expression.getExp().length();
		} else {
			character.notval = expression.getExp()[0];
			exp.push_back(character);
			expression.setExp(expression.getExp().erase(0, 1));
			remainingLength--;
		}
	}
}

void txc::vector::negatives() {
	for (int i = 0; i <= exp.size()-1; i++) {
		if (exp[i].notval == '-') {
			if (i == 0) {
				
				txc::element n = {0 - exp[i+1].val, '\0'};
				
				exp.erase(exp.begin()+i+1);
				exp.insert(exp.begin()+i+1, n);
				exp.erase(exp.begin()+i);
			} else if (exp[i-1].notval != ')' && exp[i-1].notval != '!' && exp[i-1].notval != '\0') {
				
				txc::element n = {0 - exp[i+1].val, '\0'};
				
				exp.erase(exp.begin()+i+1);
				exp.insert(exp.begin()+i+1, n);
				exp.erase(exp.begin()+i);
			}
		}
	}
}

void txc::vector::replaceX(double value) {
	
	txc::element evalue = {value, '\0'};
	
	for (int i = 0; i <= exp.size()-1; i++) {
		if (exp[i].notval == 'x') {
			exp.erase(exp.begin()+i);
			exp.insert(exp.begin()+i, evalue);
		}
	}
}

void txc::vector::replaceConst() {
	
	txc::element pi = {M_PI, '\0'};
	txc::element e = {M_E, '\0'};
	
	for (int i = 0; i <= exp.size()-1; i++) {
		if (exp[i].notval == 'p') {
			exp.erase(exp.begin()+i);
			exp.insert(exp.begin()+i, pi);
		} else if (exp[i].notval == 'e') {
			exp.erase(exp.begin()+i);
			exp.insert(exp.begin()+i, e);
		}
	}
}

int txc::vector::countParentheses() {
	
	int parentheses = 0;
	
	for (long i = 0; i < exp.size(); i++) if (exp[i].notval == '(' || exp[i].notval == ')') parentheses++;
	return parentheses;
}

void txc::vector::singleArgOp(long i, double result) {
	
	txc::element eresult = {result, '\0'};
	
	exp.erase(exp.begin()+i-1);
	exp.insert(exp.begin()+i-1, eresult);
	exp.erase(exp.begin()+i);
}

void txc::vector::doubleArgOp(long i, double result) {
	
	txc::element eresult = {result, '\0'};
	
	exp.erase(exp.begin()+i-1);
	exp.insert(exp.begin()+i-1, eresult);
	exp.erase(exp.begin()+i);
	exp.erase(exp.begin()+i);
}

void txc::vector::trig(long i, double result) {
	
	txc::element eresult = {result, '\0'};
	
	exp.erase(exp.begin()+i);
	exp.erase(exp.begin()+i);
	exp.insert(exp.begin()+i, eresult);
}

void txc::vector::solveBrackets() {
	
	long i, j, k;
	
	for (i = exp.size()-1; i>=0; i--) {
		if (exp[i].notval == '(') {
			j = i;
			break;
		}
	}
	for (k = 0; k < 11; k++) {
		for (i = j; ; ) { // Breaks when it reaches a closing bracket
			if (exp[i].notval == ORDEROFOPS[k]) {
				switch (ORDEROFOPS[k]) {
					case '+':
						doubleArgOp(i, exp[i-1].val + exp[i+1].val);
						break;
					case '-':
						doubleArgOp(i, exp[i-1].val - exp[i+1].val);
						break;
					case '*':
						doubleArgOp(i, exp[i-1].val * exp[i+1].val);
						break;
					case '/':
						doubleArgOp(i, exp[i-1].val / exp[i+1].val);
						break;
					case '^':
						doubleArgOp(i, pow(exp[i-1].val, exp[i+1].val));
						break;
					case '%':
						doubleArgOp(i, remainder(exp[i-1].val, exp[i+1].val));
						break;
					case 'r':
						doubleArgOp(i, pow(exp[i-1].val, 1 / exp[i+1].val));
						break;
					case '!':
						singleArgOp(i, tgamma(exp[i-1].val + 1));
						break;
					case 's':
						trig(i, sin(exp[i+1].val));
						break;
					case 'c':
						trig(i, cos(exp[i+1].val));
						break;
					case 't':
						trig(i, tan(exp[i+1].val));
						break;
				}
				i--;
			} else if (exp[i].notval == ')') {
				i = j;
				break;
			} else i++;
		}
	}
	exp.erase(exp.begin()+i);
	exp.erase(exp.begin()+i+1);
}

double txc::vector::solveExpression() {
	for (long k = 0; k < 11; k++) {
		for (long i = 0; i <= exp.size()-1; i++) {
			if (exp[i].notval == ORDEROFOPS[k]) {
				switch (ORDEROFOPS[k]) {
					case '+':
						doubleArgOp(i, exp[i-1].val + exp[i+1].val);
						break;
					case '-':
						doubleArgOp(i, exp[i-1].val - exp[i+1].val);
						break;
					case '*':
						doubleArgOp(i, exp[i-1].val * exp[i+1].val);
						break;
					case '/':
						doubleArgOp(i, exp[i-1].val / exp[i+1].val);
						break;
					case '^':
						doubleArgOp(i, pow(exp[i-1].val, exp[i+1].val));
						break;
					case '%':
						doubleArgOp(i, remainder(exp[i-1].val, exp[i+1].val));
						break;
					case 'r':
						doubleArgOp(i, pow(exp[i-1].val, 1 / exp[i+1].val));
						break;
					case '!':
						singleArgOp(i, tgamma(exp[i-1].val + 1));
						break;
					case 's':
						trig(i, sin(exp[i+1].val));
						break;
					case 'c':
						trig(i, cos(exp[i+1].val));
						break;
					case 't':
						trig(i, tan(exp[i+1].val));
						break;
				}
				i--;
			}
		}
	}
	return exp[0].val;
}

double txc::vector::solveAll() {
	
	int parentheses = countParentheses();
	
	replaceConst();
	negatives();
	while (parentheses > 0) {
		solveBrackets();
		parentheses -= 2;
	}
	return solveExpression();
}