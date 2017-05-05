#include <algorithm>
#include <ctime>
#include <iostream>
#include <stdlib.h>
#include "../headers/carte.h"
#include "../headers/fonctionsjeu.h"
#include "../headers/io.h"

using namespace io;
using namespace std;

int main()
{
	srand(time(0));	//Modification de la seed de rand()

	jeu a;

	int persos_vivants = 1;
	int nbMonstres = a.getNbMonstres();
	int result = 0;

	string monstre = "m00";

	result = a.combat(monstre);
	persos_vivants = result;
	nbMonstres -= result;

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


//	while (persos_vivants != 0 && nbMonstres > 0)
//	{
//		a.afficherJeu(result);

//		if (a.getCarte().getPlateau()[currentPlayerPosition.first][currentPlayerPosition.second].substr(0, 1) == "m")
//		{
//			result = a.combat(a.getCarte().getPlateau()[currentPlayerPosition.first][currentPlayerPosition.second]);
//			persos_vivants = result;
//			nbMonstres -= result;
//		}
