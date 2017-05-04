#include <iostream>
#include "../headers/carte.h"
#include "../headers/competence.h"
#include "../headers/config.h"
#include "../headers/entite.h"
#include "../headers/io.h"


using namespace io;
using namespace std;

void config::config_carte()
{
	string nom_fichier = "fichierCarte.txt";
	vector<Carte> vect_carte;
	vector<Carte>::iterator itc;

	while(1)
	{
		vect_carte = loadAllCarteFromFile(nom_fichier);

		int cpt = 0;
		for (itc = vect_carte.begin() + Carte::nbElemProt; itc != vect_carte.end(); itc++)
		{
			cout << ++cpt << "- ";
			(* itc).afficher_brut();
		}

		//Choix action
		cout << "\nVoulez-vous supprimer une de ces cartes, ou en créer une nouvelle?" << endl;
		cout << "1- Supprimer carte existante     2- Créer nouvelle carte     3- Quitter" << endl;

		char c_input;

		try
		{
			c_input = de();                                            //Input utilisateur
		}
		catch (int deError)
		{
			std::cout << "Configuration carte quitée. Retour au menu principal." << std::endl;
			return;
		}
		int input = c_input - '0';                                      //Transcription en chiffres

		while (input <= 0 || input > 3)                //Input incorrect
		{
			std::puts("Input incorrect. Réessayez!");
			try
			{
				c_input = de();                                            //Input utilisateur
			}
			catch (int deError)
			{
				std::cout << "Configuration carte quitée. Retour au menu principal." << std::endl;
				return;
			}
			input = c_input - '0';                                      //Trancription en chiffres
		}

		if (input == 1)
		{
			deleteLineElement(nom_fichier, vect_carte, "c", Carte::nbElemProt);
		}
		else if (input == 2)
		{
			try
			{
				creationCarte();
			}
			catch (int creationCarteError)
			{
				return;
			}
		}
		else
		{
			break;
		}
	}
	return;
}

void config::config_monstre()
{
	string nom_fichier = "fichierMonstre.txt";
	vector<monstre> vect_monstre;
	vector<monstre>::iterator itp;
	monstre duh;

	while(1)
	{
		vect_monstre = loadAllEntiteFromFile(duh, nom_fichier);
		int cpt = 0;

		for (itp = vect_monstre.begin() + monstre::nbElemProt; itp != vect_monstre.end(); itp++)
		{
			cout << ++cpt << "- ";
			(* itp).afficher_brut();
		}

		//Choix action
		cout << "Voulez-vous supprimer un de ces monstres, ou en créer un nouveau?" << endl;
		cout << "1- Supprimer monstre existant     2- Créer nouveau monstre     3- Quitter" << endl;

		char c_input;

		try
		{
			c_input = de();                                            //Input utilisateur
		}
		catch (int deError)
		{
			std::cout << "Configuration monstre quitée. Retour au menu principal." << std::endl;
			return;
		}
		int input = c_input - '0';                                      //Transcription en chiffres

		while (input <= 0 || input > 3)                //Input incorrect
		{
			std::puts("Input incorrect. Réessayez!");
			try
			{
				c_input = de();                                            //Input utilisateur
			}
			catch (int deError)
			{
				std::cout << "Configuration monstre quitée. Retour au menu principal." << std::endl;
				return;
			}
			input = c_input - '0';                                      //Trancription en chiffres
		}

		if (input == 1)
		{
			deleteLineElement(nom_fichier, vect_monstre, "m", monstre::nbElemProt);
		}
		else if (input == 2)
		{
			try
			{
				creationEntite(duh, nom_fichier);
			}
			catch (int catchError)
			{
				std::cout << "Retour au menu principal." << std::endl;
				return;
			}
		}
		else
		{
			break;
		}
	}
	return;
}

