#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include "../headers/carte.h"
#include "../headers/fonctionsjeu.h"
#include "../headers/io.h"

using namespace io;
using namespace std;

int main()
{
	jeu a;

	int persos_vivants = 1;
	int nbMonstres = a.getNbMonstres();

	while (persos_vivants != 0 && nbMonstres > 0)
	{
		//	a.deplacement();

		string monster = "m1";	//test

		//Si case monstre
		int result = a.combat(monster);	//Combat
		persos_vivants = result;
		nbMonstres -= result;
	}

	if (persos_vivants == 0)
	{
		cout << "Tous les joueurs sont morts! Partie perdue!" << endl;
		cout << endl << "Game Over" << endl << endl;
		return 0;
	}
	else if (nbMonstres == 0)
	{
		cout << "Tous les monstres sont morts! Partie gagnée!" << endl;
		cout << endl << "Here. Have a cookie" << endl << endl;
		return 1;
	}
}
