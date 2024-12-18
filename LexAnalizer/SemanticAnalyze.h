#pragma once
#include "Node.h"
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <sstream>

class SemanticAnalyze
{
public:
	string Errors;
	Node root;
	SemanticAnalyze() = default;
	SemanticAnalyze(Node& root)
	{
		this->root = root;
	}
	vector<string> Result;
	void readTree()
	{
		countOfMarks = 0;
		Errors = "";
		begin(this->root.getSon(0));
		descriptions(this->root.getSon(1));
		operators(this->root.getSon(2));
		end(this->root.getSon(3));
		printErrors();
	}

	void begin(Node& n)
	{
		string programStr = "";
		string programName = "";
		string programResult;
		programStr += n.data + ' ';
		programName += n.children[0].data;
		this->ProgramName = programName;
		programResult = programStr + programName + " DECL";
		this->Variables[programName] = true;
		this->Result.push_back(programResult);
	}

	void descriptions(Node& n)
	{
		for (int i = 0; i < n.children.size(); i++)
		{
			string line = "INTEGER ";
			for (int j = 1; j < n.getSon(i).getSon(0).children.size(); j++)
			{
				string variable = n.getSon(i).getSon(0).children[j].data;
				if (this->Variables[variable])
				{
					Errors += "Variable " + variable + " was defined before!\n";
				}
				line += variable + ' ';
				this->Variables[variable] = 1;
			}
			line += "DECL";
			this->Result.push_back(line);
		}
	}

	void operators(Node& n)
	{
		for (int i = 0; i < n.children.size(); i++)
		{
			op(n.getSon(i));
		}
	}

	void op(Node& n)
	{
		if (n.children[0].data == "IF")
		{
			int countMarks = countOfMarks;
			string ifString = "";
			SimpleExpr(n.getSon(0).getSon(0), ifString);
			string relOper = n.getSon(0).getSon(1).data;
			ifString += relOper + ' ';
			this->countOfMarks++;
			countMarks++;
			string mark = 'm' + toString(countOfMarks);
			ifString += mark + " BF ";
			this->Result.push_back(ifString);
			for (int i = 0; i < n.getSon(1).children.size(); i++)
			{
				op(n.getSon(1).getSon(i));
			}
			if (n.children.size() == 3)
			{
				string elseMark = "m" + toString(countMarks) + " DEFL";
				this->Result.push_back(elseMark);
				for (int i = 0; i < n.getSon(2).children.size(); i++)
				{
					op(n.getSon(2).getSon(i));
				}
			}
		}
		else
		{
			string eqString = "";
			string variableLeft = n.getSon(0).data;
			if (!isdigits(variableLeft) && Variables[variableLeft] == false)
			{
				varError(variableLeft);
			}
			string eqSign = n.getSon(1).data;
			eqString += variableLeft;
			Expr(n.getSon(2), eqString);
			eqString += ' ' + eqSign + ' ';
			this->Result.push_back(eqString); 
			
		}
	}

	void Expr(Node& n, string& str)
	{
		if (n.children.size() == 1)
		{
			SimpleExpr(n.getSon(0), str);
		}
		else
		{
			SimpleExpr(n.getSon(0),str);
			string sign = n.getSon(1).data;
			for (int i = 2; i < n.children.size(); i++)
			{
				Expr(n.getSon(i), str);
			}
			str += ' ' + sign;
		}
	}

	void SimpleExpr(Node& n, string& s)
	{
		if (n.children.size() == 1)
		{
			s += ' ' + n.getSon(0).data;
		}
		else if (n.getSon(0).data == "(")
		{
			Expr(n.getSon(1), s);
		}
		else
		{
			string variableLeft = n.getSon(0).data;
			string variableRight = n.getSon(1).data;
			if (!isdigits(variableLeft) && Variables[variableLeft] == false)
			{
				varError(variableLeft);
			}
			if (!isdigits(variableRight) && Variables[variableRight] == false)
			{
				varError(variableRight);
			}
			s += variableLeft + ' ' + variableRight + ' ';
		}
	}

	void end(Node& n)
	{
		if (n.getSon(0).data != this->ProgramName)
		{
			programError(n.getSon(0).data);
		}
		else
		{
			string endString = "END " + n.getSon(0).data;
			this->Result.push_back(endString);
		}
	}

	void print()
	{
		ofstream out("SemanticOutput.txt");
		for (int i = 0; i < this->Result.size(); i++)
		{
			out << this->Result[i] << '\n';
		}
		out.close();
	}

	void varError(string& variable)
	{
		Errors += "Variable " + variable + " do not exist!\n";	
	}

	void programError(string& variable)
	{
		Errors += "Program name and " + variable + "not equal!\n";
	}

	string toString(int val)
	{
		std::ostringstream oss;
		oss << val;
		return oss.str();
	}

	void printErrors()
	{
		ofstream out("SemanticErrors.txt");
		out << Errors;
	}

	bool isdigits(string& str)
	{
		for (char c : str)
		{
			if (c >= '0' || c <= '9')
			{
				return true;
			}
		}
		return false;
	}

private:
	map<string, bool> Variables;
	int countOfMarks;
	string ProgramName;
};