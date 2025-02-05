#Python3.12.0

figures = '0123456789'

class WholeNumber:
	def __init__(self, number:str) -> None:
		if type(number)!=str: exit(code='E0')
		if number=='': exit(code='E1')
		noMoreZeros = False
		value = ''
		for character in number:
			if not character in figures: exit(code='E2')
			if character!=figures[0] and not noMoreZeros: noMoreZeros = True
			if noMoreZeros: value+=character
		if value=='': value = figures[0]
		self.number = value

def WholeNumbersRelation(number0:WholeNumber, number1:WholeNumber) -> str:
	if type(number0)!=WholeNumber or type(number1)!=WholeNumber: exit(code='E3')
	if len(number0.number)<len(number1.number): relation = '<'
	elif len(number0.number)>len(number1.number): relation = '>'
	elif number0.number==number1.number:
		relation = '='
	else:
		for figure in range(len(number0.number)):
			figureIndexNumber0 = figures.index(number0.number[figure])
			figureIndexNumber1 = figures.index(number1.number[figure])
			if figureIndexNumber0<figureIndexNumber1:
				relation = '<'
				break
			elif figureIndexNumber0>figureIndexNumber1:
				relation = '>'
				break
	return relation

def WholeNumbersAddition(addend0:WholeNumber, addend1:WholeNumber) -> WholeNumber:
	if type(addend0)!=WholeNumber or type(addend1)!=WholeNumber: exit(code='E4')
	figuresDifference = len(addend0.number)-len(addend1.number)
	if figuresDifference<0:
		thirdNumber = addend0
		addend0 = addend1
		addend1 = thirdNumber
	sumNumber = ''
	addOne = 0
	for figure in range(-1, -(len(addend1.number)+1), -1):
		figureIndexSum = figures.index(addend0.number[figure])+addOne+figures.index(addend1.number[figure])
		addOne = 0
		if figureIndexSum>=len(figures):
			figureIndexSum-=len(figures)
			addOne = 1
		sumNumber = figures[figureIndexSum]+sumNumber
	if figuresDifference!=0:
		if figuresDifference<0: figuresDifference*=-1
		for figure in range(-(len(addend0.number)-figuresDifference+1), -(len(addend0.number)+1), -1):
			if addOne==1:
				figureIndexSum = figures.index(addend0.number[figure])+1
				addOne = 0
				if figureIndexSum>=len(figures):
					figureIndexSum = 0
					addOne = 1
				sumNumber = figures[figureIndexSum] + sumNumber
				continue
			sumNumber = addend0.number[figure]+sumNumber
	if addOne==1:
		sumNumber = figures[1]+sumNumber
	return WholeNumber(sumNumber)

def WholeNumbersSubtractionLooping(minuend:WholeNumber, subtrahend:WholeNumber):
	if type(minuend)!=WholeNumber or type(subtrahend)!=WholeNumber: exit(code='E6')
	if WholeNumbersRelation(minuend, subtrahend)=='<': return 'Impossible.'
	difference = WholeNumber(figures[0])
	while WholeNumbersRelation(WholeNumbersAddition(subtrahend, difference), minuend)!='=':
		difference = WholeNumbersAddition(difference, WholeNumber(figures[1]))
	return difference

def WholeNumbersSubtraction(minuend:WholeNumber, subtrahend:WholeNumber):
	if type(minuend)!=WholeNumber or type(subtrahend)!=WholeNumber: exit(code='E6')
	if WholeNumbersRelation(minuend, subtrahend)=='<': return 'Impossible.'
	differenceNumber = ''
	adjustFigures = False
	adjustForZero = False
	for figure in range(-1, -(len(subtrahend.number)+1), -1):
		minuendFigure = WholeNumber(minuend.number[figure])
		if adjustFigures or adjustForZero:
			if WholeNumbersRelation(minuendFigure, WholeNumber(figures[0]))=='=':
				adjustForZero = True
				minuendFigure = WholeNumbersSubtractionLooping(WholeNumber(figures[1]+figures[0]), WholeNumber(figures[1]))
			else:
				minuendFigure = WholeNumbersSubtractionLooping(minuendFigure, WholeNumber(figures[1]))
				adjustForZero = False
			adjustFigures = False
		adjustFigures = WholeNumbersRelation(minuendFigure, WholeNumber(subtrahend.number[figure]))=='<'
		if adjustFigures: minuendFigure = WholeNumbersAddition(minuendFigure, WholeNumber(figures[1]+figures[0]))	#	The ten is just the second figure (the one) followed by the first figure (the zero)
		newFigure = WholeNumbersSubtractionLooping(minuendFigure, WholeNumber(subtrahend.number[figure]))
		differenceNumber = newFigure.number+differenceNumber
	for figure in range(-len(subtrahend.number)-1, -(len(minuend.number)+1), -1):
		if adjustFigures or adjustForZero:
			if WholeNumbersRelation(WholeNumber(minuend.number[figure]), WholeNumber(figures[0]))=='=': differenceNumber = WholeNumbersSubtractionLooping(WholeNumber(figures[1]+figures[0]), WholeNumber(figures[1])).number+differenceNumber
			else:
				differenceNumber = WholeNumbersSubtraction(WholeNumber(minuend.number[figure]), WholeNumber(figures[1])).number+differenceNumber
				adjustFigures = False
				adjustForZero = False
			continue
		differenceNumber = minuend.number[figure]+differenceNumber
	return WholeNumber(differenceNumber)

