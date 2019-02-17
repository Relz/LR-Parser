#ifndef TOKEN_CONSTANT_H
#define TOKEN_CONSTANT_H

#include "../Parenthesis/Parenthesis.h"
#include <regex>
#include <string>
#include <vector>

class TokenConstant
{
public:
	class Comment
	{
	public:
		static std::string const BLOCK_BEGINNING;
		static std::string const BLOCK_ENDING;
		static std::string const LINE;
	};

	class Operator
	{
	public:
		class Arithmetic
		{
		public:
			static std::string const DIVISION;
			static std::string const MINUS;
			static char const MINUS_CHARACTER;
			static std::string const MULTIPLY;
			static std::string const PLUS;
			static char const PLUS_CHARACTER;
		};

		class Assignment
		{
		public:
			static std::string const ASSIGNMENT;
			static std::string const DIVISION_ASSIGNMENT;
			static std::string const MINUS_ASSIGNMENT;
			static std::string const MULTIPLY_ASSIGNMENT;
			static std::string const PLUS_ASSIGNMENT;
		};

		class Comparison
		{
		public:
			static std::string const EQUIVALENCE;
			static std::string const NOT_EQUIVALENCE;
			static std::string const MORE_OR_EQUIVALENCE;
			static std::string const LESS_OR_EQUIVALENCE;
			static std::string const MORE;
			static std::string const LESS;
		};
	};

	class Keyword
	{
	public:
		static std::string const CLASS;
		static std::string const CONSTRUCTOR;
		static std::string const DO;
		static std::string const EXTENDS;
		static std::string const FOR;
		static std::string const GET;
		static std::string const IMPLEMENTS;
		static std::string const NOT_INITIALIZED;
		static std::string const PRIVATE;
		static std::string const PUBLIC;
		static std::string const RETURN;
		static std::string const SET;
		static std::string const WHILE;
		static std::string const IF;
		static std::string const ELSE;
	};

	class CoreType
	{
	public:
		class Number
		{
		public:
			static std::string const DOUBLE;
			static std::string const FLOAT;
			static std::string const INTEGER;
		};

		class Complex
		{
		public:
			static std::string const ARRAY;
			static std::string const STRING;
		};

		static std::string const VOID;
	};

	class Separator
	{
	public:
		static std::string const DOT;
		static char const DOT_CHARACTER;
		static std::string const COLON;
		static std::string const COMMA;
		static std::string const SEMICOLON;
		static char const EXPONENT_CHARACTER;
		static std::string const SPACE;
		static std::string const TAB;
		static std::string const END_OF_LINE_LF;
		static std::string const END_OF_LINE_CR;
		static char const UNDERSCORE_CHARACTER;
	};

	class Parentheses
	{
	public:
		static Parenthesis const CURLY_BRACKET;
		static Parenthesis const ROUND_BRACKET;
		static Parenthesis const SQUARE_BRACKET;
		static char const QUOTE_CHARACTER;
		static std::string const QUOTE_STRING;
		static char const DOUBLE_QUOTE_CHARACTER;
		static std::string const DOUBLE_QUOTE_STRING;
	};

	class Name
	{
	public:
		static std::string const UNKNOWN;

		class Operator
		{
		public:
			class Arithmetic
			{
			public:
				static std::string const DIVISION;
				static std::string const MINUS;
				static std::string const MULTIPLY;
				static std::string const PLUS;
			};

			class Assignment
			{
			public:
				static std::string const ASSIGNMENT;
				static std::string const DIVISION_ASSIGNMENT;
				static std::string const MINUS_ASSIGNMENT;
				static std::string const MULTIPLY_ASSIGNMENT;
				static std::string const PLUS_ASSIGNMENT;
			};

			class Comparison
			{
			public:
				static std::string const EQUIVALENCE;
				static std::string const NOT_EQUIVALENCE;
				static std::string const MORE_OR_EQUIVALENCE;
				static std::string const LESS_OR_EQUIVALENCE;
				static std::string const MORE;
				static std::string const LESS;
			};
		};

		class Keyword
		{
		public:
			static std::string const CLASS;
			static std::string const CONSTRUCTOR;
			static std::string const DO;
			static std::string const EXTENDS;
			static std::string const FOR;
			static std::string const GET;
			static std::string const IMPLEMENTS;
			static std::string const NOT_INITIALIZED;
			static std::string const PRIVATE;
			static std::string const PUBLIC;
			static std::string const RETURN;
			static std::string const SET;
			static std::string const WHILE;
			static std::string const IF;
			static std::string const ELSE;
		};

		static std::string const INTEGER;
		static std::string const FLOAT;
		static std::string const EXPONENTIAL;

		class Separator
		{
		public:
			static std::string const DOT;
			static std::string const COLON;
			static std::string const COMMA;
			static std::string const SEMICOLON;
		};

		class Parentheses
		{
		public:
			static std::string const CURLY_BRACKET_LEFT;
			static std::string const CURLY_BRACKET_RIGHT;
			static std::string const ROUND_BRACKET_LEFT;
			static std::string const ROUND_BRACKET_RIGHT;
			static std::string const SQUARE_BRACKET_LEFT;
			static std::string const SQUARE_BRACKET_RIGHT;
		};

		static std::string const TYPE;
		static std::string const IDENTIFIER;
		static std::string const STRING_LITERAL;
		static std::string const CHARACTER_LITERAL;
		static std::string const LINE_COMMENT;
		static std::string const BLOCK_COMMENT;

		static std::string const END_OF_FILE;
	};

	class Regex
	{
	public:
		static std::regex const IDENTIFIER;
	};
};

#endif
