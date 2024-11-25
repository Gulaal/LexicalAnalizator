#pragma once

#include <iostream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;
class Node
{
private:
	string data;
	vector<Node> children;
public:
	Node(string s);
	void addSon(string s);
	void change_data(string s);
	void addSon(Node& n);
	Node& getSon(int i);
	void print(int lvl);
};

