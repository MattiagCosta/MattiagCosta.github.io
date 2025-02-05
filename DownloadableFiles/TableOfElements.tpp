#include "TableOfElements.h"

template<typename elementDatatype>
TableOfElements<elementDatatype>::TableOfElements(validInt numberOfRows, validInt numberOfColumns){
	if(numberOfRows==0){ numberOfRows = 1; }
	if(numberOfColumns==0){ numberOfColumns = 1; }

	this->numberOfRows = 0;
	this->numberOfColumns = 0;
	Resize(numberOfRows, numberOfColumns);
	this->numberOfRows = numberOfRows;
	this->numberOfColumns = numberOfColumns;
}

template<typename elementDatatype>
void TableOfElements<elementDatatype>::Resize(validInt newNumberOfRows, validInt newNumberOfColumns){
	if(newNumberOfRows==0){ newNumberOfRows = 1; }
	if(newNumberOfColumns==0){ newNumberOfColumns = 1; }

	table.resize(newNumberOfRows);
	for(int i = 0; i<newNumberOfRows; i++){
		table[i].resize(newNumberOfColumns);
	}

	numberOfRows = newNumberOfRows;
	numberOfColumns = newNumberOfColumns;
}

template<typename elementDatatype>
validInt TableOfElements<elementDatatype>::GetNumberOfRows(){ return numberOfRows; }

template<typename elementDatatype>
validInt TableOfElements<elementDatatype>::GetNumberOfColumns(){ return numberOfColumns; }

template<typename elementDatatype>
elementDatatype TableOfElements<elementDatatype>::AccessCell(validInt row, validInt column){
	if(row>=numberOfRows){ row = numberOfRows-1; }
	if(column>=numberOfColumns){ column = numberOfColumns-1; }
	return table[row][column];
}

template<typename elementDatatype>
void TableOfElements<elementDatatype>::SetCell(validInt row, validInt column, elementDatatype element){
	if(row>=numberOfRows){ row = numberOfRows-1; }
	if(column>=numberOfColumns){ column = numberOfColumns-1; }
	table[row][column] = element;
}

template<typename elementDatatype>
TableOfElements<elementDatatype> TableOfElements<elementDatatype>::SubTable(validInt fromRow, validInt fromColumn, validInt toRow, validInt toColumn){
	if(
		toRow<fromRow || toColumn<fromColumn
		|| fromRow>=numberOfRows || fromColumn>=numberOfColumns
		|| toRow>=numberOfRows || toColumn>=numberOfColumns
		){ return *this; }

	TableOfElements<elementDatatype> subTable(toRow-fromRow+1, toColumn-fromColumn+1);
	
	for(validInt row = fromRow; row<=toRow; row++){
		for(validInt column = fromColumn; column<=toColumn; column++){
			subTable.SetCell(row-fromRow, column-fromColumn, this->table[row][column]);
		}
	}

	return subTable;
}

template<typename elementDatatype>
void TableOfElements<elementDatatype>::InsertRow(validInt atRow){
	if(atRow>numberOfRows){ atRow = numberOfRows; }

	Resize(numberOfRows+1, numberOfColumns);

	for(validInt row = numberOfRows-1; row>atRow; row--){
		table[row] = table[row-1];
	}
}

template<typename elementDatatype>
void TableOfElements<elementDatatype>::InsertColumn(validInt atColumn){
	if(atColumn>numberOfColumns){ atColumn = numberOfColumns; }

	Resize(numberOfRows, numberOfColumns+1);

	for(validInt row = 0; row<numberOfRows; row++){
		for(validInt column = numberOfColumns-1; column>atColumn; column--){
			table[row][column] = table[row][column-1];
		}
	}
}

template<typename elementDatatype>
void TableOfElements<elementDatatype>::Print(){
	std::cout << "\n\t|";
	for(validInt column = 0; column<numberOfColumns; column++){
		std::cout << "\t" << column;
	}
	std::cout << "\n\t|\n";
	for(validInt row = 0; row<numberOfRows; row++){
		std::cout << row <<"\t|";
		for(validInt column = 0; column<numberOfColumns; column++){
			std::cout << "\t" << table[row][column];
		}
		std::cout << "\n";
	}
}