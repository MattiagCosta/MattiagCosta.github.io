#include "WholeNumbers.h"

WholeNumber WholeNumberFactorial(WholeNumber number){
	WholeNumber secondNumber(figures[1]), result(figures[1]);
	while(WholeNumbersRelations(secondNumber, number)!='>'){
		result = WholeNumbersMultiplication(result, secondNumber);
		secondNumber = WholeNumbersAddition(secondNumber, WholeNumber(figures[1]));
	}
	return result;
}


#include <iostream>

int main(){

	std::cout << WholeNumbersSubtraction(WholeNumberFactorial(WholeNumber("300")), WholeNumber('1')).GetNumber();

	return 0;
}