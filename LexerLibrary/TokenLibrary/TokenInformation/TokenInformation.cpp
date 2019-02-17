#include "TokenInformation.h"

TokenInformation::TokenInformation(Token token, StreamString const & tokenStreamString, std::string const & fileName)
	: m_token(token)
	, m_tokenStreamString(tokenStreamString)
	, m_fileName(fileName)
{}

Token TokenInformation::GetToken() const
{
	return m_token;
}

StreamString const & TokenInformation::GetTokenStreamString() const
{
	return m_tokenStreamString;
}

std::string const & TokenInformation::GetFileName() const
{
	return m_fileName;
}

std::string TokenInformation::ToString() const
{
	return m_fileName + "[" + std::to_string(m_tokenStreamString.position.GetLine()) + ", "
		+ std::to_string(m_tokenStreamString.position.GetColumn()) + "]: \n" + "\t" + "String : "
		+ m_tokenStreamString.string + "\n" + "\t" + "Type   : " + TokenExtensions::ToString(m_token) + "\n";
}
