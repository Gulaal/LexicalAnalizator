#pragma once

#include<string>

using namespace std;

class Tocken
{
private:
	string tocken_name;
	string tocken_type;
public:

	Tocken(const string& tockenName, const string& tockenType)
	{
		this->tocken_name = tockenName;
		this->tocken_type = tockenType;
	}

	string getTockenName()
	{
		return this->tocken_name;
	}

	string getTockenType()
	{
		return this->tocken_type;
	}
};