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

	HashTable tokenHashTable;

	void CreateToken(vector<char>& alphabet, string& s, ofstream& out)
	{
		if (s.size() != 0)
		{
			if (s == "PROGRAM" || s == "END" || s == "INTEGER")
			{
				Token token = Token(s, "KEYWORD");
				tokenHashTable.add(token);
				s.clear();
				return;
			}
			else if (dfa(countStatesRel, alphabet, finalStatesRel, transitFunctionRel).isAccept(s))
			{
				Token token = Token(s, "REL OPER");
				tokenHashTable.add(token);
				s.clear();
				return;
			}
			else if (dfa(countStatesCond, alphabet, finalStatesCond, transitFunctionCond).isAccept(s))
			{
				Token token = Token(s, "COND OPER");
				tokenHashTable.add(token);
				s.clear();
				return;
			}
			else if (dfa(countStatesVar, alphabet, finalStatesVar, transitFunctionVar).isAccept(s))
			{
				Token token = Token(s, "VAR");
				tokenHashTable.add(token);
				s.clear();
				return;
			}
			else if (dfa(countStatesConst, alphabet, finalStatesConst, transitFunctionConst).isAccept(s))
			{
				Token token = Token(s, "CONST");
				tokenHashTable.add(token);
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
				CreateToken(alphabet, s, out);
				Token token = Token(";", "SEP");
				tokenHashTable.add(token);
			}
			else if (a == ',')
			{
				CreateToken(alphabet, s, out);
				Token token = Token(",", "SEP");
				tokenHashTable.add(token);
			}
			else if (a == ' ')
			{
				CreateToken(alphabet, s, out);
			}
			else if (a == '+' || a == '-' || a == '=')
			{
				CreateToken(alphabet, s, out);
				string oper = "";
				oper += a;
				Token token = Token(oper, "OPER");
				tokenHashTable.add(token);
			}
			else if (a == '.')
			{
				dotCounter++;
				if (dotCounter == 2)
				{
					s += a;
					CreateToken(alphabet, s, out);
				}
				else
				{
					CreateToken(alphabet, s, out);
					s += a;
				}
			}
			else if (a == '\n')
			{
				CreateToken(alphabet, s, out);
			}
			else
			{
				s += a;
			}
		}
	}

	HashTable getHashTable()
	{
		return this->tokenHashTable;
	}
};