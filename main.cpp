#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <iterator>
#include <queue>
#include <algorithm>
#include <stack>
#include "InputLibrary/Input.h"
#include "LexerLibrary/Lexer.h"
#include "Symbol/Symbol.h"
#include "Cell/Cell.h"
#include "Collapse/Collapse.h"
#include "LexerLibrary/TokenLibrary/TokenInformation/TokenInformation.h"

int const REQUIRED_ARGC = 2;
std::string const NO_ARGUMENTS_ERROR = "usage: ./LLParser <rule> <input>";

std::string const AUGMENT_NONTERMINAL = "Augment";
std::string const END_OF_FILE_TERMINAL = "End of file";

std::unordered_map<std::string, std::unordered_set<size_t>> nonterminalsToRowIndexes;
std::map<size_t, std::map<size_t, Symbol>> rules;
std::unordered_map<size_t, Collapse> collapses;

void ParseNonterminalDeclaration(Input & input, std::string & nonterminal)
{
	if (!input.ReadUntilCharacters({ '-' }, nonterminal))
	{
		throw std::runtime_error(
			nonterminal.empty()
				? "Nonterminal declaration expected"
				: "Character '-' expected after nonterminal declaration"
		);
	}
	input.SkipArgument<char>();
}

bool TryToParseSymbol(Input & input, char expectedLeftBorder, char expectedRightBorder, Symbol & symbol)
{
	Symbol possibleSymbol;
	char nextCharacter;
	if (input.GetNextCharacter(nextCharacter) && nextCharacter == expectedLeftBorder)
	{
		if (!input.ReadUntilCharacters({ expectedRightBorder }, possibleSymbol))
		{
			throw std::runtime_error(
				std::string("Symbol parsing: ")
					+ input.GetFileName() + ": "
					+ "(" + std::to_string(input.GetPosition().GetLine()) + ","
					+ std::to_string(input.GetPosition().GetColumn()) + ")" + ": "
					+ "'" + std::string(1, expectedRightBorder) + "'" + " expected"
			);
		}
		input.SkipArgument<char>();
		possibleSymbol += expectedRightBorder;
		symbol = std::move(possibleSymbol);
		return true;
	}
	return false;
}

void ReadNonterminalSequence(
	Input & input,
	std::map<size_t, Symbol> & nonterminalSequence,
	std::string const & mainNonterminal,
	bool & needAugment
)
{
	size_t index = 0;
	while (!input.IsEndOfLine())
	{
		nonterminalSequence[index] = Symbol();
		if (!TryToParseSymbol(input, Symbol::TERMINAL_LEFT_BORDER, Symbol::TERMINAL_RIGHT_BORDER, nonterminalSequence[index])
			&& !TryToParseSymbol(input, Symbol::NONTERMINAL_LEFT_BORDER, Symbol::NONTERMINAL_RIGHT_BORDER, nonterminalSequence[index]))
		{
			throw std::runtime_error(
				std::string("Sequence string splitting: ")
					+ input.GetFileName() + ": "
					+ "(" + std::to_string(input.GetPosition().GetLine()) + ","
					+ std::to_string(input.GetPosition().GetColumn()) + ")" + ": "
					+ "'" + std::string(1, Symbol::NONTERMINAL_LEFT_BORDER) + "'" + " or "
					+ "'" + std::string(1, Symbol::TERMINAL_LEFT_BORDER) + "'"
					+ " expected"
			);
		}
		if (nonterminalSequence[index].IsValueEquals(mainNonterminal))
		{
			needAugment = true;
		}
		++index;
	}
}

void ReadRule(
	std::string const & inputFileName,
	std::string & mainNonterminal,
	bool & needAugment
)
{
	Input inputFile(inputFileName);
	while (!inputFile.IsEndOfStream())
	{
		std::string nonterminal;
		ParseNonterminalDeclaration(inputFile, nonterminal);

		if (mainNonterminal.empty())
		{
			mainNonterminal = nonterminal;
		}

		size_t rowIndex = static_cast<size_t>(inputFile.GetPosition().GetLine());
		nonterminalsToRowIndexes[nonterminal].emplace(rowIndex);

		ReadNonterminalSequence(inputFile, rules[rowIndex], mainNonterminal, needAugment);

		collapses[rowIndex].ruleName = nonterminal;
		for (auto const & indexToSymbol : rules[rowIndex])
		{
			collapses[rowIndex].sequence.emplace_back(indexToSymbol.second);
		}

		inputFile.SkipLine();
	}
}

