#include "TokenExtensions.h"

bool TokenExtensions::CreateFromString(std::string const & str, Token & token)
{
	if (NAME_TO_TOKEN.find(str) == NAME_TO_TOKEN.end())
	{
		return false;
	}
	token = NAME_TO_TOKEN.at(str);
	return true;
}

bool TokenExtensions::TryToGetDelimiterToken(std::string const & str, Token & token)
{
	if (STRING_TO_DELIMITER_TOKEN.find(str) == STRING_TO_DELIMITER_TOKEN.end())
	{
		return false;
	}
	token = STRING_TO_DELIMITER_TOKEN.at(str);
	return true;
}

bool TokenExtensions::TryToGetKeywordToken(std::string const & str, Token & token)
{
	if (STRING_TO_KEYWORD_TOKEN.find(str) == STRING_TO_KEYWORD_TOKEN.end())
	{
		return false;
	}
	token = STRING_TO_KEYWORD_TOKEN.at(str);
	return true;
}

bool TokenExtensions::TryToGetTypeToken(
	std::string const & str, Token & token, std::unordered_set<std::string> const & customTypes)
{
	if (TYPES.find(str) == TYPES.end() && customTypes.find(str) == customTypes.end())
	{
		return false;
	}
	token = Token::TYPE;
	return true;
}

std::string TokenExtensions::ToString(Token token)
{
	return TOKEN_TO_NAME.find(token) == TOKEN_TO_NAME.end() ? "" : TOKEN_TO_NAME.at(token);
}

std::unordered_map<std::string, Token> const TokenExtensions::STRING_TO_DELIMITER_TOKEN {
	{ TokenConstant::Operator::Arithmetic::DIVISION, Token::DIVISION },
	{ TokenConstant::Operator::Arithmetic::MINUS, Token::MINUS },
	{ TokenConstant::Operator::Arithmetic::MULTIPLY, Token::MULTIPLY },
	{ TokenConstant::Operator::Arithmetic::PLUS, Token::PLUS },

	{ TokenConstant::Operator::Assignment::ASSIGNMENT, Token::ASSIGNMENT },
	{ TokenConstant::Operator::Assignment::PLUS_ASSIGNMENT, Token::PLUS_ASSIGNMENT },
	{ TokenConstant::Operator::Assignment::MINUS_ASSIGNMENT, Token::MINUS_ASSIGNMENT },
	{ TokenConstant::Operator::Assignment::MULTIPLY_ASSIGNMENT, Token::MULTIPLY_ASSIGNMENT },
	{ TokenConstant::Operator::Assignment::DIVISION_ASSIGNMENT, Token::DIVISION_ASSIGNMENT },

	{ TokenConstant::Operator::Comparison::EQUIVALENCE, Token::EQUIVALENCE },
	{ TokenConstant::Operator::Comparison::NOT_EQUIVALENCE, Token::NOT_EQUIVALENCE },
	{ TokenConstant::Operator::Comparison::MORE_OR_EQUIVALENCE, Token::MORE_OR_EQUIVALENCE },
	{ TokenConstant::Operator::Comparison::LESS_OR_EQUIVALENCE, Token::LESS_OR_EQUIVALENCE },
	{ TokenConstant::Operator::Comparison::MORE, Token::MORE },
	{ TokenConstant::Operator::Comparison::LESS, Token::LESS },

	{ TokenConstant::Separator::COLON, Token::COLON },
	{ TokenConstant::Separator::COMMA, Token::COMMA },
	{ TokenConstant::Separator::DOT, Token::DOT },
	{ TokenConstant::Separator::SEMICOLON, Token::SEMICOLON },

	{ TokenConstant::Parentheses::CURLY_BRACKET.LEFT, Token::LEFT_CURLY_BRACKET },
	{ TokenConstant::Parentheses::CURLY_BRACKET.RIGHT, Token::RIGHT_CURLY_BRACKET },
	{ TokenConstant::Parentheses::ROUND_BRACKET.LEFT, Token::LEFT_ROUND_BRACKET },
	{ TokenConstant::Parentheses::ROUND_BRACKET.RIGHT, Token::RIGHT_ROUND_BRACKET },
	{ TokenConstant::Parentheses::SQUARE_BRACKET.LEFT, Token::LEFT_SQUARE_BRACKET },
	{ TokenConstant::Parentheses::SQUARE_BRACKET.RIGHT, Token::RIGHT_SQUARE_BRACKET }
};

