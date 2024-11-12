#pragma once
#include "ExpressionNode.h"
#include "Token.h"
class BinOperatorNode : ExpressionNode
{
	Token oper;
	ExpressionNode leftNode;
	ExpressionNode rightNode;
	BinOperatorNode (Token oper, ExpressionNode leftNode, ExpressionNode rightNode)
	{
		this->oper = oper;
		this->leftNode = leftNode;
		this->rightNode = rightNode;
	}
};