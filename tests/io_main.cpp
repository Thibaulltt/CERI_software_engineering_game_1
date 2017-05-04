#include <iostream>
#include "../headers/io.h"
#include <stdio.h>

using namespace std;
using namespace io;

int main()
{
	cout << "Test " << BLUE << "io::" << MAGENTA << "de()" << BLANK << " : ";
	char r = de();
	cout << endl << "Resultat " << BLUE << "io::" << MAGENTA << "de()" << BLANK << " : " << r << endl;
	cout << "Resultat " << YELLOW << "int" << BLANK << "( " << BLUE << "io::" << MAGENTA << "de()" << BLANK << " ) : " << int(r) << endl;

	cout << "Test " << BLUE << "io::" << MAGENTA << "long_input()" << BLANK << " : ";
	string s = long_input();
	cout << "Resultat : " << s << endl;
	for (int i = 0; i < s.size(); i++)
		cout << "i : " << i << " : " << s[i] << " /// " << int(s[i]) << endl;

	cout << "Test " << BLUE << "io::" << MAGENTA << "getTerminalWidth()" << BLANK << " : " << getTerminalWidth() << endl;
	cout << "Test " << BLUE << "io::" << MAGENTA << "getTerminalHeight()" << BLANK << " : " << getTerminalHeight() << endl;
	cout << "Test " << BLUE << "io::" << RED << "TermWidth" << BLANK << " : " << io::TermWidth << endl;
	cout << "Test " << BLUE << "io::" << RED << "TermWidth" << BLANK << " : " << io::TermHeight << endl;

	//cout << "Test " << BLUE << "io::" << MAGENTA << "afficherInteractions()" << BLANK << " : " << endl;
	//afficherMouvements();
	//de();
	//afficherMouvements("Have you heard of the tragedy of Darth Plagueis the wise ? I thought not, it's not a story the Jedi would tell you. It's a Sith legend. Darth Plagueis was a Dark Lord of the Sith.");

	//loadAllCarteFromFile("sources/fichierCarte.txt");

	return 0;
}
