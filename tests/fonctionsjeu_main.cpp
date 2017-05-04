#include "../headers/io.h"
#include "../headers/fonctionsjeu.h"
#include <iostream>

using namespace io;
using namespace std;

int main()
{
	int dummy = 2;
	try
	{
		jeu a;
		a.afficherJeu(dummy);
	}
	catch (int constructError)
	{
		return 0;
	}
	return 0;
}
