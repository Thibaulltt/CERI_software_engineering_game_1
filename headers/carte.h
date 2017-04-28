#include <iostream>
#include <string>
#include <vector>

#ifndef CARTE_H
#define CARTE_H
#pragma once

class Carte
{
	std::string id;
	std::string nom ;
	std:: string description;
	int taille ;
	std::string ** plateau ;
	int nbr_monstre;
	int case_dispo;

	public:
		//! Carte()
		/*! Constructeur sans argument */
		Carte();
		//! Carte()
		/*! Constructeur avec arguments
		\param taille int
		taille d'un coté, la carte est carré
		\param nom string
		Nom que l'on va donner à la carte
		\param description string
		description brève de la carte
		*/
		Carte(int taille, std::string name, std::string description) ;
		int verif_taille(int taille);
		void coordonneejoueur();
		void coordonneeobstacle();
		void coordonneemonstre();
		void affichage_normal();
		//void affichage() ;
		int nbLigneFichier(std::string nomFichier);
		void sauvegarde() ;
		std::string getName() ;
		std::string getDescription() ;
		void setTaille(int taille);
		void setName(std::string name);
		void setDescription(std::string desc);
		void setPlateau(int taille);
		void setCase(int i, int j, std::string value);
		void setNbrMonstre(int nbr_monstre);
		void setCaseDispo(int case_dispo);
		//bool carte_existe(std::string nom) ;
		//int quel_taille(std::string nom);
		//void suppression(std::string nom);
		Carte operator=(const Carte & a_copier);
		int getTaille(){return taille;}
		std::string** getPlateau(){return plateau;}
		void afficher_detail();
		bool caseAccessible(int i, int j);
		Carte CarteDefaut() ;
};

#endif
