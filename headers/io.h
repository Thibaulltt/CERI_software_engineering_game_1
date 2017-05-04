#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>	// Needed for terminal input manipulation
#include <termios.h>	// Needed for terminal input manipulation
#include <typeinfo>
#include <vector>
#include "../headers/carte.h"
#include "../headers/competence.h"
#include "../headers/entite.h"
#include "../headers/monstre.h"
#include "../headers/personnage.h"

#ifndef IO_H
#define IO_H
#pragma once


//! Cet espace sera un espace permettant de définir un buffer custom pour les input, ainsi que de pouvoir afficher tout ce que l'on souhaite.
namespace io
{

	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////// Variables  nécessaires ////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////


	//! Structures qui gardent les paramètres du terminal.
	static struct termios before, after;

	//! Variable retennant la valeur de la largeur de la fenêtre du terminal. Elle permet de réduire le nombre de calculs à faire (étant donné que cette valeur est obtenue avec l'ouverture d'un fichier, son calcul prends donc quelques temps).
	extern int TermWidth;
	//! Variable retennant la valeur de la hauteur de la fenêtre du terminal. Elle permet de réduire le nombre de calculs à faire (étant donné que cette valeur est obtenue avec l'ouverture d'un fichier, son calcul prends donc quelques temps).
	extern int TermHeight;

	//! Chaîne de caractères permettant de remettre à zéro la couleur du texte
	extern std::string BLANK;
	//! Chaîne de caractères permettant de rendre le texte affiché de couleur rouge
	extern std::string RED;
	//! Chaîne de caractères permettant de rendre le texte affiché de couleur verte
	extern std::string GREEN;
	//! Chaîne de caractères permettant de rendre le texte affiché de couleur jaune
	extern std::string YELLOW;
	//! Chaîne de caractères permettant de rendre le texte affiché de couleur bleue
	extern std::string BLUE;
	//! Chaîne de caractères permettant de rendre le texte affiché de couleur magenta
	extern std::string MAGENTA;

	//! Variable permettant de retenir à partir de quelle coordonnée "x" la carte est affichée (si la carte est plus grande que la fenêtre de terminal, cette valeur ne sera pas toujours à 0 ...)
	extern int mapPositionX;
	//! Variable permettant de retenir à partir de quelle coordonnée "y" la carte est affichée (si la carte est plus grande que la fenêtre de terminal, cette valeur ne sera pas toujours à 0 ...)
	extern int mapPositiony;

	//! Stocke la position (x) de l'affichage de l'overlay des actions. Nous n'avons pas besoin du Y car l'overlay prends toute la largeur quoi qu'il arrive.
	extern int interactionsOverlayY;

	//! Paire de valeurs (std::pair) gardant la position actuelle du joueur dans
	extern std::pair<int,int> currentPlayerPosition;

	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////// TERMINAL  MANIPULATION ////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////

	//! Changement des paramètres du terminal
	/*!
		Permet de changer le mode d'entrée de stdin du terminal. Les paramètres présents auparavant sont sauvegardés.

		\param Ech Détermine si on veut que l'entrée utilisateur soit affichée ou pas.
		\sa de(), long_input()
	*/
	extern void ChangeTerminal(bool Ech = 0);

	//! Remet le terminal à zero
	/*
		Cette fonction se sert de la valeur TermHeight pour afficher le nombre de lignes vides nécessaires sur la fenêtre terminal afin de vider complètement l'écran.
	*/
	extern void ResetTerminal();

	//! Retourne la largeur du terminal
	extern int getTerminalWidth();

	//! Retourne la hauteur du terminal
	extern int getTerminalHeight();

	//! Efface l'écran.
	extern void clearScreen();

	//! Vérifie la taille du terminal
	extern void checkTerminalSize();

	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////// INPUT  FONCTIONS ///////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////

