#include <iostream>
#include <string>
#include <vector>

#ifndef CARTE_H
#define CARTE_H
#pragma once

// Décrire toute la classe ce qu'il y a dans chaque paramètre
// Comment est construite la carte
// Allocation dynamique tout ça tout ça

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

		//! Nombre de cartes protégées
		static int nbElemProt;

		//! Carte
		/*! Constructeur sans argument */
		Carte();

		//! Carte
		/*!
			Constructeur avec arguments
			\param taille Taille d'un côté, la carte est carrée
			\param nom Nom que l'on va donner à la carte
			\param description Description brève de la carte
		*/
		Carte(int taille, std::string name, std::string description, int nb_monstre);

		//! Coordonnée Joueur
		/*!
			Initialise les coordonnées du spawn de départ du joueur
			On réactualise le nombre de case dispo
		*/
		void coordonneejoueur();

		//! Coordonnée obstacle
		/*!
			Demande le nombre d'obstacles souhaités,
			vérifie que ce nombre est possible en fonction du nombre de cases dispo sur la carte,
			Demande et initialise les coordonnées de chaque obstacle.
			On ne demande pas le genre d'obstacle voulu maintenant.
			On réactualise le nombre de case dispo
		*/
		void coordonneeobstacle();
		void coordonneemonstre();
		int nbLigneFichier(std::string nomFichier);
		void saisie() ;
		void saveInFile(std::string lettreCarte, std::string nomFichier);
		std::string carteString(std::string lettreEntite, std::string nomFichier);
		std::string getName() ;
		std::string getDescription() ;
		void setTaille(int taille);
		void setId(std::string id);
		void setName(std::string name);
		void setDescription(std::string desc);
		void setPlateau(int taille);
		void setCase(int i, int j, std::string value);
		void setNbrMonstre(int nbr_monstre);
		void setCaseDispo(int case_dispo);
		Carte operator=(const Carte a_copier);
		int getTaille(){return taille;}
		std::string ** getPlateau(){return plateau;}
		int getNbrMonstres(){return nbr_monstre;}
		void affichage_normal();
		void afficher_detail();
		void afficher_brut();
		bool caseAccessible(int i, int j);
		Carte CarteDefaut() ; // A modifier nombre de case_dispo = 18 pas 24
};

#endif
