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

	void CreateToken(vector<Token>& tokenArray, vector<char>& alphabet, string& s, ofstream& out)
	{
		if (s.size() != 0)
		{
			if (s == "PROGRAM" || s == "END" || s == "INTEGER")
			{
				tokenArray.push_back(Token(s, "KEYWORD"));
				s.clear();
				return;
			}
			else if (dfa(countStatesRel, alphabet, finalStatesRel, transitFunctionRel).isAccept(s))
			{
				tokenArray.push_back(Token(s, "REL OPER"));
				s.clear();
				return;
			}
			else if (dfa(countStatesCond, alphabet, finalStatesCond, transitFunctionCond).isAccept(s))
			{
				tokenArray.push_back(Token(s, "COND OPER"));
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
		ofstream out("errors.txt");
		while (!in.eof())
		{
			in.get(a);
			if (a == ';')
			{
				CreateToken(tokenArray, alphabet, s, out);
				tokenArray.push_back(Token(";", "SEP"));
			}
			else if (a == ',')
			{
				CreateToken(tokenArray, alphabet, s, out);
				tokenArray.push_back(Token(",", "SEP"));
			}
			else if (a == ' ')
			{
				CreateToken(tokenArray, alphabet, s, out);
			}
			else if (a == '+' || a == '-' || a == '=')
			{
				CreateToken(tokenArray, alphabet, s, out);
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
					CreateToken(tokenArray, alphabet, s, out);
				}
				else
				{
					CreateToken(tokenArray, alphabet, s, out);
					s += a;
				}
			}
			else if (a == '\n')
			{
				CreateToken(tokenArray, alphabet, s, out);
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