#ifndef TOKEN_TOKENINFORMATION_H
#define TOKEN_TOKENINFORMATION_H

#include "../StreamStringLibrary/StreamString.h"
#include "../Token.h"
#include "../TokenExtensions/TokenExtensions.h"
#include <string>

class TokenInformation
{
public:
	explicit TokenInformation() = default;
	explicit TokenInformation(Token token, StreamString const & tokenStreamString, std::string const & fileName = "");
	Token GetToken() const;
	StreamString const & GetTokenStreamString() const;
	std::string const & GetFileName() const;
	std::string ToString() const;

private:
	Token m_token = Token::UNKNOWN;
	StreamString m_tokenStreamString;
	std::string m_fileName;
};

#endif
