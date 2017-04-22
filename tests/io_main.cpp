#include <iostream>
#include "../headers/io.h"
#include <stdio.h>

using namespace std;
using namespace io;

int main()
{
	cout << "Input de: ";
	char r = de();
	cout << endl << "Result de : " << r << endl;
	cout << "Result de : " << int(r) << endl;

	cout << "Input long : ";
	string s = long_input();
	cout << "Result : " << s << endl;

	cout << "Width : " << getTerminalWidth() << endl;
	cout << "Height : " << getTerminalHeight() << endl;

	bienvenue();

	return 0;
}
