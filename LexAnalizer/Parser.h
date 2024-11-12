#pragma once
#include "Token.h"
#include "ExpressionNode.h"
#include "StatementsNode.h"
#include <string>
#include <vector>


class Parser
{
private:
	vector<string> tokenTypes;
	vector<Token> tokens;
	int pos;

public:

	Parser(vector<Token> tokens)
	{
		this->tokens = tokens;
		this->pos = 0;
	}
	
	Token match(string first...)
	{
		string* pFirst = &first;
		if (this->pos < this->tokens.size())
		{
			Token currentToken = this->tokens[this->pos];
			
		}
	}

	Token require()
	{

	}

	void parseExpression()
	{

	}

	StatementsNode parseCode()
	{
		StatementsNode root;
		while (this->pos < this->tokens.size())
		{
			parseExpression();
		}
		return root;
	}

};