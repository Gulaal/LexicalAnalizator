#pragma once

#include <string>
	
class Token
{
private:

	std::string token_name;
	std::string token_type;

public:

	Token()
	{
		this->token_name = "";
		this->token_type = "";
	}

	Token(const std::string& tokenName, const std::string& tokenType)
	{
		this->token_name = tokenName;
		this->token_type = tokenType;
	}

	std::string getTokenName()
	{
		return this->token_name;
	}

	std::string getTokenType()
	{
		return this->token_type;
	}

	std::string setTokenName(std::string newName)
	{
		return this->token_name = newName;
	}

	std::string setTokenType(std::string newType)
	{
		return this->token_type = newType;
	}

};