#include "Node.h"

Node::Node(string s)
{
	data = s;
}

void Node::addSon(string s)
{
	Node n(s);
	children.push_back(n);
}

Node& Node::getSon(int i)
{
	return children[i];
}

void Node::print(int lvl)
{
	for (int i = 0; i < lvl; ++i)
		cout << "  ";
	cout << data << endl;
	for (Node n : children)
		n.print(lvl + 1);
}

double Node::evaluate(double x)
{
	if (data == "S")
		return children[0].evaluate(x) +
		children[1].evaluate(x);
	else if (data == "S1")
	{
		if (children[0].data == "+")
			return children[1].evaluate(x) +
			children[2].evaluate(x);
		else if (children[0].data == "-")
			return -(children[1].evaluate(x) +
				children[2].evaluate(x));
		else return 0;
	}
	else if (data == "T")
		return children[0].evaluate(x) *
		children[1].evaluate(x);
	else if (data == "T1")
	{
		if (children[0].data == "*")
			return children[1].evaluate(x) *
			children[2].evaluate(x);
		else if (children[0].data == "/")
			return 1.0 / (children[1].evaluate(x) *
				children[2].evaluate(x));
		else return 1;
	}
	else if (data == "F")
		return pow(children[0].evaluate(x),
			children[1].evaluate(x));
	else if (data == "F1")
	{
		if (children[0].data == "^")
			return pow(children[1].evaluate(x),
				children[2].evaluate(x));
		else return 1;
	}
	else if (data == "A")
	{
		if (children[0].data == "x")
			return x;
		else if (children[0].data == "(")
			return children[1].evaluate(x);
		else if (children[0].data == "sin")
			return sin(children[2].evaluate(x));
		else if (children[0].data == "cos")
			return cos(children[2].evaluate(x));
		else if (children[0].data == "exp")
			return exp(children[2].evaluate(x));
		else if (children[0].data == "log")
			return log(children[2].evaluate(x));
		else return stod(children[0].data);
	}
	else throw exception("Something wrong");
}
