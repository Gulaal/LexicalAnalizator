#pragma once
#include "ExpressionNode.h"
#include "Token.h"
class ConstNode : ExpressionNode
{
	Token number;

	ConstNode(Token variable)
	{
		this->number = number;
	}
};