#include <iostream>
#include <string>
#include <vector>

#ifndef CARTE_H
#define CARTE_H
#pragma once

// Décrire toute la classe ce qu'il y a dans chaque paramètres
// Comment est construite la carte
// allocation dynamique tout ca tout ca

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

		//! Carte
		/*! Constructeur sans argument */
		Carte();

		//! Carte
		/*! Constructeur avec arguments
		\param taille int
		taille d'un coté, la carte est carré
		\param nom string : Nom que l'on va donner à la carte
		\param description string : description brève de la carte
    */
		Carte(int taille, std::string name, std::string description) ;

		Carte(Carte&);

		//! Verif_taille()
		/*!  Verifie que la taille de la carte est acceptable
			La taille doit être supérieur à 4 et inférieur à 255
			\param taille int : taille à tester. Si la taille n'entre pas dans les critères, on redemande la taille
			\return taille acceptée
		*/
		int verif_taille(int taille);

		//! Coordonnée Joueur
		/*! Initialise les coordonnées du spawn de départ du joueur
			On réactualise le nombre de case dispo
		*/
		void coordonneejoueur();

		//! Coordonnée obstacle
		/*! Demande le nombre dobstacle souhaité,
			vérifie que ce nombre est possible en fonction du nombre de cases dispo sur la carte,
			Demande et initailise les coordonnées de chaque obstacles.
			On ne demande pas le genre d'obstacle voulu maintenant.
			On réactualise le nombre de case dispo
		*/
		void coordonneeobstacle();
		void coordonneemonstre();
		void affichage_normal();
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

		Carte operator=(const Carte & a_copier);
		int getTaille(){return taille;}
		std::string** getPlateau(){return plateau;}
		void afficher_detail();
		bool caseAccessible(int i, int j);
  	Carte CarteDefaut() ; // A modifier nombre de case_dispo = 18 pas 24
};

#endif