std::unordered_map<std::string, Token> const TokenExtensions::STRING_TO_KEYWORD_TOKEN {
	{ TokenConstant::Keyword::CLASS, Token::CLASS },
	{ TokenConstant::Keyword::CONSTRUCTOR, Token::CONSTRUCTOR },
	{ TokenConstant::Keyword::DO, Token::DO },
	{ TokenConstant::Keyword::EXTENDS, Token::EXTENDS },
	{ TokenConstant::Keyword::FOR, Token::FOR },
	{ TokenConstant::Keyword::GET, Token::GET },
	{ TokenConstant::Keyword::IMPLEMENTS, Token::IMPLEMENTS },
	{ TokenConstant::Keyword::NOT_INITIALIZED, Token::NOT_INITIALIZED },
	{ TokenConstant::Keyword::PRIVATE, Token::PRIVATE },
	{ TokenConstant::Keyword::PUBLIC, Token::PUBLIC },
	{ TokenConstant::Keyword::SET, Token::SET },
	{ TokenConstant::Keyword::RETURN, Token::RETURN },
	{ TokenConstant::Keyword::WHILE, Token::WHILE },
	{ TokenConstant::Keyword::IF, Token::IF },
	{ TokenConstant::Keyword::ELSE, Token::ELSE }
};

std::unordered_set<std::string> const TokenExtensions::TYPES {
	TokenConstant::CoreType::Complex::ARRAY,
	TokenConstant::CoreType::Number::DOUBLE,
	TokenConstant::CoreType::Number::FLOAT,
	TokenConstant::CoreType::Number::INTEGER,
	TokenConstant::CoreType::Complex::STRING,
	TokenConstant::CoreType::VOID
};

