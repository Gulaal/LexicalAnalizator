#pragma once
#include "ExpressionNode.h"
#include <vector>
class StatementsNode : ExpressionNode
{
private:
	vector<ExpressionNode> code;
public:
	void addNode(ExpressionNode& node)
	{
		this->code.push_back(node);
	}
};