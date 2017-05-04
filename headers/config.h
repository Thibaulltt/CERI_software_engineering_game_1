#include "../headers/competence.h"
#include "../headers/io.h"

#ifndef CONFIG_H
#define CONFIG_H
#pragma once

using namespace io;

class config
{

public:

	//! Configuration de carte
	/*!
		Permet de créer ou de supprimer une carte.
	*/
	void config_carte();

	//! Configuration de monstre
	/*!
		Permet de créer ou de supprimer un monstre.
	*/
	void config_monstre();

	//! Configuration de personnage
	/*!
		Permet de créer ou de supprimer un personnage.
	*/
	void config_perso();

	//! Caractère d'identification d'un objet
	/*!
		Permet de récupérer un caractère identifiant un objet.
		\param objet Objet à identifier
		\return Caractère string identifiant l'objet
	*/
	template<typename T> std::string identif_objet(T objet)
	{
		return objet.getID().substr(0, 1);
	}

	//! Choix de la taille
	/*!
		Permet de choisir la taille de la carte.

		La taille doit être supérieure à 4 et inférieure à 255.
		\return Taille de la carte
	*/
	int choix_taille();

	//! Création d'une carte
	/*!
		Permet de créer une carte et de la rajouter dans le fichier des cartes.

		- Demande un nom pour la carte.
		- Demande une description pour la carte.
		- Demande une taille pour la carte.
		- Construit la carte.
		- Demande le placement du joueur.
		- Demande le placement des obstacles.
		- Demande le placement des monstres.
		- Assigne des monstres aux emplacements choisis.
		- Ecrit la carte dans le fichier.
	*/
	void creationCarte();

	//! Création de compétence
	/*!
		Permet de créer une compétence d'entité.
		\param dummy Type spécifique de l'entité à utiliser
		\param rang Identifiant du numéro de compétence à saisir (parmi le total choisi)
		\return La compétence créée
	*/
	competence createCompetenceEntite(entite dummy, int rang);

	//! Création d'une entité
	/*!
		Permet de créer une entité et de la rajouter dans le fichier correspondant.
		\param dummy Type spécifique de l'entité à utiliser
		\param nom_fichier Nom du fichier dans lequel on veut insérer l'entité
	*/
	template<class T> void creationEntite(T dummy, std::string nom_fichier) //Permet à l'utilisateur de créer une entité avec des caractéristiques choisies
	{
		std::string lettreEntite = identif_objet(dummy);
		std::cout << "- Choisissez un nom pour l'entite : ";
		std::string entiteName;
		try
		{
			entiteName = long_input();
		}
		catch (int longInputError)
		{
			std::cout << std::endl;
			throw longInputError;
		}
		std::cout << "- Choisissez un nombre de points de vie : ";
		int entiteHpMax;
		try
		{
			entiteHpMax = To_int(long_input());
		}
		catch (int longInputError)
		{
			std::cout << std::endl;
			throw longInputError;
		}
		int entiteSpeed;
		std::cout << "- Choisissez la vitesse de l'entité : ";
		try
		{
			entiteSpeed = To_int(long_input());
		}
		catch (int longInputError)
		{
			std::cout << std::endl;
			throw longInputError;
		}
		std::cout << std::endl;
		int entiteManaMax = 0;

		if (dummy.is_personnage())
		{
			std::cout << "- Choisissez le nombre de points de mana de l'entité : ";
			try
			{
				entiteManaMax = To_int(long_input());
			}
			catch (int longInputError)
			{
				std::cout << std::endl;
				throw longInputError;
			}
			std::cout << std::endl;
		}

		int nbComp;
		std::cout << "- Choisissez le nombre de compétences de l'entité : ";
		try
		{
			nbComp = To_int(long_input());
		}
		catch (int longInputError)
		{
			std::cout << std::endl;
			throw longInputError;
		}
		std::cout << std::endl;

		std::vector<competence> skills;;

		for (int i = 0; i < nbComp; i++) //Remplit le tableau de compétences avec de nouvelles compétences
		{
			skills.push_back(createCompetenceEntite(dummy, i));
		}

		T creation = T("", entiteName, entiteHpMax, entiteSpeed, entiteManaMax, "", skills); //Crée le monstre

		creation.saveInFile(lettreEntite, nom_fichier); //Le sauvegarde dans le fichier texte
	}

	//! Supprimer un élément
	/*!
		Cette fonction permet de supprimer un élément choisi par l'utilisateur.

		Mode opératoire :
		- L'utilisateur choisit l'élément à supprimer dans le vecteur
		- On efface du vecteur l'élément choisi
		- Effacement de tout le fichier
		- Réecriture du fichier via le vecteur d'élément actualisé
		\param nomFichier Le nom du fichier .txt dans lequel on veut supprimer une entité
		\param allEntite Vecteur contenant tous les éléments disponibles
		\param lettreEntite String permettant de savoir quel type d'élément on traite
		\param nbElemProt Entier déterminant le nombre d'éléments par défaut à protéger de la modification
	*/
	template <class T> void deleteLineElement(std::string nomFichier, std::vector<T> & allElement, std::string lettreElement, int nbElemProt)
	{
		if (allElement.size() == nbElemProt)
		{
			std::cout << "Il n'y a plus rien à supprimer!";
			return;
		}

		else
		{
			while(1)
			{
				std::cout << "Choisissez l'élément à supprimer (1-9) (q pour annuler): "; //Choix de l'utilisateur
				std::string sInput = long_input();

				if (sInput == "q" || sInput == "Q")
				{
					return;
				}

				int input = atoi(sInput.c_str());

				while (input <= 0 || input > allElement.size() || checkInput(input) == false)                //Input incorrect
				{
					std::puts("Input incorrect. Réessayez!");
					sInput = long_input();                                   //Input utilisateur
					input = atoi(sInput.c_str());

					if (sInput == "q" || sInput == "Q")
					{
						return;
					}
				}

				allElement.erase(allElement.begin() + nbElemProt + (input - 1)); //Suppression de la case dans le vecteur

				int cpt = 0;

				for (int i = 0 + nbElemProt; i < allElement.size(); i++) //Affichage de toutes les entités
				{
					std::cout << ++cpt << "- ";
					allElement[i].afficher_brut();
				}

				cpt = 0;

				std::ofstream fichierElement(nomFichier.c_str(), std::ios::trunc); //Ouverture et suprresion de tout le fichier

				if (fichierElement)
				{
					for (int i = 1; i < allElement.size(); i++)		//i = 1. Ignore carte par défaut
					{
						allElement[i].saveInFile(lettreElement, nomFichier); //Ecriture d'une ligne dans le fichier
					}

					fichierElement.close();
				}
				else
				{
					std::cerr << "Impossible d'ouvrir le fichier." << std::endl;
				}
			}
			return;
		}
	}
};

#endif