void AugmentRule(std::string & mainNonterminal)
{
	Symbol nonterminal;
	Symbol::CreateNonterminal(mainNonterminal, nonterminal);
	rules[0][0] = nonterminal;
	nonterminalsToRowIndexes[AUGMENT_NONTERMINAL].emplace(0);
	mainNonterminal = AUGMENT_NONTERMINAL;
	collapses[0].ruleName = mainNonterminal;
	collapses[0].sequence.emplace_back(nonterminal);
}

void AddEndOfFileToken(std::string const & nonterminal)
{
	std::unordered_set<size_t> & nonterminalRowIndexes = nonterminalsToRowIndexes[nonterminal];
	for (size_t rowIndex : nonterminalRowIndexes)
	{
		std::map<size_t, Symbol> & sequence = rules[rowIndex];

		Symbol terminal;
		Symbol::CreateTerminal(END_OF_FILE_TERMINAL, terminal);
		sequence[sequence.size()] = terminal;
		collapses[rowIndex].sequence.emplace_back(terminal);
	}
}

std::string GetNonterminalValue(size_t rowIndexToFind)
{
	for (auto const & nonterminalToRowIndexes : nonterminalsToRowIndexes)
	{
		std::string const & nonterminal = nonterminalToRowIndexes.first;
		std::unordered_set<size_t> const & rowIndexes = nonterminalToRowIndexes.second;

		for (size_t rowIndex : rowIndexes)
		{
			if (rowIndex == rowIndexToFind)
			{
				return nonterminal;
			}
		}
	}
	return "";
}

void WriteRule(
	std::string const & outputFileName,
	std::string const & mainNonterminal
)
{
	std::ofstream outputFile(outputFileName);

	for (auto const & rule : rules)
	{
		size_t rowIndex = rule.first;
		std::map<size_t, Symbol> const & sequence = rule.second;

		outputFile << GetNonterminalValue(rowIndex) << "-";
		for (auto const & element : sequence)
		{
			outputFile << element.second;
		}
		outputFile << "\n";
	}
}

std::unordered_set<std::string> GetNextTerminalsExceptRow(std::string const & nonterminal, size_t exceptRow, size_t exceptColumn);

std::unordered_set<size_t> globalRowIndexBlacklist { };
std::map<std::string, std::vector<Cell>> GetCellsFirsts(Cell const & cell)
{
	std::map<std::string, std::vector<Cell>> result { };
	std::unordered_set<size_t> rowIndexBlacklist { };
	result[cell.symbol] = { cell };
	if (cell.symbol.IsNonterminal())
	{
		std::unordered_set<size_t> const & rowIndexes = nonterminalsToRowIndexes.at(cell.symbol.GetValue());
		for (size_t rowIndex : rowIndexes)
		{
			if (rowIndexBlacklist.find(rowIndex) != rowIndexBlacklist.end() || globalRowIndexBlacklist.find(rowIndex) != globalRowIndexBlacklist.end())
			{
				Cell cell1(rules.at(rowIndex).at(0), rowIndex, 0);
				if (std::find(result[rules.at(rowIndex).at(0)].begin(), result[rules.at(rowIndex).at(0)].end(), cell1) == result[rules.at(rowIndex).at(0)].end())
				{
					result[rules.at(rowIndex).at(0)].emplace_back(cell1);
				}
				continue;
			}
			Symbol const & firstSymbol = rules.at(rowIndex).at(0);
			if (firstSymbol == "<e>")
			{
				if (cell.columnIndex == rules.at(cell.rowIndex).size() - 1)
				{
					std::unordered_set<std::string> const & nextTerminals =
						GetNextTerminalsExceptRow(GetNonterminalValue(cell.rowIndex), cell.rowIndex, cell.columnIndex);
					for (std::string const & nextTerminal : nextTerminals)
					{
						result[nextTerminal].emplace_back(Cell("R" + std::to_string(rowIndex), SIZE_MAX, SIZE_MAX));
					}
				}
				else
				{
					rowIndexBlacklist.emplace(cell.rowIndex);
					globalRowIndexBlacklist.emplace(cell.rowIndex);
					Cell next = Cell(rules.at(cell.rowIndex).at(cell.columnIndex + 1), cell.rowIndex, cell.columnIndex + 1);
					std::map<std::string, std::vector<Cell>> const & cellsFirsts = GetCellsFirsts(next);
					globalRowIndexBlacklist.erase(cell.rowIndex);
					for (auto const & cellFirsts : cellsFirsts)
					{
						result[cellFirsts.first].emplace_back(Cell("R" + std::to_string(rowIndex), SIZE_MAX, SIZE_MAX));
					}
				}
			}
			else
			{
				rowIndexBlacklist.emplace(rowIndex);
				globalRowIndexBlacklist.emplace(rowIndex);
				std::map<std::string, std::vector<Cell>> resultParts = GetCellsFirsts(Cell(firstSymbol, rowIndex, 0));
				//globalRowIndexBlacklist.erase(rowIndex);
				for (auto const & resultPart : resultParts)
				{
					for (auto const & cell1 : resultPart.second)
					{
						if (std::find(result[resultPart.first].begin(), result[resultPart.first].end(), cell1) == result[resultPart.first].end())
						{
							result[resultPart.first].emplace_back(cell1);
						}
					}
				}
			}
		}
	}
	return result;
}

