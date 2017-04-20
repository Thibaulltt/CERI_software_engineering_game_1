#include "../headers/io.h"
#include <stack>

#ifndef FONCTIONSJEU_H
#define FONCTIONSJEU_H

using namespace io;

//! Normalement, à ca point là, la carte doit être chargée, le personnage est choisi et chargé, les monstres sont chargés et il ne reste qu'à lancer le jeu.

//using namespace io;

//! Ceci sera la classe du jeu. Elle contient toutes les entités, la carte, ainsi que les fonctions nécessaires à la partie.
/*!
	Cette classe contient les fonctions nécessaires au démarrage de la partie, au combat, ainsi que toutes les fonctions intermédiaires nécessaires au bon fonctionnement de celles-ci.

	Librairies incluses :
		- std::stack ,
		- io ( depuis io.h )
*/
class jeu
{
	// carte jeu_carte;
	// perso jeu_perso;
	// std::stack<> jeu_coups;
	//! Compte le nombre de monstres restant sur la carte.
	int jeu_nombre_monstre;

	public:
		//! Constructeur par défaut sans argument.
		/*!
			Avec ce constructeur, on peut créer toutes les entités du jeu.

			- Chargement de la carte,
			- Création d'un personnage,
			- Création de tous les monstres.

			\sa perso(), carte(), monstre()
		*/
		jeu();
		//! Destructeur par défaut.
		~jeu();
		//! Fonction permettant de déterminer comment va démarrer la partie.
		/*!
			Etant donné que cette fonction utilise des entités externes, il faut que tout le monde aie fini lesdites entités pour que la fonction compile.

			\todo demander à Loic et Ludivine de finir les entités (ou au moins nous dire la syntaxe demandée)
		*/
		void demarrer_jeu();
	//	void combat(perso &p, monstre &m);
	//	void application_coup(perso &p, compet &a, monstre &m, compet &b);
};

#endif
