#pragma once
#include "Node.h"
#include <iostream>
#include <string>
using namespace std;
class Parser
{
private:
	string input, lexeme;
	int i;
	int str;
	vector<Token> tokens;

	bool isNumber(string s);
	void getLexeme();
	void match(const string& s);
	void Parse();
	void Begin(Node& n);
	void Descriptions(Node& n);
	void Descriptions1(Node& n);
	void Operators(Node& n);
	void End(Node& n);
	void Id(Node& n);
	void S(Node& n);
	void S1(Node& n);
	void T(Node& n);
	void T1(Node& n);
	void F(Node& n);
	void F1(Node& n);
	void A(Node& n);
public:
	Parser(string inp);
	Node parse();
};

