#include "TokenConstant.h"

std::string const TokenConstant::Comment::BLOCK_BEGINNING = "/*";
std::string const TokenConstant::Comment::BLOCK_ENDING = "*/";
std::string const TokenConstant::Comment::LINE = "//";

std::string const TokenConstant::Operator::Arithmetic::DIVISION = "/";
std::string const TokenConstant::Operator::Arithmetic::MINUS = "-";
char const TokenConstant::Operator::Arithmetic::MINUS_CHARACTER = '-';
std::string const TokenConstant::Operator::Arithmetic::MULTIPLY = "*";
std::string const TokenConstant::Operator::Arithmetic::PLUS = "+";
char const TokenConstant::Operator::Arithmetic::PLUS_CHARACTER = '+';

std::string const TokenConstant::Operator::Assignment::ASSIGNMENT = "=";
std::string const TokenConstant::Operator::Assignment::DIVISION_ASSIGNMENT = "/=";
std::string const TokenConstant::Operator::Assignment::MINUS_ASSIGNMENT = "-=";
std::string const TokenConstant::Operator::Assignment::MULTIPLY_ASSIGNMENT = "*=";
std::string const TokenConstant::Operator::Assignment::PLUS_ASSIGNMENT = "+=";

std::string const TokenConstant::Operator::Comparison::EQUIVALENCE = "==";
std::string const TokenConstant::Operator::Comparison::NOT_EQUIVALENCE = "!=";
std::string const TokenConstant::Operator::Comparison::MORE_OR_EQUIVALENCE = ">=";
std::string const TokenConstant::Operator::Comparison::LESS_OR_EQUIVALENCE = "<=";
std::string const TokenConstant::Operator::Comparison::MORE = ">";
std::string const TokenConstant::Operator::Comparison::LESS = "<";

std::string const TokenConstant::Keyword::CLASS = "class";
std::string const TokenConstant::Keyword::CONSTRUCTOR = "Constructor";
std::string const TokenConstant::Keyword::DO = "do";
std::string const TokenConstant::Keyword::EXTENDS = "extends";
std::string const TokenConstant::Keyword::FOR = "for";
std::string const TokenConstant::Keyword::GET = "get";
std::string const TokenConstant::Keyword::IMPLEMENTS = "implements";
std::string const TokenConstant::Keyword::NOT_INITIALIZED = "NULL";
std::string const TokenConstant::Keyword::PRIVATE = "private";
std::string const TokenConstant::Keyword::PUBLIC = "public";
std::string const TokenConstant::Keyword::RETURN = "return";
std::string const TokenConstant::Keyword::SET = "set";
std::string const TokenConstant::Keyword::WHILE = "while";
std::string const TokenConstant::Keyword::IF = "if";
std::string const TokenConstant::Keyword::ELSE = "else";

std::string const TokenConstant::CoreType::Number::DOUBLE = "Double";
std::string const TokenConstant::CoreType::Number::FLOAT = "Float";
std::string const TokenConstant::CoreType::Number::INTEGER = "Integer";

std::string const TokenConstant::CoreType::Complex::ARRAY = "Array";
std::string const TokenConstant::CoreType::Complex::STRING = "String";

std::string const TokenConstant::CoreType::VOID = "Void";

std::string const TokenConstant::Separator::DOT = ".";
char const TokenConstant::Separator::DOT_CHARACTER = '.';
std::string const TokenConstant::Separator::COLON = ":";
std::string const TokenConstant::Separator::COMMA = ",";
std::string const TokenConstant::Separator::SEMICOLON = ";";
char const TokenConstant::Separator::EXPONENT_CHARACTER = 'E';
std::string const TokenConstant::Separator::SPACE = " ";
std::string const TokenConstant::Separator::TAB = "\t";
std::string const TokenConstant::Separator::END_OF_LINE_LF = "\n";
std::string const TokenConstant::Separator::END_OF_LINE_CR = "\r";
char const TokenConstant::Separator::UNDERSCORE_CHARACTER = '_';

Parenthesis const TokenConstant::Parentheses::CURLY_BRACKET = { "{", "}" };
Parenthesis const TokenConstant::Parentheses::ROUND_BRACKET = { "(", ")" };
Parenthesis const TokenConstant::Parentheses::SQUARE_BRACKET = { "[", "]" };
char const TokenConstant::Parentheses::QUOTE_CHARACTER = '\'';
std::string const TokenConstant::Parentheses::QUOTE_STRING = "'";
char const TokenConstant::Parentheses::DOUBLE_QUOTE_CHARACTER = '"';
std::string const TokenConstant::Parentheses::DOUBLE_QUOTE_STRING = "\"";

std::string const TokenConstant::Name::UNKNOWN = "Unknown";