std::unordered_map<Token, std::string> const TokenExtensions::TOKEN_TO_NAME {
	{ Token::UNKNOWN, TokenConstant::Name::UNKNOWN },

	{ Token::DIVISION, TokenConstant::Name::Operator::Arithmetic::DIVISION },
	{ Token::MINUS, TokenConstant::Name::Operator::Arithmetic::MINUS },
	{ Token::MULTIPLY, TokenConstant::Name::Operator::Arithmetic::MULTIPLY },
	{ Token::PLUS, TokenConstant::Name::Operator::Arithmetic::PLUS },

	{ Token::PLUS_ASSIGNMENT, TokenConstant::Name::Operator::Assignment::PLUS_ASSIGNMENT },
	{ Token::MULTIPLY_ASSIGNMENT, TokenConstant::Name::Operator::Assignment::MULTIPLY_ASSIGNMENT },
	{ Token::MINUS_ASSIGNMENT, TokenConstant::Name::Operator::Assignment::MINUS_ASSIGNMENT },
	{ Token::DIVISION_ASSIGNMENT, TokenConstant::Name::Operator::Assignment::DIVISION_ASSIGNMENT },
	{ Token::ASSIGNMENT, TokenConstant::Name::Operator::Assignment::ASSIGNMENT },

	{ Token::EQUIVALENCE, TokenConstant::Name::Operator::Comparison::EQUIVALENCE },
	{ Token::NOT_EQUIVALENCE, TokenConstant::Name::Operator::Comparison::NOT_EQUIVALENCE },
	{ Token::MORE_OR_EQUIVALENCE, TokenConstant::Name::Operator::Comparison::MORE_OR_EQUIVALENCE },
	{ Token::LESS_OR_EQUIVALENCE, TokenConstant::Name::Operator::Comparison::LESS_OR_EQUIVALENCE },
	{ Token::MORE, TokenConstant::Name::Operator::Comparison::MORE },
	{ Token::LESS, TokenConstant::Name::Operator::Comparison::LESS },

	{ Token::CLASS, TokenConstant::Name::Keyword::CLASS },
	{ Token::CONSTRUCTOR, TokenConstant::Name::Keyword::CONSTRUCTOR },
	{ Token::DO, TokenConstant::Name::Keyword::DO },
	{ Token::EXTENDS, TokenConstant::Name::Keyword::EXTENDS },
	{ Token::FOR, TokenConstant::Name::Keyword::FOR },
	{ Token::WHILE, TokenConstant::Name::Keyword::WHILE },
	{ Token::GET, TokenConstant::Name::Keyword::GET },
	{ Token::IMPLEMENTS, TokenConstant::Name::Keyword::IMPLEMENTS },
	{ Token::NOT_INITIALIZED, TokenConstant::Name::Keyword::NOT_INITIALIZED },
	{ Token::PRIVATE, TokenConstant::Name::Keyword::PRIVATE },
	{ Token::PUBLIC, TokenConstant::Name::Keyword::PUBLIC },
	{ Token::RETURN, TokenConstant::Name::Keyword::RETURN },
	{ Token::SET, TokenConstant::Name::Keyword::SET },
	{ Token::IF, TokenConstant::Name::Keyword::IF },
	{ Token::ELSE, TokenConstant::Name::Keyword::ELSE },

	{ Token::INTEGER, TokenConstant::Name::INTEGER },
	{ Token::FLOAT, TokenConstant::Name::FLOAT },
	{ Token::EXPONENTIAL, TokenConstant::Name::EXPONENTIAL },

	{ Token::DOT, TokenConstant::Name::Separator::DOT },
	{ Token::COLON, TokenConstant::Name::Separator::COLON },
	{ Token::COMMA, TokenConstant::Name::Separator::COMMA },
	{ Token::SEMICOLON, TokenConstant::Name::Separator::SEMICOLON },

	{ Token::LEFT_CURLY_BRACKET, TokenConstant::Name::Parentheses::CURLY_BRACKET_LEFT },
	{ Token::RIGHT_CURLY_BRACKET, TokenConstant::Name::Parentheses::CURLY_BRACKET_RIGHT },
	{ Token::LEFT_ROUND_BRACKET, TokenConstant::Name::Parentheses::ROUND_BRACKET_LEFT },
	{ Token::RIGHT_ROUND_BRACKET, TokenConstant::Name::Parentheses::ROUND_BRACKET_RIGHT },
	{ Token::LEFT_SQUARE_BRACKET, TokenConstant::Name::Parentheses::SQUARE_BRACKET_LEFT },
	{ Token::RIGHT_SQUARE_BRACKET, TokenConstant::Name::Parentheses::SQUARE_BRACKET_RIGHT },

	{ Token::TYPE, TokenConstant::Name::TYPE },
	{ Token::IDENTIFIER, TokenConstant::Name::IDENTIFIER },
	{ Token::STRING_LITERAL, TokenConstant::Name::STRING_LITERAL },
	{ Token::CHARACTER_LITERAL, TokenConstant::Name::CHARACTER_LITERAL },
	{ Token::LINE_COMMENT, TokenConstant::Name::LINE_COMMENT },
	{ Token::BLOCK_COMMENT, TokenConstant::Name::BLOCK_COMMENT },

	{ Token::END_OF_FILE, TokenConstant::Name::END_OF_FILE }
};

