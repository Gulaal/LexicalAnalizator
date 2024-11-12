#pragma once
#include "ExpressionNode.h"
#include "Token.h"
class VariableNode : ExpressionNode
{
	Token variable;

	VariableNode(Token variable)
	{
		this->variable = variable;
	}
};