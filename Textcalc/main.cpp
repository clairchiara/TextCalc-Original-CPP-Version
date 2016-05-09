//
//  main.cpp
//  Textcalc
//
//  Copyright (c) 2014 Clair Marchesani. All rights reserved.
//

#include <iostream>
#include <math.h>
#include "txc-vector.h"

int main(int argc, const char * argv[]) {
	
	char help[] = "Error. Use --help for help\n";

	if (argc == 7) {
		if((strcmp(argv[1], "-q")) != 0) std::cout << help;
		else if ((strcmp(argv[2], "-s")) != 0) std::cout << help;
		else if ((strcmp(argv[5], "-p")) != 0) std::cout << help;
		else { // Equation solving mode with custom parameters
			
			txc::string equation;
			
			equation.solveEquation(atof(argv[3]), atof(argv[4]), atol(argv[6]));
		}
	} else if (argc == 5) { // Equation solving mode with custom starting values
		if ((strcmp(argv[1], "-q")) != 0) std::cout << help;
		else if ((strcmp(argv[2], "-s")) != 0) std::cout << help;
		else {
			
			txc::string equation;
			
			equation.solveEquation(atof(argv[3]), atof(argv[4]), 500000);
		}
	} else if (argc == 4) { // Equation solving mode with custom number of passages
		if ((strcmp(argv[1], "-q")) != 0) std::cout << help;
		else if ((strcmp(argv[2], "-p")) != 0) std::cout << help;
		else {
			
			txc::string equation;
			
			equation.solveEquation(txc::random(1), txc::random(1), atol(argv[3]));
		}
	} else if (argc == 2) { // Help
		if (strcmp(argv[1], "--help") == 0) txc::help(argv[0]);
		else if (strcmp(argv[1], "-h") == 0) txc::help(argv[0]);
		else if (strcmp(argv[1], "-e") == 0) { // Expression solving mode
			std::cout << "Please type in your expression, without spaces\n";
			
			txc::string expression = txc::string::newFromInput();
			txc::vector eqVector;
			
			expression.checkBrackets();
			expression.checkSpaces();
			expression.checkForm();
			eqVector.populate(expression);
			std::cout << "The solution is " << eqVector.solveAll() << "\n";
			exit(0);
		} else if (strcmp(argv[1], "-q") == 0) { // Equation solving mode with default parameters
			
			txc::string equation;
			
			equation.solveEquation(txc::random(1), txc::random(1), 500000);
		} else std::cout << help;
	} else if (argc == 1) { // Calculator mode
		
		double one, two, result;
		char oper;
				
		std::cout << "\nPlease type in your operation\n";
		scanf("%lg", &one);
		scanf("%s", &oper);
		switch (oper) {
			case '+':
				scanf("%lg", &two);
				result = one + two;
				break;
			case '-':
				scanf("%lg", &two);
				result = one - two;
				break;
			case '*':
				scanf("%lg", &two);
				result = one * two;
				break;
			case '/':
				scanf("%lg", &two);
				result = one / two;
				break;
			case '^':
				scanf("%lg", &two);
				result = pow(one, two);
				break;
			case '%':
				scanf("%lg", &two);
				result = remainder(one, two);
				break;
			case 'r':
				scanf("%lg", &two);
				result = pow(one, 1 / two);
				break;
			case '!':
				result = tgamma(one + 1);
				break;
			case 's':
				scanf("%lg", &two);
				result = sin(two);
				break;
			case 'c':
				scanf("%lg", &two);
				result = cos(two);
				break;
			case 't':
				scanf("%lg", &two);
				result = tan(two);
				break;
			default:
				result = NAN;
				break;
		}
		std::cout << result << "\n";
		for (; ; ) { // Continues until the program is terminated
			scanf("%s", &oper);
			switch (oper) {
				case '+':
					scanf("%lg", &two);
					result += two;
					break;
				case '-':
					scanf("%lg", &two);
					result -= two;
					break;
				case '*':
					scanf("%lg", &two);
					result *= two;
					break;
				case '/':
					scanf("%lg", &two);
					result /= two;
					break;
				case '^':
					scanf("%lg", &two);
					result = pow(result, two);
					break;
				case '%':
					scanf("%lg", &two);
					result = remainder(result, two);
					break;
				case 'r':
					scanf("%lg", &two);
					result = pow(result, 1 / two);
					break;
				case '!':
					result = tgamma(result + 1);
					break;
				case 's':
					result = sin(one);
					break;
				case 'c':
					result = cos(one);
					break;
				case 't':
					result = tan(one);
					break;
				default:
					result = NAN;
					break;
			}
			std::cout << result << "\n";
		}
	}
	return 0;
}