	//! Input
	/*!
		Gestion des entrées utilisateur, ne prends qu'un seul caractère à la fois.

		Voici son mode opératoire :
		-# On crée une variable (char)
		-# On change la façon dont le terminal gère l'entrée utilisateur avec ChangeTerminal()
		-# On utilise la fonction std::getchar() (qui ne prends maintenant qu'un seul caractère sans avoir besoin d'appuyer sur entrée, grâce à ChangeTerminal())
		-# On remets les paramètres du terminal comme avant avec ResetTerminal()
		-# On retourne l'entrée utilisateur

		\sa ChangeTerminal(); ResetTerminal(); long_input()
	*/
	extern char de();

	//! Entrée utilisateur contenant plus d'un caractère.
	/*!
		Mode opératoire :
		- Utilise les mêmes fonction de changement du terminal que `de()` (avec la seule différence que l'echo des caractères rentrés est activé), mais possède une boucle qui utilise `getchar()` tant que le caractère entré est différent de la touche `ENTREE`.
		- Enlève ensuite le dernier caractère (qui est un caractère `RETOUR_CHARIOT`+`NEWLINE`).
		  - Si la longueur de la chaîne résultante est de 0, alors l'utilisateur n'a rien saisi, donc on lui redemande.
		  - Sinon, on renvoie l'entrée utilisateur.
	*/
	extern std::string long_input();

	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////// OUTPUT FONCTIONS ///////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////

	//! Affichage de la carte
	extern void afficherCarte(Carte&, int, bool reset = 1);

	//! Met à jour l'affichage de la carte.
	extern void updateMap(Carte& jeu_carte, std::pair<int,int> newPlayerPos);

	//! Message d'accueil
	/*!
		Affiche un message de bienvenue.
	*/
	extern void bienvenue();

	//! Fonction permettant d'afficher un overlay sur la carte
	/*!
		Fonction permettant d'afficher un overlay sur la carte, montrant au joueur dans quelles directions il peut aller.
		Ne fait qu'appeller afficherMouvements(std::string deplacements_possibles, std::string erreur_deplacement)

		\sa afficherMouvements(std::string erreur_deplacement) & afficherMouvements(std::string deplacements_possibles, std::string erreur_deplacement)
	*/
	extern void afficherMouvements();
	//! Fonction permettant d'afficher un overlay sur la carte
	/*!
		Fonction permettant d'afficher un overlay sur la carte, montrant au joueur dans quelles directions il peut aller. Il affiche aussi un message d'erreur si demandé.
		Ne fait qu'appeller afficherMouvements(std::string deplacements_possibles, std::string erreur_deplacement)

		\sa afficherMouvements() & afficherMouvements(std::string deplacements_possibles, std::string erreur_deplacement)
	*/
	extern void afficherMouvements(std::string erreur_deplacement);
	//! Fonction permettant d'afficher un overlay sur la carte
	/*!
		Fonction permettant d'afficher un overlay sur la carte, montrant au joueur dans quelles directions il peut aller.
		Ne fait qu'appeller afficherMouvements(std::string deplacements_possibles, std::string erreur_deplacement)

		\sa afficherMouvements() & afficherMouvements(std::string erreur_deplacement)
	*/
	extern void afficherMouvements(std::string deplacements_possibles, std::string erreur_deplacement);

	//! Fonction permettant d'afficher un overlay sur la carte
 	/*!
 		Fonction permettant d'afficher un overlay sur la carte, montrant au joueur dans quelles directions il peut aller.
 		Ne fait qu'appeller afficherMouvements(std::string deplacements_possibles, std::string erreur_deplacement)

 		\sa afficherMouvements() & afficherMouvements(std::string erreur_deplacement) & afficherMouvements(std::string deplacements_possibles, std::string erreur_deplacement)
 	*/
 	extern void afficherMouvements(std::string message, std::string deplacements_possibles, std::string erreur_deplacement);

	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////// MISCELLANEOUS FONCTIONS ////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////

