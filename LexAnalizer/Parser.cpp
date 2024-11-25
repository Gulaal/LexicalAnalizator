#include "Parser.h"
#include "fstream"
#include "Token.h"
#include "Node.h"

using namespace std;

void Parser::match(const string& s)
{
	if (tokens[i].getTokenType() == s)
	{
		i++;
	}
	else
	{
		ofstream out("SyntaxErrors.txt");
		out << "Wrong symbol in " << i << " position in tokens" << endl
			<< "Expected token type: " + s << endl << "Resieved token type: " << tokens[i].getTokenType();
		exit(1);
	}
}

void Parser::match_name(const string& s)
{
	if (tokens[i].getTokenName() == s)
	{
		i++;
	}
	else
	{
		throw exception("Wrong input");
		exit(1);
	}
}

Parser::Parser(vector<Token>& tokens)
{
	this->tokens = tokens;
}

Node Parser::Parse()
{
	Node root("Begin");
	Begin(root);
	return root;
}

void Parser::Begin(Node& n)
{
	match("KEYWORD");
	n.addSon("PROGRAM");
	Id(n.getSon(0));
	n.addSon("Descriptions");
	Descriptions(n.getSon(1));
	n.addSon("Operators");
	Operators(n.getSon(2));
	n.addSon("End");
	End(n.getSon(3));
}

void Parser::End(Node& n)
{
	match("KEYWORD");
	n.addSon(tokens[i].getTokenName());
	match("VAR");
}

void Parser::Descriptions(Node& n)
{
	Descr(n);
	while (tokens[i].getTokenName() != "END" && tokens[i].getTokenType() != "VAR" && tokens[i].getTokenType() != "COND OPER")
	{
		Descr(n);
	}
}

void Parser::Operators(Node& n)
{
	n.addSon("Op");
	Op(n.getSon(0));
	while (tokens[i].getTokenName() != "END" && tokens[i].getTokenName() != "ELSE")
	{
		Op(n.getSon(0));
	}
}

void Parser::Op(Node& n)
{
	if (tokens[i].getTokenType() == "VAR")
	{
		match("VAR");
		n.addSon(tokens[i - 1].getTokenName());
		match("OPER");
		n.addSon(tokens[i - 1].getTokenName());
		n.addSon("Expr");
		Expr(n.getSon(2));
	}
	else if (tokens[i].getTokenType() == "COND OPER")
	{
		match("COND OPER");
		n.addSon("IF");
		Condition(n.getSon(0));
		n.addSon("THEN");
		match_name("THEN");             
		Operators(n.getSon(1));
		if (tokens[i].getTokenName() == "ELSE")
		{
			match("COND OPER");
			n.addSon("ELSE");
			Operators(n.getSon(2));
		}

	}
}

void Parser::Condition(Node& n)
{
	Expr(n);
	RelationOperators(n);
	Expr(n);
}

void Parser::Descr(Node& n)
{
	n.addSon("Type");
	Type(n.getSon(0));
	n.addSon("VarList");
	VarList(n.getSon(1));
}

void Parser::Type(Node& n)
{
	n.addSon("INTEGER");
	match("KEYWORD");
}

void Parser::VarList(Node& n)
{
	Id(n);
	while (tokens[i].getTokenType() == "SEP")
	{
		match("SEP");
		Id(n);
	}
}

void Parser::RelationOperators(Node& n)
{
	match("REL OPER");
	n.addSon(tokens[i - 1].getTokenName());
}

void Parser::Expr(Node& n)
{
	SimpleExpr(n);
	while (tokens[i].getTokenType() == "OPER")
	{
		match("OPER");
		n.addSon(tokens[i - 1].getTokenName());
		Expr(n);
	}
}

void Parser::SimpleExpr(Node& n)
{
	n.addSon("SimpleExpr");
	if (tokens[i].getTokenType() == "VAR")
	{
		Id(n);
	}
	else if (tokens[i].getTokenType() == "CONST")
	{
		Const(n);
	}
	else if (tokens[i].getTokenType() == "LEFT PAR")
	{
		match("LEFT PAR");
		n.addSon("(");
		Expr(n);
		match("RIGHT PAR");
		n.addSon(")");
	}
}

void Parser::Id(Node& n)
{
	match("VAR");
	n.addSon(tokens[i-1].getTokenName());
}

void Parser::Const(Node& n)
{
	match("CONST");
	n.addSon(tokens[i-1].getTokenName());
}

