#include "../headers/io.h"
#include "../headers/carte.h"
#include "../headers/monstre.h"
#include "../headers/competence.h"
#include "../headers/personnage.h"
#include <stack>
#include <vector>

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
	Carte jeu_carte;

	//! Personnage choisi par le joueur, à choisir au début du jeu.
	personnage jeu_perso;	//Peut-être passer à un vecteur, pour évolution du code (plusieurs persos)

	//! Vecteur contenant les monstres présents sur la carte
	std::vector<monstre> jeu_monstres;

	//! Compte le nombre de monstres restant sur la carte.
	int jeu_nombre_monstres;

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

	Carte getCarte();

	personnage getPerso();

	std::vector<monstre> getMonstres();

	int getNbMonstres();

	//! Fonction permettant de déterminer comment va démarrer la partie.
	/*!
		Affichage d'un message de bienvenue.
		Choix du personnage.
		Choix de la carte.
		Chargement des monstres.
	*/
	void preparation_partie();

	//! Module de combat
	/*!
		Fonction permettant de gérer le combat.
	*/
};


bool sort_speed(entite a, entite b);

#endif