	//! Enlève le dernier caractère d'un stringstream.
	/*!
		Le but de cette fonction est d'enlever le dernier caractère d'un flux de caractères (std::stringstream) étant donné que le C++ ne propose pas de fonction par défaut pour cette fonctionnalité.
		Voici son mode opératoire :
		-# On prends tout le contenu du stringstream et on le met dans une chaîne de caractères (std::string)
		-# Si la chaîne de caractère contient au moins 1 caractère :
		    -# On enlève le dernier caractère affiché sur stdout (en déplacant le curseur vers la droite après avoir affiché un espace)
		    -# Alors on utilise la fonction std::string::erase(std::string::iterator) pour enlever le dernier caractère
		    -# On remplace le contenu du flux de caractère par du vide
		    -# On remet la chaîne de caractère coupée dans le flux.

		\pre La fonction recevra un stringstream d'entrée utilisateur. Son but est d'enlever le dernier caractère entré (cette fonction est appelée dans long_input() dans une condition si le caractère rentré est 127, aussi connu sous le nom de DEL ASCII).
		\post La fonction ne retourne rien, car le seul argument est passé **par argument** et est donc automatiquement modifié.
		\param i C'est un flux de caractères (std::stringstream) à partir duquel il faudra enlever le dernier caractère.
	*/
	extern void removeLastChar(std::stringstream& i);

	//! Vérifie que l'user entre des entiers
	/*!
		Cette fonction vérifie que l'entrée utilisateur est bien un entier.
		Mode opératoire :
		- Vérification du failbit de l'entrée utilisateur (std::cin::failbit)
			-# Vidage du buffer
			-# Ignore 256 caractères ou jusqu'a <code>\n</code>
			-# Affichage d'un message d'erreur d'entrée utilisateur.
			-# Retourne faux
		- Sinon retourne vrai

		\param x on sait pas ce qu'il fait là, mais il est là.
	*/
	extern bool checkInput(int x);

	//!Verifie qu'une ligne est correcte dans un fichier texte d'entités (bon nombre de séparateurs)		 +	//! Créer une competence
 	/*!
 		Cette fonction permet de vérifier qu'une ligne contient bien le bon nombre de séparateurs pour éviter les erreurs dans le chargement d'une entité
 		Mode opératoire:
 		- Parcours de toute la string passée en paramétre
 		- A chaque séparateur trouvé, on ajoute 1 aux compteurs
 		- Si le nombre de séparateurs correspond au nombre défini, on retourne true

 		\param uneLigne Ligne à vérifier
 	*/
 	extern bool checkSeparatorEntite(std::string uneLigne);

	//!Verifie qu'un champ compétences est correct dans un fichier texte d'entités (bon nombre de séparateurs)
	/*!
		Cette fonction permet de vérifier qu'un champ compétences d'une ligne contient bien le bon nombre de séparateurs pour éviter les erreurs dans le chargement d'une entité
		Mode opératoire:
		- Recherche de la ligne dans le fichier
		- Parcours de toute la ligne
		- A chaque séparateur trouvé, on ajoute 1 aux compteurs
		- Si le nombre de séparateurs correspond au nombre défini, on retourne true

		\param nomFichier Le nom du fichier .txt dans lequel on fait la vérification
		\param numLigne Le numéro de la ligne à vérifier
	*/
	extern bool checkSeparatorSkill(std::string nomFichier, int numLigne);

	//! Compte la taille d'une string mieux que la fonction std::string::size(), car elle ne compte pas les accents comme deux caractères.
	extern int taille_str(std::string);

	extern void setPlayerPosition(int, int);

	//! Convertit un string en int
	/*!
		Renvoie 0 si l'input n'est pas convertible.
		\param input String à convertir
		\return Entier obtenu suite à la conversion
	*/
	int To_int(std::string input);

	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////// TEMPLATES DE FONCTIONS ////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////

	//! Affichage d'objet.
	/*!
		Affiche le nom et la description d'un objet.

		\param object Objet à afficher.
	*/
	template<typename T> void afficher(T object)
	{
		std::cout << (object).getName();					//Affiche le nom

		if ((object).getDescription() != "")
		{
			std::cout << ", \"" << (object).getDescription() << "\"";	//Affiche la description
		}
	}