def WholeNumbersMultiplicationLooping(multiplicand:WholeNumber, multiplier:WholeNumber) -> WholeNumber:
	if type(multiplicand)!=WholeNumber or type(multiplier)!=WholeNumber: exit(code='E5')
	product = WholeNumber(figures[0])
	thirdNumber = WholeNumber(figures[0])
	while WholeNumbersRelation(thirdNumber, multiplier)!='=':
		product = WholeNumbersAddition(product, multiplicand)
		thirdNumber = WholeNumbersAddition(thirdNumber, WholeNumber(figures[1]))
	return product

def  WholeNumbersMultiplication(multiplicand:WholeNumber, multiplier:WholeNumber):
	if type(multiplicand)!=WholeNumber or type(multiplier)!=WholeNumber: exit(code='E5')
	product = WholeNumber(figures[0])
	zeroesToAdd = 0
	for multiplierFigure in range(-1, -(len(multiplier.number)+1), -1):
		tempProduct = WholeNumber(figures[0])
		figuresCount = 0
		for multiplicandFigure in range(-1, -(len(multiplicand.number)+1), -1):
			figuresProduct = WholeNumbersMultiplicationLooping(WholeNumber(multiplier.number[multiplierFigure]), WholeNumber(multiplicand.number[multiplicandFigure]))
			figuresProduct.number+=figures[0]*figuresCount
			tempProduct = WholeNumbersAddition(tempProduct, figuresProduct)
			figuresCount+=1
		tempProduct.number+=figures[0]*zeroesToAdd
		zeroesToAdd+=1
		product = WholeNumbersAddition(product, tempProduct)
	return product

def WholeNumbersDivision(dividend:WholeNumber, divisor:WholeNumber):
	if type(dividend)!=WholeNumber or type(divisor)!=WholeNumber: exit(code='E')
	if WholeNumbersRelation(dividend, WholeNumber(figures[0]))=='=' and WholeNumbersRelation(divisor, WholeNumber(figures[0]))=='=': return 'Undefined.'
	if WholeNumbersRelation(divisor, WholeNumber(figures[0]))=='=': return 'Impossible.'
	quozientNumber = ''
	thirdNumberFigures = ''
	for figure in dividend.number:
		thirdNumberFigures+=figure
		quozientFigure = WholeNumber(figures[0])
		thirdNumber = WholeNumber(thirdNumberFigures)
		while WholeNumbersRelation(WholeNumbersMultiplication(divisor, quozientFigure), thirdNumber)=='<': quozientFigure = WholeNumbersAddition(quozientFigure, WholeNumber(figures[1]))
		if WholeNumbersRelation(WholeNumbersMultiplication(quozientFigure, divisor), thirdNumber)=='>': quozientFigure = WholeNumbersSubtraction(quozientFigure, WholeNumber(figures[1]))
		thirdNumberFigures = WholeNumbersSubtraction(thirdNumber, WholeNumbersMultiplication(quozientFigure, divisor)).number
		quozientNumber+=quozientFigure.number
	if WholeNumbersRelation(WholeNumber(thirdNumberFigures), WholeNumber(figures[0]))=='=': return WholeNumber(quozientNumber)
	return (WholeNumber(quozientNumber), WholeNumber(thirdNumberFigures))

