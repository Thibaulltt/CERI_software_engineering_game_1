#include "../headers/io.h"
#include "../headers/carte.h"
#include "../headers/monstre.h"
#include "../headers/competence.h"
#include "../headers/personnage.h"
#include <stack>

#ifndef FONCTIONSJEU_H
#define FONCTIONSJEU_H
#pragma once

using namespace io;

//! Ceci sera la classe du jeu. Elle contient toutes les entités, la carte, ainsi que les fonctions nécessaires à la partie.
/*!
	Cette classe contient les fonctions nécessaires au démarrage de la partie, au combat, ainsi que toutes les fonctions intermédiaires nécessaires au bon fonctionnement de celles-ci.

	Librairies incluses :
		- std::stack ,
		- io ( depuis io.h )
*/
class jeu
{
	//! Carte du jeu, à choisir au début du jeu.
	Carte * jeu_carte;

	//! Personnage choisi par le joueur, à choisir au début du jeu.
	personnage * jeu_perso;
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
		Manque carte pour pouvoir finaliser cette partie.
	*/
	voentiteId demarrer_jeu();

	//! Module de combat
	/*!
		Fonction permettant de gérer le combat.
	*/

	//	voentiteId combat(perso &p, monstre &m);
	//	voentiteId application_coup(perso &p, compet &a, monstre &m, compet &b);
};

//struct ent_combat
//{
//	monstre entite;
//
//	ent_combat(monstre monst);
//	monstre Get_entite();
//	voentiteId util_comp(monstre entite, competence comp);
//};

bool sort_entiteSpeed(monstre a, monstre b);

#endif
