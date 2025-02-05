#include "WholeNumbers.h"

#include <cassert>

std::string figures = "0123456789";

WholeNumber::WholeNumber(char rawNumber){ // Easier to work with figures
	assert(figures.find(rawNumber)!=std::string::npos);
	number = std::string(1, rawNumber);
}
WholeNumber::WholeNumber(std::string rawNumber){
	assert(!rawNumber.empty());
	for(char figure : rawNumber){
		assert(figures.find(figure)!=std::string::npos);
	}
	size_t numberOfZeroes = 0;
	for(char figure : rawNumber){
		if(figure==figures[0]){ numberOfZeroes++; }
		else{ break; }
	}
	rawNumber.erase(0, numberOfZeroes);
	if(rawNumber.empty()){ rawNumber = figures[0]; }
	number = rawNumber;
}
std::string WholeNumber::GetNumber(){ return number; }

char WholeNumbersRelations(WholeNumber number0, WholeNumber number1){
	if(number0.GetNumber().length()<number1.GetNumber().length()){ return '<'; }
	if(number0.GetNumber().length()>number1.GetNumber().length()){ return '>'; }
	if(number0.GetNumber()==number1.GetNumber()){ return '='; }
	for(size_t index = 0; index<number0.GetNumber().length(); index++){
		int figure0Index = figures.find(number0.GetNumber()[index]);
		int figure1Index = figures.find(number1.GetNumber()[index]);
		if(figure0Index<figure1Index){ return '<'; }
		if(figure0Index>figure1Index){ return '>'; }
	}
}

WholeNumber WholeNumbersAddition(WholeNumber addend0, WholeNumber addend1){
	int figuresDifference = addend0.GetNumber().length()-addend1.GetNumber().length();
	if(figuresDifference<0){
		WholeNumber thirdNumber (addend0);
		addend0 = addend1;
		addend1 = thirdNumber;
		figuresDifference = -figuresDifference;
	}
	std::string sumNumber;
	int addOne = 0;
	int sumFigureIndex;
	for(long long int index = addend1.GetNumber().length()-1; index>=0; index--){
		sumFigureIndex = figures.find(addend0.GetNumber()[index+figuresDifference])+figures.find(addend1.GetNumber()[index])+addOne;
		addOne = 0;
		if(sumFigureIndex>=figures.length()){
			sumFigureIndex-=figures.length();
			addOne = 1;
		}
		sumNumber = figures[sumFigureIndex]+sumNumber;
	}
	for(long long int index = figuresDifference-1; index>=0; index--){
		sumFigureIndex = figures.find(addend0.GetNumber()[index])+addOne;
		addOne = 0;
		if(sumFigureIndex>=figures.length()){
			sumFigureIndex-=figures.length();
			addOne = 1;
		}
		sumNumber = figures[sumFigureIndex]+sumNumber;
	}
	if(addOne){ sumNumber = figures[1]+sumNumber; }
	return WholeNumber(sumNumber);
}

WholeNumber WholeNumbersSubtractionLooping(WholeNumber minuend, WholeNumber subtrahend){
	assert(WholeNumbersRelations(minuend, subtrahend)!='<'); // Impossible
	WholeNumber difference (figures[0]);
	while(WholeNumbersRelations(WholeNumbersAddition(subtrahend, difference), minuend)!='='){
		difference = WholeNumbersAddition(difference, WholeNumber(figures[1]));
	}
	return difference;
}

