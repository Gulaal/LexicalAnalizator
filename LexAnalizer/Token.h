#pragma once

#include <string>
	
using namespace std;

class Token
{
private:

	string token_name;
	string token_type;
	
public:

	Token()
	{
		this->token_name = "";
		this->token_type = "";
	}

	Token(const string& tokenName, const string& tokenType)
	{
		this->token_name = tokenName;
		this->token_type = tokenType;
	}

	string getTokenName()
	{
		return this->token_name;
	}

	string getTokenType()
	{
		return this->token_type;
	}

	string setTokenName(string newName)
	{
		return this->token_name = newName;
	}

	string setTokenType(string newType)
	{
		return this->token_type = newType;
	}

};