std::unordered_map<std::string, Token> const TokenExtensions::NAME_TO_TOKEN {
		{ TokenConstant::Name::UNKNOWN, Token::UNKNOWN },

		{ TokenConstant::Name::Operator::Arithmetic::DIVISION, Token::DIVISION },
		{ TokenConstant::Name::Operator::Arithmetic::MINUS, Token::MINUS },
		{ TokenConstant::Name::Operator::Arithmetic::MULTIPLY, Token::MULTIPLY },
		{ TokenConstant::Name::Operator::Arithmetic::PLUS, Token::PLUS },

		{ TokenConstant::Name::Operator::Assignment::PLUS_ASSIGNMENT, Token::PLUS_ASSIGNMENT },
		{ TokenConstant::Name::Operator::Assignment::MULTIPLY_ASSIGNMENT, Token::MULTIPLY_ASSIGNMENT },
		{ TokenConstant::Name::Operator::Assignment::MINUS_ASSIGNMENT, Token::MINUS_ASSIGNMENT },
		{ TokenConstant::Name::Operator::Assignment::DIVISION_ASSIGNMENT, Token::DIVISION_ASSIGNMENT },
		{ TokenConstant::Name::Operator::Assignment::ASSIGNMENT, Token::ASSIGNMENT },

		{ TokenConstant::Name::Operator::Comparison::EQUIVALENCE, Token::EQUIVALENCE },
		{ TokenConstant::Name::Operator::Comparison::NOT_EQUIVALENCE, Token::NOT_EQUIVALENCE },
		{ TokenConstant::Name::Operator::Comparison::MORE_OR_EQUIVALENCE, Token::MORE_OR_EQUIVALENCE },
		{ TokenConstant::Name::Operator::Comparison::LESS_OR_EQUIVALENCE, Token::LESS_OR_EQUIVALENCE },
		{ TokenConstant::Name::Operator::Comparison::MORE, Token::MORE },
		{ TokenConstant::Name::Operator::Comparison::LESS, Token::LESS },

		{ TokenConstant::Name::Keyword::CLASS, Token::CLASS },
		{ TokenConstant::Name::Keyword::CONSTRUCTOR, Token::CONSTRUCTOR },
		{ TokenConstant::Name::Keyword::DO, Token::DO },
		{ TokenConstant::Name::Keyword::EXTENDS, Token::EXTENDS },
		{ TokenConstant::Name::Keyword::FOR, Token::FOR },
		{ TokenConstant::Name::Keyword::WHILE, Token::WHILE },
		{ TokenConstant::Name::Keyword::GET, Token::GET },
		{ TokenConstant::Name::Keyword::IMPLEMENTS, Token::IMPLEMENTS },
		{ TokenConstant::Name::Keyword::NOT_INITIALIZED, Token::NOT_INITIALIZED },
		{ TokenConstant::Name::Keyword::PRIVATE, Token::PRIVATE },
		{ TokenConstant::Name::Keyword::PUBLIC, Token::PUBLIC },
		{ TokenConstant::Name::Keyword::RETURN, Token::RETURN },
		{ TokenConstant::Name::Keyword::SET, Token::SET },
		{ TokenConstant::Name::Keyword::IF, Token::IF },
		{ TokenConstant::Name::Keyword::ELSE, Token::ELSE },

		{ TokenConstant::Name::INTEGER, Token::INTEGER },
		{ TokenConstant::Name::FLOAT, Token::FLOAT },
		{ TokenConstant::Name::EXPONENTIAL, Token::EXPONENTIAL },

		{ TokenConstant::Name::Separator::DOT, Token::DOT },
		{ TokenConstant::Name::Separator::COLON, Token::COLON },
		{ TokenConstant::Name::Separator::COMMA, Token::COMMA },
		{ TokenConstant::Name::Separator::SEMICOLON, Token::SEMICOLON },

		{ TokenConstant::Name::Parentheses::CURLY_BRACKET_LEFT, Token::LEFT_CURLY_BRACKET },
		{ TokenConstant::Name::Parentheses::CURLY_BRACKET_RIGHT, Token::RIGHT_CURLY_BRACKET },
		{ TokenConstant::Name::Parentheses::ROUND_BRACKET_LEFT, Token::LEFT_ROUND_BRACKET },
		{ TokenConstant::Name::Parentheses::ROUND_BRACKET_RIGHT, Token::RIGHT_ROUND_BRACKET },
		{ TokenConstant::Name::Parentheses::SQUARE_BRACKET_LEFT, Token::LEFT_SQUARE_BRACKET },
		{ TokenConstant::Name::Parentheses::SQUARE_BRACKET_RIGHT, Token::RIGHT_SQUARE_BRACKET },

		{ TokenConstant::Name::TYPE, Token::TYPE },
		{ TokenConstant::Name::IDENTIFIER, Token::IDENTIFIER },
		{ TokenConstant::Name::STRING_LITERAL, Token::STRING_LITERAL },
		{ TokenConstant::Name::CHARACTER_LITERAL, Token::CHARACTER_LITERAL },
		{ TokenConstant::Name::LINE_COMMENT, Token::LINE_COMMENT },
		{ TokenConstant::Name::BLOCK_COMMENT, Token::BLOCK_COMMENT },

		{ TokenConstant::Name::END_OF_FILE, Token::END_OF_FILE }
};