WholeNumber WholeNumbersSubtraction(WholeNumber minuend, WholeNumber subtrahend){
	assert(WholeNumbersRelations(minuend, subtrahend)!='<'); // Impossible
	int figuresDifference = minuend.GetNumber().length()-subtrahend.GetNumber().length();
	std::string differenceNumber;
	bool adjustFigures = false, adjustForZero = false;
	for(long long int index = subtrahend.GetNumber().length()-1; index>=0; index--){
		char minuendFigure = minuend.GetNumber()[index+figuresDifference];
		if(adjustFigures || adjustForZero){
			if(WholeNumbersRelations(WholeNumber(minuendFigure), WholeNumber(figures[0]))=='='){
				adjustForZero = true;
				minuendFigure = WholeNumbersSubtractionLooping(WholeNumber(std::string(1, figures[1])+std::string(1, figures[0])), WholeNumber(figures[1])).GetNumber()[0];
			}
			else{
				minuendFigure = WholeNumbersSubtractionLooping(WholeNumber(minuendFigure), WholeNumber(figures[1])).GetNumber()[0];
				adjustForZero = false;
			}
			adjustFigures = false;
		}
		adjustFigures = WholeNumbersRelations(WholeNumber(minuendFigure), WholeNumber(subtrahend.GetNumber()[index]))=='<';
		WholeNumber newFigure(figures[0]);
		if(adjustFigures){
			newFigure = WholeNumbersSubtractionLooping(WholeNumbersAddition(WholeNumber(minuendFigure), WholeNumber(std::string(1, figures[1])+std::string(1, figures[0]))), WholeNumber(subtrahend.GetNumber()[index]));
		}
		else{
			newFigure = WholeNumbersSubtractionLooping(WholeNumber(minuendFigure), WholeNumber(subtrahend.GetNumber()[index]));
		}
		differenceNumber = newFigure.GetNumber() + differenceNumber;
	}
	for(long long int index = figuresDifference-1; index>=0; index--){
		if(adjustFigures || adjustForZero){
			if(WholeNumbersRelations(WholeNumber(minuend.GetNumber()[index]), WholeNumber(figures[0]))=='='){
				differenceNumber = WholeNumbersSubtractionLooping(WholeNumber(std::string(1, figures[1])+std::string(1, figures[0])), WholeNumber(figures[1])).GetNumber()+differenceNumber;
			}
			else{
				differenceNumber = WholeNumbersSubtractionLooping(WholeNumber(minuend.GetNumber()[index]), WholeNumber(figures[1])).GetNumber()+differenceNumber;
				adjustFigures = false;
				adjustForZero = false;
			}
			continue;
		}
		differenceNumber = minuend.GetNumber()[index]+differenceNumber;
	}
	return WholeNumber(differenceNumber);
}

WholeNumber WholeNumbersMultiplicationLooping(WholeNumber multiplicand, WholeNumber multiplier){
	WholeNumber product(figures[0]);
	WholeNumber thirdNuber(figures[0]);
	while(WholeNumbersRelations(thirdNuber, multiplier)!='='){
		product = WholeNumbersAddition(product, multiplicand);
		thirdNuber = WholeNumbersAddition(thirdNuber, WholeNumber(figures[1]));
	}
	return product;
}

WholeNumber WholeNumbersMultiplication(WholeNumber multiplicand, WholeNumber multiplier){
	std::string productFigures(1, figures[0]);
	size_t zeroesToAdd = 0;
	for(long long int multiplierIndex = multiplier.GetNumber().length()-1; multiplierIndex>=0; multiplierIndex--){
		std::string tempProductFigures(1, figures[0]);
		int zeroesToAddTemp = 0;
		for(long long int multiplicandIndex = multiplicand.GetNumber().length()-1; multiplicandIndex>=0; multiplicandIndex--){
			std::string figuresProductNumber = WholeNumbersMultiplicationLooping(WholeNumber(multiplier.GetNumber()[multiplierIndex]), WholeNumber(multiplicand.GetNumber()[multiplicandIndex])).GetNumber();
			for(int i = 0; i<zeroesToAddTemp; i++){ figuresProductNumber+=std::string(1, figures[0]); }
			tempProductFigures = WholeNumbersAddition(WholeNumber(tempProductFigures), WholeNumber(figuresProductNumber)).GetNumber();
			zeroesToAddTemp++;
		}
		for(int i = 0; i<zeroesToAdd; i++){ tempProductFigures+=std::string(1, figures[0]); }
		zeroesToAdd++;
		productFigures = WholeNumbersAddition(WholeNumber(productFigures), WholeNumber(tempProductFigures)).GetNumber();
	}
	return WholeNumber(productFigures);
}

