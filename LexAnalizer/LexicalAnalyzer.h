#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Token.h"
#include "dfa.h"
#include "dfaSettings.h"
#include "HashTable.h"

using namespace std;

class LexicalAnalizer
{
private:
	vector<Token> tokenArray;

	void CreateToken(vector<Token>& tokenArray, vector<char> alphabet, string& s)
	{
		if (s.size() != 0)
		{
			if (s == "PROGRAM" || s == "END" || s == "INTEGER")
			{
				tokenArray.push_back(Token(s, "KEYWORD"));
				s.clear();
				return;
			}
			else if (dfa(countStatesVar, alphabet, finalStatesVar, transitFunctionVar).isAccept(s))
			{
				tokenArray.push_back(Token(s, "VAR"));
				s.clear();
				return;
			}
			else if (dfa(countStatesConst, alphabet, finalStatesConst, transitFunctionConst).isAccept(s))
			{
				tokenArray.push_back(Token(s, "CONST"));
				s.clear();
				return;
			}
			else if (dfa(countStatesRel, alphabet, finalStatesRel, transitFunctionRel).isAccept(s))
			{
				tokenArray.push_back(Token(s, "OPER"));
				s.clear();
				return;
			}
			ofstream out("errors.txt", ios::app);
			out << "Неудалось распознать лексему: " << s << '\n';
			s.clear();
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
		int dotCounter = 0;
		while (!in.eof())
		{
			in.get(a);
			if (a == ';')
			{
				CreateToken(tokenArray, alphabet, s);
				tokenArray.push_back(Token(";", "SEP"));
			}
			else if (a == ',')
			{
				CreateToken(tokenArray, alphabet, s);
				tokenArray.push_back(Token(",", "SEP"));
			}
			else if (a == ' ')
			{
				CreateToken(tokenArray, alphabet, s);
			}
			else if (a == '+' || a == '-' || a == '=')
			{
				CreateToken(tokenArray, alphabet, s);
				string oper = "";
				oper += a;
				tokenArray.push_back(Token(oper, "OPER"));
			}
			else if (a == '.')
			{
				dotCounter++;
				if (dotCounter == 2)
				{
					s += a;
					CreateToken(tokenArray, alphabet, s);
				}
				else
				{
					CreateToken(tokenArray, alphabet, s);
					s += a;
				}
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

	vector<Token> getTokenArray()
	{
		return this->tokenArray;
	}
};