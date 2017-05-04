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
	personnage jeu_perso;

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

	//! Setter de carte de jeu
	void setJeuCarte(Carte jeu_map);

	//! Fonction de déplacement du joueur sur la carte.
	/*!
		Cette fonction permet au joueur de se déplacer sur la carte, en tenant compte des obstacles présents sur ladite carte.

		Mode opératoire :
		- Génère les déplacements possibles grâce à la fonction `genererDeplacement()` ;
		- Génère les entrées utilisateur possibles grâce à la fonction `genererInputAccepte()` ;
		- Va chercher la position actuelle du joueur, puis la stocke dans deux entiers (`x` et `y`, oui je sais ces noms sont très originaux) ;
		- Afficher les mouvements possibles au joueur grâce à la fonction `afficherMouvements()` ;
		- Demande à l'utilisateur où il souhaiterais aller grâce à la fonction `de()`
		- Si le joueur rentre un caractère non compris dans la liste des mouvements possibles :
		  - On ré-affiche les mouvements possibles avec `afficherMouvements()`, cette fois-ci avec un message d'erreur en plus.
		  - On re-demande son choix pour le mouvement grâce à la fonction `de()`
		- On change les coordonnées des entiers `x` et `y` en accord avec la demande de l'utilisateur dans un `switch`.
		- On met à jour l'affichage de la carte grâce à la fonction `updateMap()`
		\post La position du joueur aura changé. La paire d'entiers `currentPlayerPosition` sera donc mise à jour (grâce à `updateMap()`).
		\sa afficherMouvements(), genererDeplacement(), genererInputAccepte(), de() & io::updateMap()
	*/
	void deplacement(int & result);

	//! Fonction permettant d'afficher la carte, puis de demander un déplacement au joueur.
	/*!
		\note Cette fonction est là uniquement pour des fins de tests. La fonctionnalité qu'elle remplit sera remplacée par d'autres méthodes dans la fichier `tests/main.cpp`.
	*/
	void afficherJeu(int & result);

	//! Fonction permettant de générer les déplacements possibles à partir d'une case `i,j` du plateau de jeu.
	/*!
		Cette fonction permet de générer la chaîne de caractères qui affiche les déplacements disponibles au joueur à partir de la case où il se trouve.

		Mode opératoire :
		- On prends les coordonnées actuelles du joueur, que l'on met dans deux entiers créativement appelés `x` et `y`.
		- On prends la taille de la carte du jeu grâce à la fonction `carte::getTaille()`. La taille du plateau nous sert à déterminer si une case existe, enlevant ainsi un peu de temps de calcul lors de l'analyse des cases voisines à celle où se trouve le joueur.
		- On crée une chaîne de caractères. Cette chaîne servira à stocker les déplacements possibles à afficher par la suite au joueur.
		- On vérifie les cases autour du joueur en vérifiant leurs indices et leur contenu (grâce à la fonction `carte::caseAccessible()`)
		- Si la case au dessus du joueur est libre, alors :
		  - On ajoute `Z - Haut` à la chaîne de caractères
		  - On met à 1 le booléen permettant de savoir si la case est accessible ou non.
		- Si la case à la gauche du joueur est libre, alors :
  		  - On ajoute `Q - Gauche` à la chaîne de caractères
  		  - On met à 1 le booléen permettant de savoir si la case est accessible ou non.
		- Si la case en dessous du joueur est libre, alors :
  		  - On ajoute `S - Bas` à la chaîne de caractères
  		  - On met à 1 le booléen permettant de savoir si la case est accessible ou non.
		- Si la case à la droite du joueur est libre, alors :
  		  - On ajoute `D - Droite` à la chaîne de caractères
  		  - On met à 1 le booléen permettant de savoir si la case est accessible ou non.
		- On retourne la châine de caractères générée.
		\param v Vecteur de booléens (`std::vector<bool>`) permettant de savoir quelles cases sont accessibles aux alentours de la case où se trouve le joueur.
		\return Une châine de caractères à afficher au joueur pour qu'il puisse savoir où il peut aller. La chaine est définie par l'expression régulière suivante : `"|"+(" Z - Haut |")?+(" Q - Gauche |")?+(" S - Bas |")?+(" D - Droite |")?`
		\post La fonction ***ne change absolument rien*** au plateau, ni au jeu. Toutes les données générées pour l'analyse des voisins de la case ont une portée locale.
		\sa genererInputAccepte(), deplacement(), carte::caseAccessible() & carte::getTaille()
	*/
	std::string genererDeplacement(std::vector<bool>& v);

	//! Fonction permettant de générer une chaine d'entrées utilisateur acceptables pour le déplacement.
	/*!
		Cette fonction permet de générer la chaîne de caractères qui sera analysée pour accepter ou non un déplacement demandé par le joueur à partir de la case où il se trouve.

		Mode opératoire :
		- Crée une chaîne de caractères (`std::string`) qui contiendra les caractères acceptés lors de l'entrée utilisateur dans la fonction `deplacement()`.
		- Lit le vecteur de booléens rempli dans la fonction `genererDeplacement()` :
		  - Si le premier booléen est à 1 : on ajoute "Zz" à la chaîne (l'utilisateur pourra donc appuyer sur 'Z' ou 'z' et se déplacer)
    		  - Si le second booléen est à 1 : on ajoute "Qq" à la chaîne (l'utilisateur pourra donc appuyer sur 'Q' ou 'q' et se déplacer)
    		  - Si le troisième booléen est à 1 : on ajoute "Ss" à la chaîne (l'utilisateur pourra donc appuyer sur 'S' ou 's' et se déplacer)
    		  - Si le quatrième booléen est à 1 : on ajoute "Dd" à la chaîne (l'utilisateur pourra donc appuyer sur 'D' ou 'd' et se déplacer)
		- Retourne la chaîne de caractères.
		\param b Vecteur de booléens (`std::vector<bool>`) rempli dans la fonction `genererDeplacement()`.
		\return Une chaine de caractères permettant de déterminer si l'entrée utilisateur est acceptable ou pas. La chaîne est définie par l'expression régulière suivante : `"Zz"?+"Qq"?+"Ss"?+"Dd"?`.
		\post La fonction ***ne change absolument rien*** au plateau, ni au jeu. Mais cette chaîne sera utilisée de la facon suivante : pour déterminer si l'utilisateur a rentré une demande de deplacement valide, on vérifie que le caractère rentré est présent dans la chaîne de caractères générée ici. Si le caractère n'est pas présent, on redemande l'entrée utilisateur au joueur.
		\sa genererDeplacement() & deplacements()
	*/
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