WholeNumbersDivisionResult WholeNumbersDivision(WholeNumber dividend, WholeNumber divisor){
	assert(WholeNumbersRelations(divisor, WholeNumber(figures[0]))!='='); // Undefined / Impossible
	std::string quotientNumber, thirdNumberFigures;
	for(char figure : dividend.GetNumber()){
		thirdNumberFigures+=figure;
		WholeNumber quotientFigure(figures[0]);
		WholeNumber thirdNumber(thirdNumberFigures);
		while(WholeNumbersRelations(WholeNumbersMultiplication(divisor, quotientFigure), thirdNumber)=='<'){
			quotientFigure = WholeNumbersAddition(quotientFigure, WholeNumber(figures[1]));
		}
		if(WholeNumbersRelations(WholeNumbersMultiplication(divisor, quotientFigure), thirdNumber)=='>'){
			quotientFigure = WholeNumbersSubtraction(quotientFigure, WholeNumber(figures[1]));
		}
		thirdNumberFigures = WholeNumbersSubtraction(thirdNumber, WholeNumbersMultiplication(divisor, quotientFigure)).GetNumber();
		quotientNumber+=quotientFigure.GetNumber();
	}
	return {WholeNumber(quotientNumber), WholeNumber(thirdNumberFigures)};
}

WholeNumber WholeNumbersExponentiation(WholeNumber base, WholeNumber power){
	assert(WholeNumbersRelations(base, WholeNumber(figures[0]))!='=' || WholeNumbersRelations(power, WholeNumber(figures[0]))!='='); // Undefined
	WholeNumber result(figures[1]), thirdNumber(figures[0]);
	while(WholeNumbersRelations(thirdNumber, power)!='='){
		result = WholeNumbersMultiplication(result, base);
		thirdNumber = WholeNumbersAddition(thirdNumber, WholeNumber(figures[1]));
	}
	return result;
}

bool IsPrimeNumberLooping(WholeNumber number){
	if(WholeNumbersRelations(number, WholeNumber(figures[0]))=='=' || WholeNumbersRelations(number, WholeNumber(figures[1]))=='='){ return false; }
	WholeNumber secondNumber = WholeNumbersAddition(WholeNumber(figures[1]), WholeNumber(figures[1]));
	while(WholeNumbersRelations(number, secondNumber)=='>'){
		if(WholeNumbersRelations(WholeNumbersDivision(number, secondNumber).remainder, WholeNumber(figures[0]))=='='){ return false; }
		secondNumber = WholeNumbersAddition(secondNumber, WholeNumber(figures[1]));
	}
	return true;
}

bool IsPrimeNumber(WholeNumber number, std::vector<WholeNumber> previousPrimeNumbers){
	if(WholeNumbersRelations(number, WholeNumber(figures[0]))=='=' || WholeNumbersRelations(number, WholeNumber(figures[1]))=='='){ return false; }
	for(WholeNumber primeNumber : previousPrimeNumbers){
		if(WholeNumbersRelations(WholeNumbersDivision(number, primeNumber).remainder, WholeNumber(figures[0]))=='='){ return false; }
	}
	return true;
}

std::vector<WholeNumber> GetPrimeNumbers(WholeNumber lastNumber){
	if(WholeNumbersRelations(lastNumber, WholeNumbersAddition(WholeNumber(figures[1]), WholeNumber(figures[1])))=='<'){ return {}; }
	WholeNumber number = WholeNumbersAddition(WholeNumber(figures[1]), WholeNumber(figures[1]));
	std::vector<WholeNumber> primeNumbers;
	while(WholeNumbersRelations(number, lastNumber)!='>'){
		if(IsPrimeNumber(number, primeNumbers)){ primeNumbers.push_back(number); }
		number = WholeNumbersAddition(number, WholeNumber(figures[1]));
	}
	return primeNumbers;
}

