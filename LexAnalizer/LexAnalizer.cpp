#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include "Tocken.h"
#include "dfa.h"
#include "LexicalAnalyzer.h"
#include "dfaSettings.h"

using namespace std;

int main()
{
	// 34 * 2
	ifstream in("input.txt");
	LexicalAnalizer A(in);
	vector<Tocken> result = A.getTockenArray();
	for (int i = 0; i < result.size(); i++)
	{
		cout << setw(10) << result[i].getTockenName() << " |" << result[i].getTockenType() << '\n';
	}
}
