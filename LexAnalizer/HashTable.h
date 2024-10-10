#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Token.h"
#include <string>
#include <vector>

using namespace std;

const int INITIAL_SIZE = 10;
const int PRIME = 31;

class HashTable {
private:

	Token* table;
	int size;
	int elementCount;

	void rehash()
	{
		int newSize = this->size * 2;
		Token* newTable = new Token[newSize];
		for (int i = 0; i < size; i++)
		{
			if (table[i].getTokenName() != "")
			{
				int newHash = hashFunc(table[i], newSize);
				while (newTable[newHash].getTokenName() != "")
				{
					newHash = (newHash + 1) % newSize;
				}
				newTable[newHash].setTokenName(table[i].getTokenName());
				newTable[newHash].setTokenType(table[i].getTokenType());
			}
		}
		table = move(newTable);
		size = newSize;
	}

public:

	HashTable()
	{
		size = INITIAL_SIZE;
		elementCount = 0;
		table = new Token[INITIAL_SIZE];
	}

	HashTable(vector<Token>& tokenArray)
	{
		size = INITIAL_SIZE;
		elementCount = 0;
		table = new Token[INITIAL_SIZE];
		for (int i = 0; i < tokenArray.size(); i++)
		{
			add(tokenArray[i]);
		}
	}

	void add(Token& token)
	{
		if (elementCount >= size * 0.75)
		{
			rehash();
		}
		int hash = hashFunc(token, size);
		if (elementCount < size)
		{
			Token tokenByIndex = table[hash];
			if (tokenByIndex.getTokenName() == token.getTokenName())
			{
				return;
			}
			else
			{
				while (tokenByIndex.getTokenName() != "")
				{
					if (tokenByIndex.getTokenName() == token.getTokenName())
					{
						return;
					}
					hash = (hash + 1) % size;
					tokenByIndex = table[hash];
				}
				table[hash].setTokenName(token.getTokenName());
				table[hash].setTokenType(token.getTokenType());
				elementCount++;
			}
		}
	}

	int hashFunc(Token& token, int size)
	{
		int hash = 0;
		int power = 1;
		string tokenName = token.getTokenName();
		for (char ch : tokenName)
		{
			hash = (hash + (ch - 'a' + 1) * power) % size;
			power = (power * PRIME) % size;
		}
		return abs(hash) % size;
	}

	int hashFunc(const string& str, int size)
	{
		int hash = 0;
		int power = 1;
		for (char ch : str)
		{
			hash = (hash + (ch - 'a' + 1) * power) % size;
			power = (power * PRIME) % size;
		}
		return abs(hash) % size;
	}

	string get(const string& key)
	{
		int hash = hashFunc(key, size);
		int startIndex = hash;
		while (table[hash].getTokenName() != "")
		{
			if (table[hash].getTokenName() == key)
			{
				return table[hash].getTokenType();
			}
			hash = (hash + 1) % size;
			if (hash == startIndex)
			{
				break;
			}
		}
		return "";
	}

	void printHashTable() const
	{
		std::ofstream out("output.txt");
		for (int i = 0; i < size; i++)
		{
			if (!table[i].getTokenName().empty())
			{
				out << setw(10) << i << " |" << setw(10) << table[i].getTokenName() << " |" << table[i].getTokenType() << '\n';
			}
		}
	}
};