std::vector<WholeNumber> WholeNumberFactorization(WholeNumber number){
	assert(WholeNumbersRelations(number, WholeNumber(figures[0]))!='='); // Can't factorize zero
	if(WholeNumbersRelations(number, WholeNumber(figures[1]))=='='){ return {}; }
	std::vector<WholeNumber> factors;
	std::vector<WholeNumber> primeNumbers = GetPrimeNumbers(number);
	size_t index = 0;
	while(index<primeNumbers.size()){
		if(WholeNumbersRelations(number, WholeNumber(figures[1]))=='='){ break; }
		WholeNumbersDivisionResult division = WholeNumbersDivision(number, primeNumbers[index]);
		if(WholeNumbersRelations(division.remainder, WholeNumber(figures[0]))=='='){
			factors.push_back(primeNumbers[index]);
			number = division.quotient;
			continue;
		}
		index++;
	}
	return factors;
}

WholeNumber WholeNumbersGreatestCommonDivisor(std::vector<WholeNumber> wholeNumbers){
	assert(wholeNumbers.size()>1); // There must be at least two whole numbers
	std::vector<std::vector<WholeNumber>> factorizations;
	for(WholeNumber number : wholeNumbers){
		assert(WholeNumbersRelations(number, WholeNumber(figures[0]))!='='); // Can't factorize zero
		if(WholeNumbersRelations(number, WholeNumber(figures[1]))=='='){ return WholeNumber(figures[1]); }
		factorizations.push_back(WholeNumberFactorization(number));
	}
	std::vector<WholeNumber> commonFactors;
	bool isCommonFactor, skip;
	for(WholeNumber factor : factorizations[0]){
		skip = false;
		for(WholeNumber number : commonFactors){
			if(WholeNumbersRelations(factor, number)=='='){ skip = true; }
		}
		if(skip){ continue; }
		for(size_t index = 1; index<factorizations.size(); index++){
			isCommonFactor = false;
			for(WholeNumber otherFactor : factorizations[index]){
				if(WholeNumbersRelations(factor, otherFactor)=='='){
					isCommonFactor = true;
					break;
				}
			}
			if(!isCommonFactor){ break; }
		}
		if(isCommonFactor){ commonFactors.push_back(factor); }
	}
	if(commonFactors.empty()){ return WholeNumber(figures[1]); }
	for(size_t index = 1; index<commonFactors.size(); index++){
		commonFactors[0] = WholeNumbersMultiplication(commonFactors[0], commonFactors[index]);
	}
	return commonFactors[0];
}

WholeNumber WholeNumbersLeastCommonMultiple(std::vector<WholeNumber> wholeNumbers){
	assert(wholeNumbers.size()>1); // There must be at least two whole numbers
	std::vector<std::vector<WholeNumber>> factorizations;
	for(WholeNumber number : wholeNumbers){
		assert(WholeNumbersRelations(number, WholeNumber(figures[0]))!='='); // Can't factorize zero
		factorizations.push_back(WholeNumberFactorization(number));
	}
	std::vector<WholeNumber> factors, powers;
	bool isAlreadyInFactors;
	int index;
	for(std::vector<WholeNumber> factorization : factorizations){
		if(factorization.empty()){ continue; }
		WholeNumber LastPrimeNumber(figures[0]);
		for(WholeNumber primeNumberToConsider : factorization){
			if(WholeNumbersRelations(primeNumberToConsider, LastPrimeNumber)=='='){ continue; }
			WholeNumber power(figures[0]);
			for(WholeNumber primeNumber : factorization){
				if(WholeNumbersRelations(primeNumberToConsider, primeNumber)=='='){ power = WholeNumbersAddition(power, WholeNumber(figures[1])); }
			}
			isAlreadyInFactors = false;
			for(index = 0; index<factors.size(); index++){
				if(WholeNumbersRelations(primeNumberToConsider, factors[index])=='='){
					isAlreadyInFactors = true;
					break;
				}
			}
			if(!isAlreadyInFactors){
				factors.push_back(primeNumberToConsider);
				powers.push_back(power);
				continue;
			}
			if(WholeNumbersRelations(power, powers[index])=='>'){ powers[index] = power; }
		}
	}
	if(factors.empty()){ return WholeNumber(figures[1]); }
	for(index = 0; index<factors.size(); index++){
		factors[index] = WholeNumbersExponentiation(factors[index], powers[index]);
	}
	for(index = 1; index<factors.size(); index++){
		factors[0] = WholeNumbersMultiplication(factors[0], factors[index]);
	}
	return factors[0];
}

