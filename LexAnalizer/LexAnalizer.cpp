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

using namespace std;

int main()
{
	ifstream in("input.txt");
	LexicalAnalizer A(in);
	
}
