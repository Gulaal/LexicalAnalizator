#pragma once

#include <string>
#include <vector>
#include <fstream>
#include "Tocken.h"
#include "dfa.h"
#include "dfaSettings.h"
#include "HashTable.h"

using namespace std;

class LexicalAnalizer
{
private:
	vector<Tocken> tockenArray;

	void CreateTocken(vector<Tocken>& tockenArray, vector<char> alphabet, string& s)
	{
		if (s.size() != 0)
		{
			if (s == "PROGRAM" || s == "END" || s == "INTEGER")
			{
				tockenArray.push_back(Tocken(s, "KEYWORD"));
				s.clear();
				return;
			}
			else if (dfa(countStatesVar, alphabet, finalStatesVar, transitFunctionVar).isAccept(s))
			{
				tockenArray.push_back(Tocken(s, "VAR"));
				s.clear();
				return;
			}
			else if (dfa(countStatesConst, alphabet, finalStatesConst, transitFunctionConst).isAccept(s))
			{
				tockenArray.push_back(Tocken(s, "CONST"));
				s.clear();
				return;
			}
			ofstream out("errors.txt");
			out << "Неудалось распознать лексему: " << s << '\n';
			s.clear();
			// Принтануть в errors.txt если не смог разпознать лексему
		}

	}
public:

	LexicalAnalizer(ifstream& in)
	{
		vector<char> alphabet;
		for (char c = 'a'; c <= 'z'; c++)
		{
			alphabet.push_back(c);
		}
		for (char c = 'A'; c <= 'Z'; c++)
		{
			alphabet.push_back(c);
		}
		for (char c = '0'; c <= '9'; c++)
		{
			alphabet.push_back(c);
		}
		alphabet.push_back('.');
		alphabet.push_back('+');
		alphabet.push_back('-');
		alphabet.push_back(',');
		alphabet.push_back(';');
		char a;
		string s;
		while (!in.eof())
		{
			in.get(a);
			if (a == ';')
			{
				CreateTocken(tockenArray, alphabet, s);
				tockenArray.push_back(Tocken(";", "SEP"));
			}
			else if (a == ',')
			{
				CreateTocken(tockenArray, alphabet, s);
				tockenArray.push_back(Tocken(",", "SEP"));
			}
			else if (a == ' ')
			{
				CreateTocken(tockenArray, alphabet, s);
			}
			else if (a == '+' || a == '-' || a == '=')
			{
				CreateTocken(tockenArray, alphabet, s);
				string oper = "";
				oper += a;
				tockenArray.push_back(Tocken(oper, "OPER"));
			}
			else if (a == '\n')
			{
				continue;
			}
			else
			{
				s += a;
			}
		}
	}

	vector<Tocken> getTockenArray()
	{
		return this->tockenArray;
	}
};