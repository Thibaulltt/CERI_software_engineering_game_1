#include "../headers/carte.h"
#include "../headers/config.h"
#include "../headers/io.h"

using namespace io;
using namespace std;

int main ()
{
	config test;

	while (1)
	{
		puts("Bienvenue dans le module de configuration de The Game \n Choisissez l'élément à configurer: ");

		puts("1- Configuration des cartes");
		puts("2- Configuration des monstres");
		puts("3- Configuration des personnages");
		puts("q- Quitter le module de configuration");

		puts("\n");

		char c_choix = de();
		int choix = c_choix - '0';

		switch (choix)
		{
		case 1:
			test.config_carte();
			break;

		case 2:
			test.config_monstre();
			break;

		case 3:
			test.config_perso();
			break;

		default:
			goto fin;
		}
	}
fin:return 0;
}
