#ifndef LEXER_LEXER_H
#define LEXER_LEXER_H

#include "InputLibrary/Input.h"
#include "NumberSystem/NumberSystem.h"
#include <string>
#include <unordered_set>
#include <vector>

class TokenInformation;
enum class NumberSystem;
enum class Token;

class Lexer
{
public:
	explicit Lexer(std::string const & inputFileName);
	explicit Lexer(std::istream & is);
	bool GetNextTokenInformation(TokenInformation & tokenInformation);

private:
	static std::vector<std::string> const SCANNER_DELIMITERS;
	static NumberSystem const DEFAULT_NUMBER_SYSTEM;
	static std::unordered_set<std::string> const DELIMITERS_TO_SKIP;

	static bool DetermineScannedStringToken(
		std::string const & scannedString, Token & token, std::unordered_set<std::string> const & customTypes
	);
	static bool IsIdentifier(std::string const & str);
	static bool IsDigit(char ch, NumberSystem numberSystem = DEFAULT_NUMBER_SYSTEM);
	static bool IsInteger(
			std::string const & str,
			size_t fromIndex,
			size_t & failIndex,
			std::string & goodString,
			NumberSystem numberSystem = DEFAULT_NUMBER_SYSTEM
	);
	static bool DetermineNumberToken(std::string const & scannedString, Token & token);
	static bool DetermineDelimiterToken(std::string const & delimiterString, Token & token);
	static bool TryToAddLiteralToken(std::string const & delimiterString, Token & token);
	static bool TryToAddCommentToken(std::string const & delimiterString, Token & token);

	Input m_input;
	std::vector<TokenInformation> m_tokenInformations;
	std::unordered_set<std::string> m_customTypes;
	bool m_endOfFileReached = false;

	bool PopNextTokenInformation(TokenInformation & tokenInformation);
	bool DetermineNextTokenInformation(TokenInformation & tokenInformation);
	bool TryToCreateComment(std::string const & delimiterString, std::string & comment);
	bool TryToCreateLiteral(std::string const & delimiterString, std::string & literal);
	bool NeedMoreScanning(std::string const & scannedString, std::string const & delimiter);
};

#endif
