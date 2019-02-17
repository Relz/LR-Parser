#include "NumberSystemExtensions.h"
#include "../NumberSystem.h"

void NumberSystemExtensions::CreateAvailableCharacters(NumberSystem numberSystem, std::set<char> & availableCharacters)
{
	if (numberSystem == DEFAULT_NUMBER_SYSTEM)
	{
		availableCharacters = DEFAULT_NUMBER_SYSTEM_DIGITS;
		return;
	}
	auto goalIterator = ALL_AVAILABLE_CHARACTERS.begin();
	std::advance(goalIterator, ToUInt(numberSystem));
	availableCharacters = std::set<char>(ALL_AVAILABLE_CHARACTERS.begin(), goalIterator);
}

bool NumberSystemExtensions::CreateFromString(std::string const & str, NumberSystem & numberSystem)
{
	if (STRING_TO_NUMBER_SYSTEM.find(str) == STRING_TO_NUMBER_SYSTEM.end())
	{
		return false;
	}
	numberSystem = STRING_TO_NUMBER_SYSTEM.at(str);
	return true;
}

unsigned int NumberSystemExtensions::ToUInt(NumberSystem numberSystem)
{
	return NUMBER_SYSTEM_TO_UINT.at(numberSystem);
}

NumberSystem const NumberSystemExtensions::DEFAULT_NUMBER_SYSTEM = NumberSystem::TEN;

std::set<char> const NumberSystemExtensions::ALL_AVAILABLE_CHARACTERS {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};

std::set<char> const NumberSystemExtensions::DEFAULT_NUMBER_SYSTEM_DIGITS {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
};

std::unordered_map<std::string, NumberSystem> const NumberSystemExtensions::STRING_TO_NUMBER_SYSTEM {
	{ "2", NumberSystem::TWO },
	{ "3", NumberSystem::THREE },
	{ "4", NumberSystem::FOUR },
	{ "5", NumberSystem::FIVE },
	{ "6", NumberSystem::SIX },
	{ "7", NumberSystem::SEVEN },
	{ "8", NumberSystem::EIGHT },
	{ "9", NumberSystem::NINE },
	{ "10", NumberSystem::TEN },
	{ "11", NumberSystem::ELEVEN },
	{ "12", NumberSystem::TWELVE },
	{ "13", NumberSystem::THIRTEEN },
	{ "14", NumberSystem::FOURTEEN },
	{ "15", NumberSystem::FIFTEEN },
	{ "16", NumberSystem::SIXTEEN }
};

std::unordered_map<NumberSystem, unsigned int> const NumberSystemExtensions::NUMBER_SYSTEM_TO_UINT {
	{ NumberSystem::TWO, 2 },
	{ NumberSystem::THREE, 3 },
	{ NumberSystem::FOUR, 4 },
	{ NumberSystem::FIVE, 5 },
	{ NumberSystem::SIX, 6 },
	{ NumberSystem::SEVEN, 7 },
	{ NumberSystem::EIGHT, 8 },
	{ NumberSystem::NINE, 9 },
	{ NumberSystem::TEN, 10 },
	{ NumberSystem::ELEVEN, 11 },
	{ NumberSystem::TWELVE, 12 },
	{ NumberSystem::THIRTEEN, 13 },
	{ NumberSystem::FOURTEEN, 14 },
	{ NumberSystem::FIFTEEN, 15 },
	{ NumberSystem::SIXTEEN, 16 }
};