std::unordered_set<std::string> GetNextTerminalsExceptRow(std::string const & nonterminal, size_t exceptRow, size_t exceptColumn)
{
	std::unordered_set<std::string> result;
	for (auto const & rule : rules)
	{
		size_t rowIndex = rule.first;
		for (auto const & columnIndexToSymbol : rule.second)
		{
			size_t columnIndex = columnIndexToSymbol.first;
			if (rowIndex == exceptRow && columnIndex == exceptColumn)
			{
				continue;
			}
			Symbol const & symbol = columnIndexToSymbol.second;

			if (symbol.IsValueEquals(nonterminal))
			{
				if (columnIndex == rules.at(rowIndex).size() - 1)
				{
					std::string const & newNonterminal = GetNonterminalValue(rowIndex);
					return GetNextTerminalsExceptRow(newNonterminal, rowIndex, columnIndex);
				}
				else
				{
					Symbol const & nextSymbol = rules.at(rowIndex).at(columnIndex + 1);
					std::map<std::string, std::vector<Cell>> cellsFirsts =
						GetCellsFirsts(Cell(nextSymbol, rowIndex, columnIndex + 1));
					for (auto const & cellFirsts : cellsFirsts)
					{
						result.emplace(cellFirsts.first);
					}
				}
			}
		}
	}
	return result;
}

void WriteTable(
	std::string const & outputFileName,
	std::vector<std::pair<std::vector<Cell>, std::map<std::string, std::vector<Cell>>>> const & table
)
{
	std::ofstream outputFile(outputFileName);

	for (std::pair<std::vector<Cell>, std::map<std::string, std::vector<Cell>>> const & tableRow : table)
	{
		std::vector<Cell> const & from = tableRow.first;
		std::map<std::string, std::vector<Cell>> const & bysAndTos = tableRow.second;

		for (Cell const & cell : from)
		{
			outputFile << cell.symbol;
			if (cell.rowIndex != SIZE_MAX || cell.columnIndex != SIZE_MAX)
			{
				outputFile << "(" << std::to_string(cell.rowIndex) << "," << std::to_string(cell.columnIndex + 1) << ")";
			}
			outputFile << ",";
		}
		outputFile << ":\n";

		for (auto const & byAndTo : bysAndTos)
		{
			std::string const & by = byAndTo.first;
			std::vector<Cell> const & to = byAndTo.second;

			outputFile << "\t" << by << ": ";

			for (Cell const & cell : to)
			{
				outputFile << cell.symbol;
				if (cell.rowIndex != SIZE_MAX || cell.columnIndex != SIZE_MAX)
				{
					outputFile << "(" << std::to_string(cell.rowIndex) << "," << std::to_string(cell.columnIndex + 1) << ")";
				}
				outputFile << ",";
			}
			outputFile << "\n";
		}
		outputFile << "\n";
	}
}

bool GetTableIndex(
	std::vector<std::pair<std::vector<Cell>, std::map<std::string, std::vector<Cell>>>> const & table,
	std::vector<Cell> const & toCells,
	size_t & result
)
{
	for (size_t i = 0; i < table.size(); ++i)
	{
		if (table[i].first == toCells)
		{
			result = i;
			return true;
		}
	}
}