	//! Affichage d'un ensemble d'objets
	/*!
		Parcourt le vecteur de stockage des objets chargés, et les affiche.

		\param vect_element Vecteur d'éléments.
		\sa afficher()
	*/
	template<typename T> void liste_elements(std::vector<T> vect_element)
	{
		typename std::vector<T>::iterator itv;                              //Variable de parcours de vecteur
		int cpt = 0;                                                        //Compteur d'éléments

		for (itv = vect_element.begin(); itv != vect_element.end(); itv++)  //Parcours vecteur
		{
			cpt++;                                                          //Incrémentation compteur
			std::cout << cpt%10 << "- ";                                    //Numéro de l'élément (1 - 9)
			afficher((* itv));												//Affichage de l'élément
			std::cout << "   ";
		}
	}

	//! Choix d'un élément unique
	/*!
		Fonction qui prend un élément, un vecteur d'éléments ainsi qu'un booléen en entrée, et affiche les caractéristiques assignées à l'élément.

		\param element Elément dont les caractéristiques doivent être établies.
		\param vect_element Vecteur de l'élément à choisir.
		\param combat Situation de combat ou non.
		\return L'élement choisi.
		\sa liste_elements(), afficher(), afficher_detail()
	*/
	template<typename T> void choix_unique_element(T & element, std::vector<T> vect_element, bool combat)
	{
		std::string type_name = typeid(T).name();						//String à partir du type appelant

		while (isdigit(type_name[0]))
		{
			type_name = type_name.substr(1, type_name.size());			//Conservation des caractères pertinents
		}

		while (1)
		{
			std::transform(type_name.begin(), type_name.end(), type_name.begin(), ::tolower);
			std::cout << "Veuillez choisir votre " << type_name << " (1-9): ";

			liste_elements(vect_element);                        			//Affichage des éléments parmi lesquels choisir

			char c_input = de();                                            //Input utilisateur
			int input = c_input - '0';                                      //Transcription en chiffres

			while (input <= 0 || input > vect_element.size())                //Input incorrect
			{
				std::puts("Input incorrect. Réessayez!");
				c_input = de();                                             //Input utilisateur
				input = c_input - '0';                                      //Trancription en chiffres
			}

			element = vect_element[input - 1];                              //Sélection de l'objet dans son vecteur

			if (combat == false)
			{
				element.afficher_detail();
				puts("Appuyez sur \"v\" pour valider votre choix, ou sur une autre touche pour revenir au menu de sélection");
				c_input = de();

				if (c_input == 'v' || c_input == 'V')
				{
					std::cout << std::endl << "Vous avez choisi: ";
					afficher(element);												//Affichage de l'objet choisi
					std::puts("\n");
					return;
				}
				else
				{
					continue;
				}
			}
			return;
		}
	}

	//! Affichage des entités du combat
	/*!
		Parcourt le vecteur d'entités, affiche les personnages.
		Parcourt de nouveau le vecteur, affiche les monstres.
		\param vect_entité Le vecteur d'entités à afficher.
		\sa afficher_combat()
	*/
		void aff_combat(std::vector<entite> vect_entite);

	//! Chargement des compétences
	/*!
		Lit une ligne d'un fichier, et remplit un vecteur avec des objets construits à partir des informations récupérées.
		\param nomFichier Le nom du fichier à partir duquel on lit les informations.
		\param numLigne La ligne sur laquelle on recherche les informations.
		\return Un vecteur contenant les compétences créées.
	*/
	std::vector<competence> loadCompetenceFromFile(std::string nomFichier,int numLigne);

	//! Chargement des cartes
	/*!
		Lit toutes les lignes d'un fichier, et remplit un vecteur avec des objets construits à partir des informations récupérées.
		\param nomFichier Le nom du fichier à partir duquel on lit les informations.
		\return Un vecteur contenant les cartes créées.
	*/
	std::vector<Carte> loadAllCarteFromFile(std::string nomFichier);