def WholeNumbersExponentiation(base:WholeNumber, power:WholeNumber):
	if type(base)!=WholeNumber or type(power)!=WholeNumber: exit(code='E8')
	if WholeNumbersRelation(base, WholeNumber(figures[0]))=='=' and WholeNumbersRelation(power, WholeNumber(figures[0]))=='=': return 'Undefined.'
	result = WholeNumber(figures[1])
	thirdNumber = WholeNumber(figures[0])
	while WholeNumbersRelation(thirdNumber, power)!='=':
		result = WholeNumbersMultiplication(result, base)
		thirdNumber = WholeNumbersAddition(thirdNumber, WholeNumber(figures[1]))
	return result

def WholeNumberFactorization(number:WholeNumber) -> list:
	def GetPrimeNumbers(lastNumber):
		def IsPrimeNumber(number):
			secondNumber = WholeNumbersAddition(WholeNumber(figures[1]), WholeNumber(figures[1]))
			while WholeNumbersRelation(number, secondNumber)=='>':
				if type(WholeNumbersDivision(number, secondNumber))!=tuple: return False
				secondNumber = WholeNumbersAddition(secondNumber, WholeNumber(figures[1]))
			return True
		number = WholeNumbersAddition(WholeNumber(figures[1]), WholeNumber(figures[1]))
		primeNumbers = []
		while WholeNumbersRelation(number, lastNumber)!='>':
			if IsPrimeNumber(number): primeNumbers.append(number)
			number = WholeNumbersAddition(number, WholeNumber(figures[1]))
		return primeNumbers
	if type(number)!=WholeNumber: exit(code='E24')
	if WholeNumbersRelation(number, WholeNumber(figures[0]))=='=': return 'Can\'t factorize the whole number zero.'
	if WholeNumbersRelation(number, WholeNumber(figures[1]))=='=': return []
	factors = []
	primeNumbers = GetPrimeNumbers(number)
	index = 0
	while index<len(primeNumbers):
		if WholeNumbersRelation(number, WholeNumber(figures[1]))=='=': break
		division = WholeNumbersDivision(number, primeNumbers[index])
		if type(division)==WholeNumber:
			factors.append(primeNumbers[index])
			number = division
			continue
		index+=1
	return factors

def SolveShortWholeNumbersExpression(expression:list):
	index = -1
	while index>-(len(expression)+1):
		if expression[index]=='^':
			expression.insert(index, WholeNumbersExponentiation(expression[index-1], expression[index+1]))
			expression.pop(index)
			expression.pop(index+1)
			expression.pop(index)
			continue
		index-=1
	index = 0
	while index<len(expression):
		if expression[index]=='*':
			expression.insert(index, WholeNumbersMultiplication(expression[index-1], expression[index+1]))
			expression.pop(index+1)
			expression.pop(index+1)
			expression.pop(index-1)
			continue
		index+=1
	return expression[0]

def WholeNumbersGreatestCommonDivisor(numbers:list):
	if type(numbers)!=list: exit(code='E25')
	if len(numbers)<2: return 'There must be at least two whole numbers to find the greatest common divisor between whole numbers.'
	factorizations = []
	for number in numbers: factorizations.append(WholeNumberFactorization(number))
	if 'Can\'t factorize the whole number zero.' in factorizations: return 'Can\'t factorize the whole number zero.'
	if [] in factorizations: return WholeNumber(figures[1])
	factorsInCommon = []
	for primeNumber in factorizations[0]:
		if primeNumber in factorsInCommon: continue
		factorizationsWithPrimeNumber = 0
		for otherFactorization in factorizations:
			for otherPrimeNumber in otherFactorization:
				if WholeNumbersRelation(primeNumber, otherPrimeNumber)=='=':
					factorizationsWithPrimeNumber+=1
					break
		if factorizationsWithPrimeNumber==len(factorizations): factorsInCommon.append(primeNumber)
	if factorsInCommon==[]: return WholeNumber(figures[1])
	index = 1
	while index<len(factorsInCommon):
		factorsInCommon.insert(index, '*')
		index+=2
	return SolveShortWholeNumbersExpression(factorsInCommon)

