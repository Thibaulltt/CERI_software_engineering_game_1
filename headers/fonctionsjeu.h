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

	Inclut la librairie io.
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
	int jeu_nombre_monstres = 1;							///Temporaire!!

public:
	//! Constructeur par défaut sans argument.
	/*!
		Affichage d'un message de bienvenue.
		Choix du personnage.
		Choix de la carte.
		Chargement des monstres.

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

	void deplacement();

	void afficherJeu();

	std::string genererDeplacement(std::vector<bool>& v);

	std::string genererInputAccepte(std::vector<bool> b);

	//! Module de combat
	/*!
		Permet de gérer le combat.
		- Charge les entités (personnages et monstres) contenus dans la case.
		- Identifie les personnages et leur nombre.
		- Identifie les monstres et leur nombre.
		- Pour chaque acteur, choix d'une compétence, puis d'une cible, puis application des effets.
		\param id_monstre Identifiant du monstre à combattre.
		\return Un entier: 1 si la partie continue, 0 si elle se termine.
		\sa chargement_entite(), orga_entites(), aff_combat(), choix_comp(), choix_target(), appliquer_comp()
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
		\param vect_entite Vecteur où chercher le monstre.
		\param id_monstre Identifiant du monstre à charger.
		\return Chargement réussi ou non.
		\sa cherche_monstre()
	*/
	bool chargement_entite(std::vector<entite> & vect_entite, std::string id_monstre);

	//! Organisation entités
	/*!
		Permet de trier les entités (selon leur vitesse).
		Identifie également les indices de vecteur correspondant à des personnages et les stocke dans un vecteur (pour ciblage par monstres).
		\param vect_entite Vecteur de personnages à trier.
		\return Un vecteur d'entités utilisées pour le combat.
	*/
	std::vector<int> orga_entites(std::vector<entite> & vect_entite);

	//! Choix compétence
	/*!
		Permet de sélectionner une compétence par input parmi une liste tirée d'un vecteur (spécifique à chaque entité)
		Vérifie la possibilité du lancer (niveau de mana).
		Si l'entité est un monstre, le choix est aléatoire.
		\param indiv L'entité qui joue actuellement.
		\return Une compétence parmi les compétences utilisables.
		\sa choix_unique_element()
	*/
	competence choix_comp(entite & indiv);

	//! Choix cible
	/*!
        Permet de choisir une cible parmi une liste tirée d'un vecteur de cibles disponibles.
        Si l'entité est un monstre, le choix est aléatoire (uniquement parmi les cibles personnages).
        \param comp_util La compétence à utiliser.
        \param indiv L'entité qui joue actuellement.
        \param vect_entite Le vecteur duquel on tire la cible de la compétence.
        \param vect_p Vecteur permettant d'identifier les personnages parmi toutes les entités.
        \return Une entité, cible de la compétence.
        \sa choix_unique_element()
	*/
	entite choix_target(competence comp_util, entite & indiv, std::vector<entite> & vect_entite, std::vector<int> vect_p);

	//! Appliquer compétence
	/*!
        	Permet d'appliquer les effets de la compétence choisie sur la cible choisie.
        	Si la cible meurt, décrémente le compteur de personnages/monstres vivants.
        	Supprime les cibles mortes du vecteur d'entités.
        	\param target Cible de la compétence.
        	\param vect_entite Le vecteur duquel on tire la cible de la compétence.
        	\param comp_util La compétence à utiliser.
        	\param nb_players Le nombre total de joueurs de la partie.
        	\param nb_monsters Le nombre de monstres du combat en cours.
		\return Un entier: 1 si tous les monstres sont morts, 0 si tous les joueurs sont morts, 2 sinon.
		\sa enleverVie()
	*/
    int appliquer_comp(entite target, std::vector<entite> & vect_entite, competence comp_util, int & nb_players, int & nb_monsters);
};

//! Tri d'entités
/*!
	Trie des entités selon la valeur de leur attribut de vitesse.
	\param a Entité par rapport à laquelle on trie.
	\param b Entité à trier.
	\return Un booléen: true si la vitesse de a est supérieure à la vitesse de b.
*/
bool sort_speed(entite a, entite b);

#endif