std::string const TokenConstant::Name::Operator::Arithmetic::DIVISION = "Division";
std::string const TokenConstant::Name::Operator::Arithmetic::MINUS = "Minus";
std::string const TokenConstant::Name::Operator::Arithmetic::MULTIPLY = "Multiply";
std::string const TokenConstant::Name::Operator::Arithmetic::PLUS = "Plus";

std::string const TokenConstant::Name::Operator::Assignment::ASSIGNMENT = "Assignment";
std::string const TokenConstant::Name::Operator::Assignment::DIVISION_ASSIGNMENT = "Division assignment";
std::string const TokenConstant::Name::Operator::Assignment::MINUS_ASSIGNMENT = "Minus assignment";
std::string const TokenConstant::Name::Operator::Assignment::MULTIPLY_ASSIGNMENT = "Multiply assignment";
std::string const TokenConstant::Name::Operator::Assignment::PLUS_ASSIGNMENT = "Plus assignment";

std::string const TokenConstant::Name::Operator::Comparison::EQUIVALENCE = "Equivalence";
std::string const TokenConstant::Name::Operator::Comparison::NOT_EQUIVALENCE = "Not equivalence";
std::string const TokenConstant::Name::Operator::Comparison::MORE_OR_EQUIVALENCE = "More or equal";
std::string const TokenConstant::Name::Operator::Comparison::LESS_OR_EQUIVALENCE = "Less or equal";
std::string const TokenConstant::Name::Operator::Comparison::MORE = "More";
std::string const TokenConstant::Name::Operator::Comparison::LESS = "Less";

std::string const TokenConstant::Name::Keyword::CLASS = "Class keyword";
std::string const TokenConstant::Name::Keyword::CONSTRUCTOR = "Constructor keyword";
std::string const TokenConstant::Name::Keyword::DO = "Do keyword";
std::string const TokenConstant::Name::Keyword::EXTENDS = "Extends keyword";
std::string const TokenConstant::Name::Keyword::FOR = "For keyword";
std::string const TokenConstant::Name::Keyword::GET = "Get keyword";
std::string const TokenConstant::Name::Keyword::IMPLEMENTS = "Implements keyword";
std::string const TokenConstant::Name::Keyword::NOT_INITIALIZED = "NULL keyword";
std::string const TokenConstant::Name::Keyword::PRIVATE = "Private keyword";
std::string const TokenConstant::Name::Keyword::PUBLIC = "Public keyword";
std::string const TokenConstant::Name::Keyword::RETURN = "Return keyword";
std::string const TokenConstant::Name::Keyword::SET = "Set keyword";
std::string const TokenConstant::Name::Keyword::WHILE = "While keyword";
std::string const TokenConstant::Name::Keyword::IF = "If keyword";
std::string const TokenConstant::Name::Keyword::ELSE = "Else keyword";

std::string const TokenConstant::Name::INTEGER = "Integer";
std::string const TokenConstant::Name::FLOAT = "Float";
std::string const TokenConstant::Name::EXPONENTIAL = "Exponential";

std::string const TokenConstant::Name::Separator::DOT = "Dot";
std::string const TokenConstant::Name::Separator::COLON = "Colon";
std::string const TokenConstant::Name::Separator::COMMA = "Comma";
std::string const TokenConstant::Name::Separator::SEMICOLON = "Semicolon";

std::string const TokenConstant::Name::Parentheses::CURLY_BRACKET_LEFT = "Left curly bracket";
std::string const TokenConstant::Name::Parentheses::CURLY_BRACKET_RIGHT = "Right curly bracket";
std::string const TokenConstant::Name::Parentheses::ROUND_BRACKET_LEFT = "Left round bracket";
std::string const TokenConstant::Name::Parentheses::ROUND_BRACKET_RIGHT = "Right round bracket";
std::string const TokenConstant::Name::Parentheses::SQUARE_BRACKET_LEFT = "Left square bracket";
std::string const TokenConstant::Name::Parentheses::SQUARE_BRACKET_RIGHT = "Right square bracket";

std::string const TokenConstant::Name::TYPE = "Type";
std::string const TokenConstant::Name::IDENTIFIER = "Identifier";
std::string const TokenConstant::Name::STRING_LITERAL = "String literal";
std::string const TokenConstant::Name::CHARACTER_LITERAL = "Character literal";
std::string const TokenConstant::Name::LINE_COMMENT = "Line comment";
std::string const TokenConstant::Name::BLOCK_COMMENT = "Block comment";

std::string const TokenConstant::Name::END_OF_FILE = "End of file";

std::regex const TokenConstant::Regex::IDENTIFIER("[_a-zA-Z][_a-zA-Z0-9]*");
