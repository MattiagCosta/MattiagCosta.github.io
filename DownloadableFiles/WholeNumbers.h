#ifndef WHOLENUMBERS_H
#define WHOLENUMBERS_H

#include <string>
#include <vector>

extern std::string figures;

class WholeNumber {
	private:
		std::string number;
	public:
		WholeNumber(char rawNumber);
		WholeNumber(std::string rawNumber);
		std::string GetNumber();
};

char WholeNumbersRelations(WholeNumber number0, WholeNumber number1);

WholeNumber WholeNumbersAddition(WholeNumber addend0, WholeNumber addend1);
WholeNumber WholeNumbersSubtractionLooping(WholeNumber minuend, WholeNumber subtrahend);
WholeNumber WholeNumbersSubtraction(WholeNumber minuend, WholeNumber subtrahend);
WholeNumber WholeNumbersMultiplicationLooping(WholeNumber multiplicand, WholeNumber multiplier);
WholeNumber WholeNumbersMultiplication(WholeNumber multiplicand, WholeNumber multiplier);

struct WholeNumbersDivisionResult {
	WholeNumber quotient;
	WholeNumber remainder;
};

WholeNumbersDivisionResult WholeNumbersDivision(WholeNumber dividend, WholeNumber divisor);
WholeNumber WholeNumbersExponentiation(WholeNumber base, WholeNumber power);

bool IsPrimeNumberLooping(WholeNumber number);
bool IsPrimeNumber(WholeNumber number, std::vector<WholeNumber> previousPrimeNumbers);
std::vector<WholeNumber> GetPrimeNumbers(WholeNumber lastNumber);
std::vector<WholeNumber> WholeNumberFactorization(WholeNumber number);
WholeNumber WholeNumbersGreatestCommonDivisor(std::vector<WholeNumber> wholeNumbers);
WholeNumber WholeNumbersLeastCommonMultiple(std::vector<WholeNumber> wholeNumbers);

bool CheckFigures(std::string figures);
void SetFigures(std::string newFigures);
WholeNumber WholeNumberConvertBase(WholeNumber wholeNumber, std::string baseFiguresUsed, std::string newBaseFigures);

#endif // WHOLENUMBERS_H