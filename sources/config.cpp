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
			std::cout << "\nConfiguration carte quittée. Retour au menu principal." << std::endl;
			return;
		}
		int input = c_input - '0';                                      //Transcription en chiffres

		while (input <= 0 || input > 3)                //Input incorrect
		{
			std::puts("\nL'élément doit être présent dans la liste! Réessayez!\n\n");
			try
			{
				c_input = de();                                            //Input utilisateur
			}
			catch (int deError)
			{
				std::cout << "\nConfiguration carte quittée. Retour au menu principal." << std::endl;
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

		cout << "\n";

		for (itp = vect_monstre.begin() + monstre::nbElemProt; itp != vect_monstre.end(); itp++)
		{
			cout << ++cpt << "- ";
			(* itp).afficher_brut();
		}

		//Choix action
		cout << "\nVoulez-vous supprimer un de ces monstres, ou en créer un nouveau?" << endl;
		cout << "1- Supprimer monstre existant     2- Créer nouveau monstre     3- Quitter" << endl;

		char c_input;

		try
		{
			c_input = de();                                            //Input utilisateur
		}
		catch (int deError)
		{
			std::cout << "\nConfiguration monstre quittée. Retour au menu principal." << std::endl;
			return;
		}
		int input = c_input - '0';                                      //Transcription en chiffres

		while (input <= 0 || input > 3)                //Input incorrect
		{
			std::puts("\nL'élément doit être présent dans la liste! Réessayez!\n\n");
			try
			{
				c_input = de();                                            //Input utilisateur
			}
			catch (int deError)
			{
				std::cout << "\nConfiguration monstre quittée. Retour au menu principal." << std::endl;
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
		cout << "\nVoulez-vous supprimer un de ces personnages, ou en créer un nouveau?" << endl;
		cout << "1- Supprimer personnage existant     2- Créer nouveau personnage     3- Quitter" << endl;

		char c_input;

		try
		{
			c_input = de();                                            //Input utilisateur
		}
		catch (int deError)
		{
			std::cout << "\nConfiguration personnage quittée. Retour au menu principal." << std::endl;
			return;
		}
		int input = c_input - '0';                                      //Transcription en chiffres

		while (input <= 0 || input > 3)                //Input incorrect
		{
			std::puts("L'élément doit être présent dans la liste! Réessayez!\n");
			try
			{
				c_input = de();                                            //Input utilisateur
			}
			catch (int deError)
			{
				std::cout << "\nConfiguration personnage quittée. Retour au menu principal." << std::endl;
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
	cout << "- Choisissez une taille pour la carte: ";

	string s_input = "";
	int input = 0;

	try
	{
		s_input = long_input();
		input = atoi(s_input.c_str());

		while (isNumber(s_input) == false || (input < 5 || input > 254))
		{
			cout << "\nLa taille de la carte doit être comprise entre " << 5 << " et " << 254 << "! Réessayez!\n\n";
			cout << "- Choisissez une taille pour la carte: ";
			s_input = long_input();
			input = atoi(s_input.c_str());
		}
	}
	catch (int longInputError)
	{
		std::cout << "\nConfiguration de carte quittée. Retour au menu principal." << std::endl;
		return -1;
	}

	return input;
}

void config::creationCarte()
{

	std::cout << "\n- Choisissez un nom pour la carte: ";
	string name = "";
	try
	{
		name = long_input();
	}
	catch (int longInputError)
	{
		std::cout << "\nConfiguration de carte quittée. Retour au menu principal." << std::endl;
		throw longInputError;
	}
	std::cout << "- Choisissez une description pour la carte: " ;

	string desc = "";
	try
	{
		desc = long_input();
	}
	catch (int longInputError)
	{
		std::cout << "\nConfiguration de carte quittée. Retour au menu principal." << std::endl;
		throw longInputError;
	}

	int tail = choix_taille();

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

competence config::createCompetenceEntite(entite dummy, int rang, int manaMax) //Permet à l'utilisateur de créer une compétence pour monstre
{
	cout << "- Configuration compétence " << rang + 1 << " -\n";
	cout << "- Choisissez le nom de la compétence: ";
	string s_input = "";
	int input = 0;

	string skillName = "";
	try
	{
		skillName = long_input();
	}
	catch (int longInputError)
	{
		throw longInputError;
	}

	cout << "- Choisissez les dégâts de la compétence (négatif pour soin): ";
	int skillDamage = 0;
	try
		{
			s_input = long_input();
			input = atoi(s_input.c_str());

			while (isNumber(s_input) == false)
			{
				cout << "\nLa valeur entrée doit être différente de 0! Réessayez!\n\n";
				cout << "- Choisissez les dégâts de la compétence (négatif pour soin): ";
				s_input = long_input();
				input = atoi(s_input.c_str());
			}
			skillDamage = input;
		}
		catch (int longInputError)
		{
			std::cout << std::endl;
			throw longInputError;
		}

	if (dummy.is_personnage())
	{
		int skillManaCost;
		std::cout << "- Choisissez le coût en mana de la compétence (négatif pour régénération): ";
		try
		{
			s_input = long_input();
			input = atoi(s_input.c_str());

			while (isNumber(s_input) == false || input > manaMax)
			{
				cout << "\nLa valeur entrée doit être différente de 0! Réessayez!\n\n";
				std::cout << "- Choisissez le coût en mana de la compétence (négatif pour régénération): ";
				s_input = long_input();
				input = atoi(s_input.c_str());
			}
			skillManaCost = input;
		}
		catch (int longInputError)
		{
			std::cout << std::endl;
			throw longInputError;
		}

		competence creation(skillName, skillDamage, skillManaCost);
		return creation;
	}

	competence creation(skillName, skillDamage);
	return creation;
}
