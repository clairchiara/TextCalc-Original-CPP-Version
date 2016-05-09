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

txc::element::element(const double& a, const char& b) : val(a), notval(b) {}

double txc::element::getVal() const {
	return val;
}

char txc::element::getNotVal() const {
	return notval;
}

void txc::element::setVal(const double& number) {
	val = number;
}

void txc::element::setNotVal(const char& oper) {
	notval = oper;
}

txc::vector::vector() {}

txc::vector::vector(const std::vector<txc::element>& v) : std::vector<txc::element>(v) {}

void txc::vector::populate(txc::string expression) {
	
	txc::element number;
	txc::element character;
	int remainingLength = (int)expression.length();
	
	clear();
	while (remainingLength != 0) {
		if (strchr(NUMBERSWITHPOINT, expression[0]) != 0) {
			number.val = atof(expression.c_str());
			long cut = expression.find_first_not_of(NUMBERSWITHPOINT);
			expression.erase(0, cut);
			push_back(number);
			remainingLength = (int)expression.length();
		} else {
			character.notval = expression[0];
			push_back(character);
			expression.erase(0, 1);
			remainingLength--;
		}
	}
}

void txc::vector::negatives() {
	for (int i = 0; i <= size()-1; i++) {
		if (at(i).notval == '-') {
			if (i == 0) {
				
				txc::element n = {0 - at(i+1).val, '\0'};
				
				erase(begin()+i+1);
				insert(begin()+i+1, n);
				erase(begin()+i);
			} else if (at(i-1).notval != ')' && at(i-1).notval != '!' && at(i-1).notval != '\0') {
				
				txc::element n = {0 - at(i+1).val, '\0'};
				
				erase(begin()+i+1);
				insert(begin()+i+1, n);
				erase(begin()+i);
			}
		}
	}
}

void txc::vector::replaceX(const double& value) {
	
	txc::element evalue = {value, '\0'};
	
	for (int i = 0; i <= size()-1; i++) {
		if (at(i).notval == 'x') {
			erase(begin()+i);
			insert(begin()+i, evalue);
		}
	}
}

void txc::vector::replaceConst() {
	
	txc::element pi = {M_PI, '\0'};
	txc::element e = {M_E, '\0'};
	
	for (int i = 0; i <= size()-1; i++) {
		if (at(i).notval == 'p') {
			erase(begin()+i);
			insert(begin()+i, pi);
		} else if (at(i).notval == 'e') {
			erase(begin()+i);
			insert(begin()+i, e);
		}
	}
}

int txc::vector::countParentheses() const {
	
	int parentheses = 0;
	
	for (long i = 0; i < size(); i++) if (at(i).notval == '(' || at(i).notval == ')') parentheses++;
	return parentheses;
}

void txc::vector::singleArgOp(const long& i, const double& result) {
	
	txc::element eresult = {result, '\0'};
	
	erase(begin()+i-1);
	insert(begin()+i-1, eresult);
	erase(begin()+i);
}

void txc::vector::doubleArgOp(const long& i, const double& result) {
	
	txc::element eresult = {result, '\0'};
	
	erase(begin()+i-1);
	insert(begin()+i-1, eresult);
	erase(begin()+i);
	erase(begin()+i);
}

void txc::vector::trig(const long& i, const double& result) {
	
	txc::element eresult = {result, '\0'};
	
	erase(begin()+i);
	erase(begin()+i);
	insert(begin()+i, eresult);
}

void txc::vector::solveBrackets() {
	
	long i, j, k;
	
	for (i = size()-1; i>=0; i--) {
		if (at(i).notval == '(') {
			j = i;
			break;
		}
	}
	for (k = 0; k < 11; k++) {
		for (i = j; ; ) { // Breaks when it reaches a closing bracket
			if (at(i).notval == ORDEROFOPS[k]) {
				switch (ORDEROFOPS[k]) {
					case '+':
						doubleArgOp(i, at(i-1).val + at(i+1).val);
						break;
					case '-':
						doubleArgOp(i, at(i-1).val - at(i+1).val);
						break;
					case '*':
						doubleArgOp(i, at(i-1).val * at(i+1).val);
						break;
					case '/':
						doubleArgOp(i, at(i-1).val / at(i+1).val);
						break;
					case '^':
						doubleArgOp(i, pow(at(i-1).val, at(i+1).val));
						break;
					case '%':
						doubleArgOp(i, remainder(at(i-1).val, at(i+1).val));
						break;
					case 'r':
						doubleArgOp(i, pow(at(i-1).val, 1 / at(i+1).val));
						break;
					case '!':
						singleArgOp(i, tgamma(at(i-1).val + 1));
						break;
					case 's':
						trig(i, sin(at(i+1).val));
						break;
					case 'c':
						trig(i, cos(at(i+1).val));
						break;
					case 't':
						trig(i, tan(at(i+1).val));
						break;
				}
				i--;
			} else if (at(i).notval == ')') {
				i = j;
				break;
			} else i++;
		}
	}
	erase(begin()+i);
	erase(begin()+i+1);
}

double txc::vector::solveExpression() {
	for (long k = 0; k < 11; k++) {
		for (long i = 0; i <= size()-1; i++) {
			if (at(i).notval == ORDEROFOPS[k]) {
				switch (ORDEROFOPS[k]) {
					case '+':
						doubleArgOp(i, at(i-1).val + at(i+1).val);
						break;
					case '-':
						doubleArgOp(i, at(i-1).val - at(i+1).val);
						break;
					case '*':
						doubleArgOp(i, at(i-1).val * at(i+1).val);
						break;
					case '/':
						doubleArgOp(i, at(i-1).val / at(i+1).val);
						break;
					case '^':
						doubleArgOp(i, pow(at(i-1).val, at(i+1).val));
						break;
					case '%':
						doubleArgOp(i, remainder(at(i-1).val, at(i+1).val));
						break;
					case 'r':
						doubleArgOp(i, pow(at(i-1).val, 1 / at(i+1).val));
						break;
					case '!':
						singleArgOp(i, tgamma(at(i-1).val + 1));
						break;
					case 's':
						trig(i, sin(at(i+1).val));
						break;
					case 'c':
						trig(i, cos(at(i+1).val));
						break;
					case 't':
						trig(i, tan(at(i+1).val));
						break;
				}
				i--;
			}
		}
	}
	return at(0).val;
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