void config::config_perso()
{
	string nom_fichier = "fichierPersonnage.txt";
	vector<personnage> vect_perso;
	vector<personnage>::iterator itp;
	personnage duh;

	while(1)
	{
		vect_perso = loadAllEntiteFromFile(duh, nom_fichier);
		int cpt = 0;

		for (itp = vect_perso.begin() + personnage::nbElemProt; itp != vect_perso.end(); itp++)	///Penser à remettre begin() + 3 pour persos par défaut
		{
			cout << ++cpt << "- ";
			(* itp).afficher_brut();
		}

		//Choix action
		cout << "Voulez-vous supprimer un de ces personnages, ou en créer un nouveau?" << endl;
		cout << "1- Supprimer personnage existant     2- Créer nouveau personnage     3- Quitter" << endl;

		char c_input;

		try
		{
			c_input = de();                                            //Input utilisateur
		}
		catch (int deError)
		{
			std::cout << "Configuration carte quitée. Retour au menu principal." << std::endl;
			return;
		}
		int input = c_input - '0';                                      //Transcription en chiffres

		while (input <= 0 || input > 3)                //Input incorrect
		{
			std::puts("Input incorrect. Réessayez!");
			try
			{
				c_input = de();                                            //Input utilisateur
			}
			catch (int deError)
			{
				std::cout << "Configuration carte quitée. Retour au menu principal." << std::endl;
				return;
			}
			input = c_input - '0';                                      //Trancription en chiffres
		}

		if (input == 1)
		{
			deleteLineElement(nom_fichier, vect_perso, "p", personnage::nbElemProt);
		}
		else if (input == 2)
		{
			try
			{
				creationEntite(duh, nom_fichier);
			}
			catch (int catchError)
			{
				std::cout << "Retour au menu principal." << std::endl;
				return;
			}
		}
		else
		{
			break;
		}
	}
	return;
}

int config::choix_taille()
{
	puts("\n- Choix taille -");

	string s_input;

	try
	{
		s_input = long_input();                                            //Input utilisateur
	}
	catch (int longInputError)
	{
		std::cout << "Choix de la taille quitté. Retour au menu principal" << std::endl;
		return -1;
	}

	while (inputSepCheck(s_input) == false)
	{
		puts("\n Input incorrect! Réessayez!\n");
		puts("\n- Choix taille -");
		try
		{
			s_input = long_input();                                            //Input utilisateur
		}
		catch (int longInputError)
		{
			std::cout << "Choix de la taille quitté. Retour au menu principal" << std::endl;
			return -1;
		}
	}

	int input = To_int(s_input);

	while (input < 5 || input > 254)                				//Input incorrect
	{
		puts("Taille impossible, veuillez choisir une taille entre 5 et 254!");
		try
		{
			s_input = long_input();                                            //Input utilisateur
		}
		catch (int longInputError)
		{
			std::cout << "Choix de la taille quitté. Retour au menu principal" << std::endl;
			return -1;
		}
		input = To_int(s_input);
	}

	return input;
}

void config::creationCarte()
{

	std::cout << "- Choisissez une nom pour la carte : ";
	string name;
	try
	{
		name = long_input();
	}
	catch (int longInputError)
	{
		std::cout << "Configuration de carte quitée. Retour au menu principal." << std::endl;
		throw longInputError;
	}
	std::cout << std::endl << "- Choisissez une description pour la carte : " ;
	string desc;
	try
	{
		desc = long_input();
	}
	catch (int longInputError)
	{
		std::cout << "Configuration de carte quitée. Retour au menu principal." << std::endl;
		throw longInputError;
	}
	std::cout << endl;
	int tail = choix_taille();
	if (tail == -1)
		return;

	Carte a_creer(tail, name, desc, 0);
	try
	{
		a_creer.coordonneejoueur();
		a_creer.coordonneeobstacle();
		a_creer.coordonneemonstre();

		a_creer.saisie();
	}
	catch (int coodonneesError)
	{
		throw coodonneesError;
	}
}

competence config::createCompetenceEntite(entite dummy, int rang) //Permet à l'utilisateur de créer une compétence pour monstre
{
	cout << "- Configuration compétence " << rang + 1 << " -\n";
	cout << "- Choisissez le nom de la compétence : ";
	string skillName;
	try
	{
		skillName = long_input();
	}
	catch (int longInputError)
	{
		throw longInputError;
	}
	cout << endl << "- Choisissez le nombre de points de dégâts pour la compétence : ";
	int skillDamage;
	try
	{
		skillDamage = To_int(long_input());
	}
	catch (int longInputError)
	{
		throw longInputError;
	}

	if (dummy.is_personnage())
	{
		int skillManaCost;
		std::cout << "- Choisissez le coût en mana compétence (négatif pour régénération) : ";
		try
		{
			skillManaCost = To_int(long_input());
		}
		catch (int longInputError)
		{
			throw longInputError;
		}
		competence creation(skillName, skillDamage, skillManaCost);
		return creation;
	}

	competence creation(skillName, skillDamage);
	return creation;
}
