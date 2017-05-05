#include <iostream>
#include <string>
#include <vector>

#ifndef CARTE_H
#define CARTE_H
#pragma once

//! Classe qui permet de modéliser une carte en mémoire
/*!

	La classe Carte regroupe le plateau de jeu ainsi que le contenu de chaque case et créer une Carte en allocation dynamique.

	Chaque Carte est caractérisée par:

	un identifiant,

	un nom,

	une description,

	une taille,

	un nombre de monstres,

	un nombre de cases disponibles,

	et un plateau qui lui sont propres.

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
			On demande les coordonnées du spawn du joueur.

			Initialise les coordonnées du spawn de départ du joueur.

			On réactualise le nombre de case dispo.

			\sa long_input()
			\sa c_str()
			\sa atoi(string)
		*/
		void coordonneejoueur();

		//! Coordonnée obstacle
		/*!
			Demande le nombre d'obstacles souhaités,
			vérifie que ce nombre est possible en fonction du nombre de cases dispo sur la carte,
			demande et initialise les coordonnées de chaque obstacle.

			On ne demande pas le genre d'obstacle voulu maintenant.

			On réactualise le nombre de case dispo.

			\sa long_input()
			\sa atoi(string)
			\sa c_str()
		*/
		void coordonneeobstacle();

		//! Coordonnée monstre
		/*!
			Demande le nombre de monstres souhaités.

			Vérifie que ce nombre est possible en fonction de la taille et du nombre de cases dispo sur la carte.

			Demande et initialise les coordonnées de chaque monstre.

			Vérifie que la case choisit est libre.

			On réactualise le nombre de case dispo.

			\sa long_input()
			\sa atoi(string)
			\sa c_str()
		*/
		void coordonneemonstre();

		//! Nombre de ligne du fichier
		/*!

			Compte le nb de ligne du fichier pour créer l'identifiant unique d'un monstre.

			On ouvre le fichier en lecture, on parcours tout le fichier en incrémentant le compteur à chaque lignes.

			\param nomFichier string
			\sa c_str()
			\sa ifstream
			\sa getline()
			\return nbLigne : compteur de nombre de ligne.

		*/
		int nbLigneFichier(std::string nomFichier);

		//! Saisie
		/*!

			Permet de créer une carte : initialiser le type d'obstacle et de monstre.

			On ouvre le fichier carte, on écrit le nom, la description, la taille et le nombre de monstre qui ont été assigné précédemment.

			On parcours ensuite le plateau afin de retrouver la case joueur, les obstacles et de quel type ils sont.

			A chaque fois qu'on tombe sur un monstre on récupère le vecteur de monstres pour faire choisir le monstre au client.

			\sa ofstream
			\sa long_input()
			\sa atoi(string)
			\sa loadAllEntiteFromFile
			\sa afficher_brut()

		*/
		void saisie() ;

		//! Sauvegarde de carte
		/*!

			Ecrit les lignes qui contiennent toutes les caractéristique d'une carte à la fin d'un fichier.

			\param lettreCarte string à écrire
			\param nomfichier string dans lequel écrire
			\sa ofstream
			\sa c_str()
			\sa carteString(string, string)

		*/
		void saveInFile(std::string lettreCarte, std::string nomFichier);

		//! Carte en ligne
		/*!

			Convertit toutes les caractéristiques d'une carte en string.

			On génère l'ID, les obstacles et les entités sur la carte.

			\param lettreCarte string
			\param nomFichier string
			\sa nbLigneFichier(string)
			\sa c_str()
			\sa toString(int)
			\return string ligneFichier


		*/
		std::string carteString(std::string lettreCarte, std::string nomFichier);

		//! Nom
		/*!

			Récupère le nom de la carte.

			\return string nom (de la carte)

		*/
		std::string getName() ;

		//! Description
		/*!

			Récupère la description de la carte.

			\returnt string description (de la carte)

		*/
		std::string getDescription() ;

		//! Taille
		/*!

			Configurer la taille souhaitée de la carte.

		*/
		void setTaille(int taille);

		//! Id
		/*!

				Configurer l'identifiant de la carte.

				Uniquement pour la carte par défaut, pas accessible pour la configuration générale.
		*/
		void setId(std::string id);

		//! Nom
		/*!

			Configurer le nom souhaitée de la carte.

		*/
		void setName(std::string name);

		//! Description
		/*!

			Configurer la description souhaitée pour la carte.

		*/
		void setDescription(std::string desc);

		//! Plateau
		/*!

			Configurer la plateau par rapport à la taille demandé. (Suite au chargement d'une carte).

			\param taille int d'un coté de la carte

		*/
		void setPlateau(int taille);

		//! Case
		/*!

			Configurer la case de ligne i et de colonne j avec la valeur value. (Joueur, monstres, obstacle).

			\param i int ligne
			\param j int colonne
			\param value string valeur de la case
			\sa setPlayerPosition(int, int)

		*/
		void setCase(int i, int j, std::string value);

		//! Nombre de monstre
		/*!

			Configurer le nombre de monstres présent sur la carte.

			\param nbr_monstre int nombre de monstre souhaité

		*/
		void setNbrMonstre(int nbr_monstre);

		//! Case disponible
		/*!

			Configurer le nombre de case disponibles sur la carte.

			\param case_dispo int nombre de case dispo

		*/
		void setCaseDispo(int case_dispo);

		//! Copie de Carte
		/*!

			On copie une Carte.

			On récupère les informations de la carte a_copier pour retourner une nouvelle carte avec ces même caractéristiques.

			\param a_copier Carte
			\return adresse Carte

		*/
		Carte operator=(const Carte a_copier);

		//! Taille
		/*!

			Récupère la taille de la carte.

			\return taille int

		*/
		int getTaille(){return taille;}

		//! Plateau
		/*!

			Récupère le plateau de la carte.

			\return plateau string **

		*/
		std::string ** getPlateau(){return plateau;}

		//! Nombre de monstre
		/*!

			Récupère le nombre de monstre présents sur la carte.

			\return nbr_monstre int nombre de monstre présent sur la carte

		*/
		int getNbrMonstres(){return nbr_monstre;}

		//! Affichage normal
		/*!

			Affiche la carte, avec ce que contient chaque case

			(affichage du plateau)

		*/
		void affichage_normal();

		//! Affichage détaillé
		/*!

			Affiche un petit texte avec tous les détails de la carte:

			Affiche en premier le nom de la carte,

			puis la taille d'un coté de la carte, et le nombre de case au total sur la carte

			par la suite le nombre de monstre qu'il y a sur la carte,

			et enfin affiche la description de la carte

		*/
		void afficher_detail();

		//! Affichage brut
		/*!

			Affiche une phrase avec le nom de la carte, le nombre de cases qu'il y a au total sur la carte et le nombre de monstre qu'il y a exactement sur la carte

		*/
		void afficher_brut();

		//! Case Accessible
		/*!

			Vérifie si une case ij est accessible ou pas.

			\param i entier correspondant à la ligne
			\param j entier correspondant à la colonne
			\return true si la case ij accessible
			\return false si la case ij n'est pas accessible

		*/
		bool caseAccessible(int i, int j);

		//! Echange le contenu de la case plateau[i1][j1] avec ceux du plateau[i2][j2]
		void echangerContenuCase(int i1, int j1, int i2, int j2);

		//! Fait mourir un monstre à la case x,y et enlève 1 à nbr_monstre
		void monstreMort(int x, int y);
};

#endif
