#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include "Token.h"
#include "dfa.h"
#include "LexicalAnalyzer.h"
#include "HashTable.h"
#include "dfaSettings.h"
#include "Parser.h"
#include "Node.h"

using namespace std;

int main()
{
	ifstream in("input.txt");
	LexicalAnalizer A(in);
	vector<Token> B(A.tokenArray);
	Parser P(B);
	Node root = P.Parse();
	root.print(0);
}
