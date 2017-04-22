#include <iostream>
#include <vector>
#include <typeinfo>
#include <termios.h>	// Needed for terminal input manipulation
#include <stdio.h>		// Needed for terminal input manipulation
#include <sstream>
#include "../headers/competence.h"
#include "../headers/monstre.h"
#include "../headers/personnage.h"

#ifndef IO_H
#define IO_H
#pragma once


//! Cet espace sera un espace permettant de définir un buffer custom pour les input, ainsi que de pouvoir afficher tout ce que l'on souhaite.
namespace io
{
	//! Structures qui gardent les paramètres du terminal.
	static struct termios before, after;

	//! Changement des paramètres du terminal
	/*!
		Permet de changer le mode d'entrée de stdin du terminal. Les paramètres présents auparavant sont sauvegardés.
		\param Ech Détermine si on veut que l'entrée utilisateur soit affichée ou pas.
		\sa de(), long_input()
	*/
	extern void ChangeTerminal(bool Ech = 0);

	//! Remet le terminal à zero
	extern void ResetTerminal();

	//! Input
	/*!
		Gestion des entrées utilisateur, ne prends qu'un seul caractère à la fois.
	*/
	extern char de();

	//! Enlève le dernier caractère d'un stringstream.
	extern void removeLastChar(std::stringstream& i);

	//! Long input
	/*!
		magic.gif
	*/
	extern std::string long_input();

	//! Message d'accueil
	/*!
		Affiche un message de bienvenue.
	*/
	void bienvenue();

	//! Retourne la largeur du terminal
	int getTerminalWidth();

	//! Retourne la hauteur du terminal
	int getTerminalHeight();

	//! Vérifie que l'user entre des entier
	/*!
		Cette fonction vérifie que l'entrée utilisateur est bien un entier.

		Mode opératoire :
		- Vérification du failbit de l'entrée utilisateur (std::cin::failbit)
			-# Vidage du buffer
			-# Ignore 256 caractères ou jusqu'a <pre>\n</pre>
			-# Affichage d'un message d'erreur d'entrée utilisateur.
			-# Retourne faux
		- Sinon retourne vrai
		\param x on sait pas ce qu'il fait la, mais il est la.
	*/
	bool checkInput(int x); //Vérifie que l'user entre des entier

	//! Creer une competence
	/*!
		Cette fonction permet de créer rapidement une compétence pour pouvoir l'utiliser facilement après.

		Mode opératoire :
		- On crée les variables qui vont tenir les infos rentrées (skillName, damage, manaCost)
		- On rentre
	*/
	competence createCompetence(); //Creer une competence

	//! Créer une compétence pour monstre (sans mana)
	competence createCompetenceMonstre(); //Créer une compétence pour monstre (sans mana)

	//! Créer un monstre
	monstre createMonstre(); //Créer un monstre

	//! Récupérer les compétences d'un monstre dans le .txt
	std::vector<competence> loadCompetenceFromFile(std::string nomFichier,int numLigne);

	//Retourne un vecteur contenant tous les monstres du fichier .txt
	std::vector<monstre> loadAllMonstreFromFile();

	//! Retourne un vecteur contenant tous les personnages du fichier .txt
	std::vector<personnage> loadAllPersonnageFromFile();

	//! Affichage d'objet.
	/*!
		Affiche le nom et la description d'un objet.
		\param object Objet à afficher.
	*/
	template<typename T> void afficher(T object)
	{
		std::cout << (object).getName();                            //Affiche le nom
		std::cout << ", \"" << (object).getDescription() << "\"";  //Affiche la description
	}


	//! Affichage d'un ensemble d'objets
	/*!
		Parcourt le vecteur de stockage des objets chargés, et les affiche.
		\param vect_element Vecteur d'éléments.
		\param need_desc Description ou non.
		\sa afficher()
	*/
	template<typename T> void liste_elements(std::vector<T> vect_element)
	{
		typename std::vector<T>::iterator itv;                              //Variable de parcours de vecteur
		int cpt = 0;                                                        //Compteur d'éléments

		for (itv = vect_element.begin(); itv != vect_element.end(); itv++)  //Parcours vecteur
		{
			cpt++;                                                          //Incrémentation compteur
			std::cout << cpt%10 << "- ";                                    //Numéro de l'élément (0 - 9)
			afficher((* itv));												//Affichage de l'élément
			std::cout << "   ";
		}
	}


	//! Choix d'un élément unique
	/*!
		Fonction qui prend un vecteur d'éléments en entrée ainsi qu'un booléen (affichage ou non de la description), et affiche puis renvoie l'élément choisi.
		\param vect_element Vecteur de l'élément à choisir.
		\param need_desc Nécessité de description ou non.
		\return L'élement choisi.
		\sa liste_elements(), afficher()
	*/
	template<typename T> T choix_unique_element(std::vector<T> vect_element)
	{
		std::string type_name = typeid(T).name();						//String à partir du type appelant

		while (isdigit(type_name[0]))
		{
			type_name = type_name.substr(1, type_name.size());			//Conservation des caractères pertinents
		}

		std::cout << "Veuillez choisir votre " << type_name << " (1-9): ";

		liste_elements(vect_element);                        			//Affichage des éléments parmi lesquels choisir

		char c_input = de();                                            //Input utilisateur
		int input = c_input - '0';                                      //Transcription en chiffres

		while (input < 0 || input > vect_element.size())                //Input incorrect
		{
			std::puts("Input incorrect. Réessayez!");
			c_input = de();                                             //Input utilisateur
			input = c_input - '0';                                      //Trancription en chiffres
		}

		T choix = vect_element[input - 1];                              //Sélection de l'objet dans son vecteur

		std::cout << std::endl << "Vous avez choisi: ";
		afficher(choix);												//Affichage de l'objet choisi
		std::puts("\n");

		return choix;													//Renvoi de l'objet choisi
    }
}

#endif