int main(int argc, char * argv[])
{
	if (argc - 1 < REQUIRED_ARGC)
	{
		std::cerr << NO_ARGUMENTS_ERROR << "\n";
		return EXIT_FAILURE;
	}

	std::string inputFileName = argv[1];
	std::string mainNonterminal;
	bool needAugment = false;

	ReadRule(argv[1], mainNonterminal, needAugment);

	size_t firstRowIndex = 1;
	if (needAugment)
	{
		firstRowIndex = 0;
		AugmentRule(mainNonterminal);
	}
	AddEndOfFileToken(mainNonterminal);

	std::vector<std::vector<Cell>> blacklist { };
	std::queue<std::vector<Cell>> unresolvedCellsQueue;

	std::vector<std::pair<std::vector<Cell>, std::map<std::string, std::vector<Cell>>>> table;

	Symbol mainNonterminalSymbol;
	Symbol::CreateNonterminal(mainNonterminal, mainNonterminalSymbol);
	std::pair<std::vector<Cell>, std::map<std::string, std::vector<Cell>>> firstTableRow =
		std::make_pair(
			std::vector<Cell>({ Cell(Symbol("Start"), SIZE_MAX, SIZE_MAX) }),
			std::map<std::string, std::vector<Cell>>({{ mainNonterminalSymbol, { Cell(Symbol("OK"), SIZE_MAX, SIZE_MAX) }}})
		);
	Cell newCell(rules[firstRowIndex][0], firstRowIndex, 0);
	std::map<std::string, std::vector<Cell>> newCellFirsts = GetCellsFirsts(newCell);
	globalRowIndexBlacklist.clear();
	firstTableRow.second.insert(newCellFirsts.begin(), newCellFirsts.end());
	table.emplace_back(firstTableRow);

	for (auto const & newCellFirstsElement : newCellFirsts)
	{
		if (newCellFirstsElement.second.front().rowIndex != SIZE_MAX && newCellFirstsElement.second.front().columnIndex != SIZE_MAX)
		{
			unresolvedCellsQueue.push(newCellFirstsElement.second);
		}
		blacklist.emplace_back(newCellFirstsElement.second);
	}

	while (!unresolvedCellsQueue.empty())
	{
		std::vector<Cell> const & unresolvedCells = unresolvedCellsQueue.front();
		std::map<std::string, std::vector<Cell>> totalCellsFirsts;
		for (Cell const & unresolvedCell : unresolvedCells)
		{
			if (unresolvedCell.columnIndex == rules.at(unresolvedCell.rowIndex).size() - 1)
			{
				std::unordered_set<std::string> const & nextTerminals =
					GetNextTerminalsExceptRow(GetNonterminalValue(unresolvedCell.rowIndex), unresolvedCell.rowIndex, unresolvedCell.columnIndex);
				for (std::string const & nextTerminal : nextTerminals)
				{
					totalCellsFirsts[nextTerminal].emplace_back(Cell(Symbol("R" + std::to_string(unresolvedCell.rowIndex)), SIZE_MAX, SIZE_MAX));
				}
			}
			else
			{
				Symbol const & nextSymbol = rules.at(unresolvedCell.rowIndex).at(unresolvedCell.columnIndex + 1);
				if (nextSymbol.IsValueEquals(END_OF_FILE_TERMINAL))
				{
					totalCellsFirsts[nextSymbol].emplace_back(Cell(Symbol("R" + std::to_string(unresolvedCell.rowIndex)), SIZE_MAX, SIZE_MAX));
				}
				else
				{
					std::map<std::string, std::vector<Cell>> const & cellsFirsts =
						GetCellsFirsts(Cell(nextSymbol, unresolvedCell.rowIndex, unresolvedCell.columnIndex + 1));
					globalRowIndexBlacklist.clear();
					for (auto const & cellFirsts : cellsFirsts)
					{
						totalCellsFirsts[cellFirsts.first].insert(totalCellsFirsts[cellFirsts.first].end(), cellFirsts.second.begin(), cellFirsts.second.end());

						if (cellFirsts.second.front().rowIndex != SIZE_MAX && cellFirsts.second.front().columnIndex != SIZE_MAX && std::find(blacklist.begin(), blacklist.end(), cellFirsts.second) == blacklist.end())
						{
							unresolvedCellsQueue.push(cellFirsts.second);
						}
					}
				}
			}
		}
		table.emplace_back(std::make_pair(unresolvedCells, totalCellsFirsts));
		blacklist.emplace_back(unresolvedCells);
		unresolvedCellsQueue.pop();
	}

	//WriteRule("output", mainNonterminal);
	WriteTable("output", table);
	//
	std::stack<std::vector<Cell>> stack1 { };
	stack1.push(std::vector<Cell>({ Cell(Symbol("Start"), SIZE_MAX, SIZE_MAX) }));

	Lexer lexer(argv[2]);

	std::vector<std::string> words;
	std::vector<std::string> sourceWords;
	TokenInformation tokenInformation;
	while (lexer.GetNextTokenInformation(tokenInformation))
	{
		words.emplace_back(TokenExtensions::ToString(tokenInformation.GetToken()));
		sourceWords.emplace_back(tokenInformation.GetTokenStreamString().string);
	}
	for (std::string & word : words)
	{
		word = "[" + word + "]";
	}

	size_t currentRowIndex = 0;
	size_t currentWordIndex = SIZE_MAX;
	bool failure = false;
	while (true)
	{
		size_t nextWordIndex = currentWordIndex + 1;
		std::string const & word = words[nextWordIndex];
		std::pair<std::vector<Cell>, std::map<std::string, std::vector<Cell>>> const & tableRow = table[currentRowIndex];
		std::vector<Cell> const & fromCells = tableRow.first;
		std::map<std::string, std::vector<Cell>> const & references = tableRow.second;

		if (references.find(word) == references.end())
		{
			std::cerr << "Ошибка!\n";
			std::cout << "Правильная часть: ";
			for (size_t i = 0; i < nextWordIndex && i < sourceWords.size(); ++i)
			{
				std::cout << sourceWords[i] << " ";
			}
			std::cout << "\n";
			failure = true;
			break;
		}
		std::vector<Cell> const & toCells = references.at(word);
		size_t i = 0;
		bool found = GetTableIndex(table, toCells, i);
		if (!found)
		{
			std::string const & collapseString = toCells.front().symbol;
			if (collapseString == "OK")
			{
				break;
			}
			size_t collapseId = stoul(collapseString.substr(1, collapseString.size() - 1));
			Collapse const & collapse = collapses[collapseId];
			if (collapse.sequence.front() != "<e>")
			{
				if (words.size() == collapse.sequence.size())
				{
					++currentWordIndex;
				}
				if (collapse.sequence.size() - 1 > currentWordIndex)
				{
					std::cout << "Ошибка!\n";
					std::cout << "Правильная часть: ";
					for (size_t i = 0; i < nextWordIndex && i < sourceWords.size(); ++i)
					{
						std::cout << sourceWords[i] << " ";
					}
					std::cout << "\n";
					failure = true;
					break;
				}
				bool fail = false;
				for (size_t i = collapse.sequence.size() - 1; i != SIZE_MAX ; --i)
				{
					if (words[currentWordIndex] != collapse.sequence[i])
					{
						std::cout << "Ошибка!\n";
						std::cout << "Правильная часть: ";
						for (size_t i = 0; i < nextWordIndex && i < sourceWords.size(); ++i)
						{
							std::cout << sourceWords[i] << " ";
						}
						std::cout << "\n";
						failure = true;
						fail = true;
						break;
					}
					--currentWordIndex;
				}
				if (fail)
				{
					break;
				}
				for (size_t i = 0; i < collapse.sequence.size(); ++i)
				{
					words.erase(words.begin() + currentWordIndex + 1);
					if (stack1.size() != 1)
					{
						stack1.pop();
					}
				}
			}
			words.insert(words.begin() + currentWordIndex + 1, "<" + collapse.ruleName + ">");
			GetTableIndex(table, stack1.top(), currentRowIndex);
		}
		else
		{
			stack1.push(table.at(i).first);
			currentRowIndex = i;
			++currentWordIndex;
		}
	}
	if (!failure)
	{
		std::cout << "Успешно!\n";
		for (std::string const & word : sourceWords)
		{
			std::cout << word << " ";
		}
		std::cout << "\n";
	}

	return EXIT_SUCCESS;
}
