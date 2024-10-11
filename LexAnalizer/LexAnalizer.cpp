#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include "Token.h"
#include "dfa.h"
#include "LexicalAnalyzer.h"
#include "HashTable.h"
#include "dfaSettings.h"

using namespace std;

int main()
{
	// 34 * 2
	ifstream in("input.txt");
	LexicalAnalizer A(in);
	A.getHashTable().printHashTable();
}
