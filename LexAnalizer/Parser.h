#pragma once
#include "Node.h"
#include <iostream>
#include <string>
#include "Token.h"
#include <vector>

using namespace std;
class Parser
{
private:

	int i;
	void match(const string& s);
	void match_name(const string& s);
	void Begin(Node& n);
	void Descriptions(Node& n);
	void Op(Node& n);
	void Condition(Node& n);
	void Descr(Node& n);
	void Type(Node& n);
	void VarList(Node& n);
	void RelationOperators(Node& n);
	void Expr(Node& n);
	void SimpleExpr(Node& n);
	void Operators(Node& n);
	void Const(Node& n);
	void End(Node& n);
	void Id(Node& n);

public:

	vector<Token> tokens;
	Parser(vector<Token>& tokens);
	Node Parse();
};

