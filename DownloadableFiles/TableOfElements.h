#ifndef TABLEOFELEMENTS_H
#define TABLEOFELEMENTS_H

#include <windows.h>
#include <vector>

#include <iostream>

typedef unsigned int validInt;

template<typename elementDatatype>
class TableOfElements{

	private:
	validInt numberOfRows;
	validInt numberOfColumns;
	std::vector<std::vector<elementDatatype>> table; // rows of cells
	
	public:

	TableOfElements(validInt numberOfRows, validInt numberOfColumns);

	void Resize(validInt newNumberOfRows, validInt newNumberOfColumns);

	validInt GetNumberOfRows();

	validInt GetNumberOfColumns();

	elementDatatype AccessCell(validInt row, validInt column);

	void SetCell(validInt row, validInt column, elementDatatype element);

	TableOfElements<elementDatatype> SubTable(validInt fromRow, validInt fromColumn, validInt toRow, validInt toColumn);

	void InsertRow(validInt atRow);

	void InsertColumn(validInt atColumn);

	void Print();

};

#include "TableOfElements.tpp"

#endif // TABLEOFELEMENTS_H