	//! Chargement des entités
	/*!
        	Lit toutes les lignes d'un fichier, et remplit un vecteur avec des objets construits à partir des informations récupérées.
        	\param temp Objet dummy permettant au compilateur de comprendre de quel type d'objet il s'agit.
        	\param nomFichier Le nom du fichier à partir duquel on lit les informations.
        	\return Un vecteur contenant les entités créées.
        	\sa loadCompetenceFromFile()
	*/
	template<typename T> std::vector<T> loadAllEntiteFromFile(T temp, std::string nomFichier)
	{
		std::vector<T> allEntite; //Vecteur de retour

		T test;

		if (test.is_personnage()) //Création des personnages par défaut
		{
			std::vector<competence> lesCompetences;

			//Personnage Raph
			competence une("Coup de clavier", 30, 20);
			lesCompetences.push_back(une);
			competence deux("C'est magique", 50, 50);
			lesCompetences.push_back(deux);
			competence trois("Trop vieux pour ces conneries", -15, 20);
			lesCompetences.push_back(trois);
			competence quatre("Coup de stylo", 5, -10);
			lesCompetences.push_back(quatre);
			T raph("p00", "Raph", 120, 20, 100, "Raph l'ancetre", lesCompetences);
			allEntite.push_back(raph);
			lesCompetences.clear(); //Vidage du vecteur de compétences

			//Personnage Thibault
			competence unee("Flip Keyboard", 20, 10);
			lesCompetences.push_back(unee);
			competence deuxx("Flip table", 60, 55);
			lesCompetences.push_back(deuxx);
			competence troixx("Recharge de sel", -10, 15);
			lesCompetences.push_back(troixx);
			competence quatree("Appel du Macbook", 7, -10);
			lesCompetences.push_back(quatree);
			T thibault("p01", "Thibault", 150, 15, 100, "Too salty", lesCompetences);
			allEntite.push_back(thibault);
			lesCompetences.clear(); //Vidage du vecteur de compétences

			//Personnage Bobby
			competence uneee("Attaque rapide", 15, 5);
			lesCompetences.push_back(uneee);
			competence deuxxx("Attaque chargée", 70, 65);
			lesCompetences.push_back(deuxxx);
			competence troixxx("Need healing", -15, 70);
			lesCompetences.push_back(troixxx);
			competence quatreee("Need more mana", 5, -20);
			lesCompetences.push_back(quatreee);
			T bobby("p02", "Bobby", 90, 30, 95, "Bobby ftw", lesCompetences);
			allEntite.push_back(bobby);
			lesCompetences.clear();

			personnage::nbElemProt = 3;
		}

		if (test.is_monstre()) //Création des monstres par défaut
		{
			std::vector<competence> lesCompetences;

			//Monstre Orc
			competence une("Coup hache", 30, 0);
			lesCompetences.push_back(une);
			competence deux("Coup de marteau", 22, 0);
			lesCompetences.push_back(deux);
			competence trois("Coup de fouet", 15, 0);
			lesCompetences.push_back(trois);
			T orc("m00", "Orc", 95, 10, 0, "", lesCompetences);
			allEntite.push_back(orc);
			lesCompetences.clear(); //Vidage du vecteur de compétences

			//Monstre Gobelin
			competence unee("Vol d'argent", 15, 0);
			lesCompetences.push_back(unee);
			competence deuxx("Fabrication d'explosifs", 30, 0);
			lesCompetences.push_back(deuxx);
			competence troixx("Fourberie", 20, 0);
			lesCompetences.push_back(troixx);
			T gobelin("m01", "Gobelin", 90, 20, 0, "", lesCompetences);
			allEntite.push_back(gobelin);
			lesCompetences.clear(); //Vidage du vecteur de compétences

			//Monstre elfe
			competence uneee("Tir à l'arc", 25, 0);
			lesCompetences.push_back(uneee);
			competence deuxxx("Vision d'aigle", 15, 0);
			lesCompetences.push_back(deuxxx);
			competence troixxx("Magie elfique", 20, 0);
			lesCompetences.push_back(troixxx);
			T elfe("m02", "Elfe", 85, 18, 0, "", lesCompetences);
			allEntite.push_back(elfe);
			lesCompetences.clear();

			monstre::nbElemProt = 3;
		}

		std::string uneLigne=""; //Variable stockant une ligne

		int nbSeparateur = 0; //Compteur de /
		int nbBarre = 0; //Compteur de |
		std::string sentiteId;
		std::string sentiteName;
		std::string sentiteHpMax;
		std::string sentiteSpeed;
		std::string sentiteManaMax;
		std::string entiteDescription;
		int entiteHpMax;
		int entiteSpeed;
		int entiteManaMax;
		int cptLigne=0;
		std::vector<competence> allSkills;

		char parcoursCarac; //Parcours de la ligne

		std::ifstream fichierEntite(nomFichier, std::ios::in); //Ouverture en mode lecture

		if(fichierEntite)
		{
			while (getline(fichierEntite, uneLigne)) //Parcours de tout le fichier et stockage d'une ligne
			{
				if(checkSeparatorEntite(uneLigne) == true) //Vérification que la ligne est correcte
				{
					cptLigne++; //Reset de toutes les variables afin de stocker une nouvelle ligne
					sentiteName="";
					sentiteId="";
					sentiteHpMax="";
					entiteHpMax=0;
					sentiteSpeed="";
					entiteSpeed=0;
					sentiteManaMax="";
					entiteManaMax=0;
					nbSeparateur=0;
					nbBarre=0;
					entiteDescription="";
					allSkills.clear();


					for(int i=0; i<uneLigne.length(); i++) //Analyse de la ligne
					{
						parcoursCarac = uneLigne[i];
					 //   if(nbSeparateur <4) // Récupération des carac. d'un monstre
					   // {
						if ((parcoursCarac == '/') || (parcoursCarac == '|'))
						{
							nbSeparateur++;
						}

						if (nbSeparateur == 0) // Champ entiteId
						{
							sentiteId+=parcoursCarac;
						}

						if (nbSeparateur == 1) //Champ Nom
						{
							if (parcoursCarac == '/')
							{
								continue;
							}
							sentiteName+=parcoursCarac;
						}

						if (nbSeparateur == 2) //Champ entiteHpMax
						{
							if (parcoursCarac == '/')  continue;
							sentiteHpMax+=parcoursCarac;
						}

						if (nbSeparateur == 3) //Champ vitesse
						{
							if (parcoursCarac == '/')  continue;
							sentiteSpeed+=parcoursCarac;
						}

						if(nbSeparateur == 4)
						{
							continue;
						}

						if(nbSeparateur >= 5) //Champ compétence + entiteManaMax + entiteDescription
						{
							if(parcoursCarac == '|')
							{
								nbBarre++;
							}

							if(nbBarre == 0) continue;

							if (nbBarre == 1) //Champ entiteManaMax
							{
								if(parcoursCarac=='|') continue;
								sentiteManaMax+=parcoursCarac;
							}

							if (nbBarre == 2) //Champ entiteDescription
							{
								if(parcoursCarac=='|') continue;
								entiteDescription+=parcoursCarac;
							}

							if (nbBarre==3)
							{
								break;
							}
						}
					}
				}


				std::istringstream (sentiteHpMax) >> entiteHpMax; //Conversion string to int
				std::istringstream (sentiteSpeed) >> entiteSpeed; //Conversion string to int
				std::istringstream (sentiteManaMax) >> entiteManaMax; //Conversion string to int
				std::istringstream (sentiteManaMax) >> entiteManaMax; //Conversion string to int
				if (checkSeparatorSkill(nomFichier, cptLigne) == true) //Verification que le champ compétence est correct
				{
					allSkills = loadCompetenceFromFile(nomFichier, cptLigne); //Récupération des compétences
					T creation(sentiteId, sentiteName, entiteHpMax, entiteSpeed, entiteManaMax, entiteDescription, allSkills); //Création de l'entite
					allEntite.push_back(creation); //Stockage du perso dans le vecteur de retour
				}

				else
					continue;

			}
			fichierEntite.close();
		}

		else
		{
			std::cerr << "Impossible d'ouvrir le fichier." << std::endl;
		}

		return allEntite;
	}

	template<typename T> std::string toString( const T & valeur ) //Conversion de n'importe quoi en string
	{
		std::ostringstream flux;
		flux << valeur;
		return flux.str();
	}

	bool inputSepCheck(std::string input);
}

#endif
