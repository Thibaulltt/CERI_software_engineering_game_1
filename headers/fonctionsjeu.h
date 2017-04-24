#include <stack>
#include <vector>
#include "../headers/carte.h"
#include "../headers/competence.h"
#include "../headers/io.h"
#include "../headers/monstre.h"
#include "../headers/personnage.h"

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

	//! Vecteur contenant les monstres.
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

	//! Getter de carte de jeu
	Carte getCarte();

	//! Getter de personnage
	personnage getPerso();

	//! Getter de vecteur de monstres
	std::vector<monstre> getMonstres();

	//! Getter de nombre de monstres
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
		Permet de gérer le combat.
		\param id_monstre Identifiant du monstre à combattre.
		\return Un entier: 1 si la partie continue, 0 si elle se termine.
	*/
	int combat(std::string id_monstre);

	//! Recherche de monstre
	/*!
		Permet de trouver l'objet monstre correspondant à la string id trouvée sur une case.
		Si la valeur renvoyée correspond à la fin du vecteur, le monstre n'a pas été trouvé.
		\param id_monstre Identifiant du monstre à trouver.
		\return Un itérateur correspondant à l'élément du vecteur de monstres concerné.
	*/
	std::vector<monstre>::iterator cherche_monstre(std::string id_monstre);

	//! Chargement acteurs combat
	/*!
		Permet de charger tous les acteurs du combat dans un vecteur d'entités.
		\param id_monstre Identifiant du monstre à charger.
		\return Chargement réussi ou non.
		\sa cherche_monstre()
	*/
	bool chargement_entite(std::vector<entite> & vect_entite, std::string id_monstre);

	//! Organisation entités
	/*!
		Permet de trier les entités (selon leur vitesse).
		Identifie également les indices de vecteur correspondant à des personnages.
	*/
	std::vector<int> orga_entites(std::vector<entite> vect_entite);

	//! Identification personnage
	bool is_personnage(entite indiv);

	//! Choix compétence
	competence choix_comp(entite & indiv);

	//! Choix cible
	entite choix_target(competence comp_util, entite indiv, std::vector<entite> vect_entite, std::vector<int> vect_p);

	//! Appliquer compétence
    int appliquer_comp(entite & target, competence comp_util, int & nb_players, int & nb_monsters);
};

bool sort_speed(entite a, entite b);

#endif
