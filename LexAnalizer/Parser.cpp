#include "Parser.h"

bool Parser::isNumber(string s)
{
	int state = 0;
	for (char c : s)
	{
		if (state == 0 && c == '0')
			state = 4;
		else if ((state == 0 || state == 1)
			&& isdigit(c))
			state = 1;
		else if ((state == 1 || state == 4) &&
			c == '.')
			state = 2;
		else if ((state == 2 || state == 3)
			&& isdigit(c))
			state = 3;
		else
			return false;
	}
	return (state == 1 || state == 3 || state == 4);
}

void Parser::getLexeme()
{
	if (i >= input.length())
	{
		lexeme = "#";
		return;
	}
	lexeme = "";
	if (input[i] == '+' || input[i] == '-' ||
		input[i] == '*' || input[i] == '/' ||
		input[i] == '^' || input[i] == '(' ||
		input[i] == ')')
	{
		lexeme += input[i];
		i++;
	}
	else
	{
		while (i < input.length() &&
			!(input[i] == '+' || input[i] == '-' ||
				input[i] == '*' || input[i] == '/' ||
				input[i] == '^' || input[i] == '(' ||
				input[i] == ')'))
		{
			lexeme += input[i];
			i++;
		}
	}
}

void Parser::match(const string& s)
{
	if (tokens[i].getTokenType() == s)
	{
		i++;
	}
	else
	{
		throw exception("Wrong input");
	}
}

void Parser::Parse()
{
	Node root("start");
	Begin();
	Descriptions();
	Operators();
	End();
}

void Parser::Begin(Node& n)
{
	n.addSon("Begin");
	match("KEYWORD");
	n.getSon(0).addSon("Id");
	Id(n.getSon(1));
}

void Parser::End(Node& n)
{
	n.addSon("End");
	match("KEYWORD");
	n.getSon(0).addSon("Id");
	match("VAR");
}

void Parser::Descriptions(Node& n)
{
	n.addSon("Descriptions");
	Descr(n.getSon(0));
	while (tokens[i].getTokenName() != "END" && tokens[i].getTokenType() != "VAR")
	{
		Descr(n.getSon(0));
	}
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
	n.addSon("Id");
	Id(n.getSon(0));
	while()
}

void Parser::Id(Node& n)
{
	match("VAR");
}

void Parser::Const(Node& n)
{
	match("CONST");
}

void Parser::S(Node& n)
{
	if (isNumber(lexeme) || lexeme == "x" ||
		lexeme == "(" || lexeme == "sin" ||
		lexeme == "cos" || lexeme == "exp" ||
		lexeme == "log")
	{
		// S -> TS1
		n.addSon("T");
		T(n.getSon(0));
		n.addSon("S1");
		S1(n.getSon(1));
		exit();
	}
	else throw exception("Wrong input");
}

void Parser::S1(Node& n)
{
	if (lexeme == "+")
	{
		// S1 -> +TS1
		n.addSon("+");
		getLexeme();
		n.addSon("T");
		T(n.getSon(1));
		n.addSon("S1");
		S1(n.getSon(2));
	}
	else if (lexeme == "-")
	{
		// S1 -> -TS1
		n.addSon("-");
		getLexeme();
		n.addSon("T");
		T(n.getSon(1));
		n.addSon("S1");
		S1(n.getSon(2));
	}
	else if (lexeme == ")" || lexeme == "#")
	{
		// S1 -> eps;
		n.addSon("eps");
	}
	else throw exception("Wrong input");
}

void Parser::T(Node& n)
{
	if (isNumber(lexeme) || lexeme == "x" ||
		lexeme == "(" || lexeme == "sin" ||
		lexeme == "cos" || lexeme == "exp" ||
		lexeme == "log")
	{
		// T -> FT1
		n.addSon("F");
		F(n.getSon(0));
		n.addSon("T1");
		T1(n.getSon(1));
	}
	else throw exception("Wrong input");
}

void Parser::T1(Node& n)
{
	if (lexeme == "*")
	{
		// T1 -> *FT1
		n.addSon("*");
		getLexeme();
		n.addSon("F");
		F(n.getSon(1));
		n.addSon("T1");
		T1(n.getSon(2));
	}
	else if (lexeme == "/")
	{
		// T1 -> /FT1
		n.addSon("/");
		getLexeme();
		n.addSon("F");
		F(n.getSon(1));
		n.addSon("T1");
		T1(n.getSon(2));
	}
	else if (lexeme == ")" || lexeme == "#" ||
		lexeme == "+" || lexeme == "-")
	{
		// T1 -> eps;
		n.addSon("eps");
	}
	else throw exception("Wrong input");
}

void Parser::F(Node& n)
{
	if (isNumber(lexeme) || lexeme == "x" ||
		lexeme == "(" || lexeme == "sin" ||
		lexeme == "cos" || lexeme == "exp" ||
		lexeme == "log")
	{
		// F -> AF1
		n.addSon("A");
		A(n.getSon(0));
		n.addSon("F1");
		F1(n.getSon(1));
	}
	else throw exception("Wrong input");
}

void Parser::F1(Node& n)
{
	if (lexeme == "^")
	{
		// F1 -> ^AF1
		n.addSon("^");
		getLexeme();
		n.addSon("A");
		A(n.getSon(1));
		n.addSon("F1");
		F1(n.getSon(2));
	}
	else if (lexeme == "+" || lexeme == "-" ||
		lexeme == "*" || lexeme == "/" ||
		lexeme == ")" || lexeme == "#")
	{
		// F1 -> eps;
		n.addSon("eps");
	}
	else throw exception("Wrong input");
}

void Parser::A(Node& n)
{
	if (isNumber(lexeme))
	{
		// A -> num
		n.addSon(lexeme);
		getLexeme();
	}
	else if (lexeme == "x")
	{
		// A -> x
		n.addSon("x");
		getLexeme();
	}
	else if (lexeme == "(")
	{
		n.addSon("(");
		getLexeme();
		n.addSon("S");
		S(n.getSon(1));
		if (lexeme == ")")
		{
			n.addSon(")");
			getLexeme();
		}
		else throw exception("Wrong input");
	}
	else if (lexeme == "sin" || lexeme == "cos" ||
		lexeme == "log" || lexeme == "exp")
	{
		// A -> f(S)
		n.addSon(lexeme);
		getLexeme();
		if (lexeme == "(")
		{
			n.addSon("(");
			getLexeme();
			n.addSon("S");
			S(n.getSon(2));
			if (lexeme == ")")
			{
				n.addSon(")");
				getLexeme();
			}
			else throw exception("Wrong input");
		}
		else throw exception("Wrong input");
	}
	else throw exception("Wrong input");
}

Parser::Parser(string inp)
{
	input = inp;
	i = 0;
}

Node Parser::parse()
{
	Node root("S");
	getLexeme();
	S(root);
	if (lexeme != "#")
		throw exception("Wrong input");
	return root;
}