bool CheckFigures(std::string figures){
	if(figures.length()<2){ return false; }
	for(char figure : figures){
		if(figures.find(figure)==std::string::npos){ return false; }
	}
	return true;
}

void SetFigures(std::string newFigures){
	if(CheckFigures(newFigures)){ figures = newFigures; }
}

WholeNumber WholeNumberConvertBase(WholeNumber wholeNumber, std::string baseFiguresUsed, std::string newBaseFigures){
	assert(CheckFigures(baseFiguresUsed) && CheckFigures(newBaseFigures));
	if(baseFiguresUsed==newBaseFigures){ return wholeNumber; }
	if(baseFiguresUsed.length()==newBaseFigures.length()){
		std::string newFigures, tempFigures = figures;
		figures = newBaseFigures;
		for(char figure : wholeNumber.GetNumber()){
			newFigures+=newBaseFigures[baseFiguresUsed.find(figure)];
		}
		wholeNumber = WholeNumber(newFigures);
		figures = tempFigures;
		return wholeNumber;
	}
	if(baseFiguresUsed.length()<newBaseFigures.length()){
		std::string newFigures;
		for(char figure : wholeNumber.GetNumber()){
			newFigures+=newBaseFigures[baseFiguresUsed.find(figure)];
		}
		std::string tempFigures = figures;
		figures = newBaseFigures;
		WholeNumber newWholeNumber(newBaseFigures[0]);
		for(size_t index = 0; index<newFigures.length(); index++){
			newWholeNumber = WholeNumbersAddition(newWholeNumber, WholeNumbersMultiplication(WholeNumber(newFigures[index]), WholeNumbersExponentiation(WholeNumber(newBaseFigures[baseFiguresUsed.length()]), WholeNumber(newBaseFigures[newFigures.length()-index-1]))));
		}
		figures = tempFigures;
		return newWholeNumber;
	}
	std::string numberConverted;
	WholeNumber quotient = wholeNumber;
	std::string tempFigures = figures;
	figures = baseFiguresUsed;
	while(WholeNumbersRelations(quotient, WholeNumber(baseFiguresUsed[0]))!='='){
		WholeNumbersDivisionResult divisionResult = WholeNumbersDivision(quotient, WholeNumber(baseFiguresUsed[newBaseFigures.length()]));
		if(WholeNumbersRelations(divisionResult.remainder, WholeNumber(baseFiguresUsed[0]))!='='){ numberConverted = divisionResult.remainder.GetNumber()+numberConverted; }
		else{ numberConverted = baseFiguresUsed[0]+numberConverted; }
		quotient = divisionResult.quotient;
	}
	std::string figuresWanted;
	for(size_t index = 0; index<newBaseFigures.length(); index++){
		figuresWanted+=baseFiguresUsed[index];
	}
	numberConverted = WholeNumberConvertBase(WholeNumber(numberConverted), figuresWanted, newBaseFigures).GetNumber();
	figures = newBaseFigures;
	wholeNumber = WholeNumber(numberConverted);
	figures = tempFigures;
	return wholeNumber;
}