def WholeNumbersLeastCommonMultiple(numbers:list):
	if type(numbers)!=list: exit(code='E26')
	if len(numbers)<2: return 'There must be at least two whole numbers to find the least common multiple between whole numbers.'
	factorizations = []
	for number in numbers: factorizations.append(WholeNumberFactorization(number))
	if 'Can\'t factorize the whole number zero.' in factorizations: return 'Can\'t factorize the whole number zero.'
	factors = []
	for factorization in factorizations:
		if factorization==[]: continue
		counter = 0
		lastPrimeNumber = factorization[0]
		isInFactors = False
		for primeNumber in factorization:
			if WholeNumbersRelation(primeNumber, lastPrimeNumber)=='=': counter+=1
			else:
				isInFactors = False
				for factor in factors:
					if WholeNumbersRelation(lastPrimeNumber, factor[0])=='=':
						isInFactors = True
					if isInFactors and counter>factor[1]:
						factors.remove(factor)
						factors.append((lastPrimeNumber, counter))
						break
				if isInFactors==False: factors.append((lastPrimeNumber, counter))
				counter = 1
				lastPrimeNumber = primeNumber
		isInFactors = False
		for factor in factors:
			if WholeNumbersRelation(lastPrimeNumber, factor[0])=='=':
				isInFactors = True
			if isInFactors and counter>factor[1]:
				factors.remove(factor)
				factors.append((lastPrimeNumber, counter))
		if isInFactors==False: factors.append((lastPrimeNumber, counter))
	if factors==[]: return WholeNumber(figures[1])
	expression = []
	for factor in factors:
		expression.append(factor[0])
		if factor[1]!=1:
			expression.append('^')
			expression.append(WholeNumber(str(factor[1])))
		expression.append('*')
	expression.pop(-1)
	return SolveShortWholeNumbersExpression(expression)

def CheckFigures(figures:str) -> bool:
	if type(figures)!=str: return False
	if len(figures)<2: return False
	for figure0 in range(len(figures)):
		for figure1 in range(len(figures)):
			if (figures[figure0]==figures[figure1] and figure0!=figure1):
				return False
	return True

def SetFigures(figuresToSet:str):
	global figures
	if CheckFigures(figuresToSet): figures = figuresToSet

def WholeNumberConvertBase(wholeNumber:WholeNumber, currentBaseFigures:str, newBaseFigures:str) -> WholeNumber:
	if type(wholeNumber)!=WholeNumber: exit(code='E27')
	if not (CheckFigures(currentBaseFigures) and CheckFigures(newBaseFigures)): exit(code='E28')
	global figures
	if currentBaseFigures==newBaseFigures: return wholeNumber
	if len(currentBaseFigures)==len(newBaseFigures):
		numberConverted = ''
		for figure in wholeNumber.number: numberConverted+=newBaseFigures[currentBaseFigures.index(figure)]
		currentFigures = figures
		figures = newBaseFigures
		wholeNumberConverted = WholeNumber(numberConverted)
		figures = currentFigures
		return wholeNumberConverted
	if len(currentBaseFigures)>len(newBaseFigures):
		numberConverted = ''
		quotient = wholeNumber
		currentFigures = figures
		figures = currentBaseFigures
		while WholeNumbersRelation(quotient, WholeNumber(currentBaseFigures[0]))!='=':
			result = WholeNumbersDivision(quotient, WholeNumber(currentBaseFigures[len(newBaseFigures)]))
			if type(result)==tuple:
				quotient = result[0]
				numberConverted = result[1].number+numberConverted
			else:
				quotient = result
				numberConverted = currentBaseFigures[0]+numberConverted
		figuresWanted = ''
		for index in range(len(newBaseFigures)): figuresWanted+=currentBaseFigures[index]
		numberConverted = WholeNumberConvertBase(WholeNumber(numberConverted), figuresWanted, newBaseFigures).number
		figures = newBaseFigures
		wholeNumberConverted = WholeNumber(numberConverted)
		figures = currentFigures
		return wholeNumberConverted
	figuresConverted = ''
	for figure in wholeNumber.number: figuresConverted+=newBaseFigures[currentBaseFigures.index(figure)]
	currentFigures = figures
	figures = newBaseFigures
	wholeNumberConverted = WholeNumber(newBaseFigures[0])
	for index in range(len(figuresConverted)): wholeNumberConverted = WholeNumbersAddition(wholeNumberConverted, WholeNumbersMultiplication(WholeNumber(figuresConverted[index]), WholeNumbersExponentiation(WholeNumber(newBaseFigures[len(currentBaseFigures)]), WholeNumber(newBaseFigures[len(figuresConverted)-1-index]))))
	figures = currentFigures
	return wholeNumberConverted