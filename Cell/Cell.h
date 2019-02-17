#ifndef LRPARSER_CELL_H
#define LRPARSER_CELL_H

#include <utility>
#include "../Symbol/Symbol.h"

class Cell
{
public:
	Cell(Symbol symbol, size_t rowIndex, size_t columnIndex)
		: symbol(std::move(symbol))
		, rowIndex(rowIndex)
		, columnIndex(columnIndex)
	{

	}

	Symbol symbol;
	size_t rowIndex;
	size_t columnIndex;

	bool operator==(const Cell & other) const
	{
		return symbol == other.symbol && rowIndex == other.rowIndex && columnIndex == other.columnIndex;
	}
};

#endif
