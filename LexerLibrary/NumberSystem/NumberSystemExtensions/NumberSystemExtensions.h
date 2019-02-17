#ifndef LEXER_NUMBERSYSTEMEXTENSIONS_H
#define LEXER_NUMBERSYSTEMEXTENSIONS_H

#include <set>
#include <unordered_map>

enum class NumberSystem;

class NumberSystemExtensions
{
public:
	static void CreateAvailableCharacters(NumberSystem numberSystem, std::set<char> & availableCharacters);
	static bool CreateFromString(std::string const & str, NumberSystem & numberSystem);
	static unsigned int ToUInt(NumberSystem numberSystem);

private:
	static NumberSystem const DEFAULT_NUMBER_SYSTEM;
	static std::set<char> const ALL_AVAILABLE_CHARACTERS;
	static std::set<char> const DEFAULT_NUMBER_SYSTEM_DIGITS;
	static std::unordered_map<std::string, NumberSystem> const STRING_TO_NUMBER_SYSTEM;
	static std::unordered_map<NumberSystem, unsigned int> const NUMBER_SYSTEM_TO_UINT;
};

#endif
