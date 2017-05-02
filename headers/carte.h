#include <iostream>
#include <string>
#include <vector>

#ifndef CARTE_H
#define CARTE_H
#pragma once

//! Classe qui permet de modéliser une carte en mémoire
/*!
	< La description va ici >
*/
class Carte
{
	//! Identifiant de la carte. Sorti de la lecture du fichier texte contenant les cartes.
	std::string id;
	//! Nom donné à la carte. Est présenté au joueur lors de la sélection des cartes.
	std::string nom ;
	//! Description courte de la carte. Est présenté au joueur lors de la sélection des cartes.
	std:: string description;
	//! Taille de la carte. Permet de gérer l'affichage de la carte.
	int taille ;
	//! Plateau bidimensionnel de jeu, constitué de `std::string`. Permet de stocker les infos nécessaires pour chaque case de la carte (exemple : le fait que la case contient un monstre, et quel monstre elle contient).
	std::string ** plateau ;
	//! Nombre de monstres contenus sur la carte. Permet d'arrêter le jeu lorsque ce nombre est égal à 0.
	int nbr_monstre;
	//! Le nombre de cases disponibles sur la carte. On ne sait pas pourquoi elle est là, mais elle est là.
	int case_dispo;

	public:

		//! Nombre de cartes protégées
		static int nbElemProt;

		//! Constructeur sans argument
		/*!
			Construit une carte en initialisant tous ses paramètres à 0 ou NULL.
		*/
		Carte();

		//! Constructeur avec arguments
		/*!
			Construit une carte en affectant ses nom, description, et taille, et construit le plateau de jeu à partir de ce dernier paramètre.
			\param taille Taille d'un côté, la carte est carrée
			\param nom Nom que l'on va donner à la carte
			\param description Description brève de la carte
			\param nb_monstre Nombre de monstres présents sur la carte
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
			demande et initialise les coordonnées de chaque obstacle.

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
