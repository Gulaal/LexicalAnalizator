#include "Node.h"
#include "Parser.h"
#include "Integral.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	try
	{
		string input;
		cin >> input;
		double x;
		cin >> x;
		Parser p(input);
		Node root = p.parse();
		//root.print(0);
		cout << root.evaluate(x) << endl;
	}
	catch (exception e)
	{
		cout << e.what() << endl;
	}
	return 0;
}