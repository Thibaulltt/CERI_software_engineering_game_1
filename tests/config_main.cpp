#include "../headers/config.h"
#include "../headers/io.h"

using namespace io;
using namespace std;

int main ()
{
	config test;

	while (1)
	{
		puts("\nBienvenue dans le module de configuration de The Game \n\n Choisissez l'élément à configurer: ");

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
			try
			{
				test.config_carte();
			}
			catch (...)
			{return 0;}
			break;

		case 2:
			try
			{
				test.config_monstre();
			}
			catch(...)
			{return 0;}
			break;

		case 3:
			try
			{
				test.config_perso();
			}
			catch (...)
			{return 0;}
			break;

		default:
			goto fin;
		}
	}
fin:return 0;
}
