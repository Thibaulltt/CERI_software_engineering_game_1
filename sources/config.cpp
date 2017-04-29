#include <iostream>
#include "../headers/carte.h"
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

    vect_carte = loadAllCarteFromFile(nom_fichier);

    //Affichage toutes cartes
    int cpt = 0;
    for (itc = vect_carte.begin(); itc != vect_carte.end(); itc++)	///Penser à remettre begin() + 1 pour ignorer carte par défaut
	{
		cout << ++cpt << "- ";
        (* itc).afficher_brut();
	}

	char c_input;

	while(1)
	{
		//Choix action
		cout << "Voulez-vous supprimer une de ces cartes, ou en créer une nouvelle?" << endl;
		cout << "1- Supprimer carte existante     2- Créer nouvelle carte     3- Quitter" << endl;

		char c_input = de();                                            //Input utilisateur
		int input = c_input - '0';                                      //Transcription en chiffres

		while (input <= 0 || input > 3)                //Input incorrect
		{
			std::puts("Input incorrect. Réessayez!");
			c_input = de();                                             //Input utilisateur
			input = c_input - '0';                                      //Trancription en chiffres
		}

		if (input == 1)
		{
			deleteLineElement(nom_fichier, vect_carte, "c");
		}
		else if (input == 2)
		{
			creationCarte();
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
    vect_monstre = loadAllEntiteFromFile(duh, nom_fichier);

    //Affichage tous monstres
    int cpt = 0;
    for (itp = vect_monstre.begin(); itp != vect_monstre.end(); itp++)	///Penser à remettre begin() + 3 pour persos par défaut
	{
		cout << ++cpt << "- ";
        (* itp).afficher_brut();
	}

	while(1)
	{
		//Choix action
		cout << "Voulez-vous supprimer un de ces monstres, ou en créer un nouveau?" << endl;
		cout << "1- Supprimer monstre existant     2- Créer nouveau monstre     3- Quitter" << endl;

		char c_input = de();                                            //Input utilisateur
		int input = c_input - '0';                                      //Transcription en chiffres

		while (input <= 0 || input > 3)                //Input incorrect
		{
			std::puts("Input incorrect. Réessayez!");
			c_input = de();                                             //Input utilisateur
			input = c_input - '0';                                      //Trancription en chiffres
		}

		if (input == 1)
		{
			deleteLineElement(nom_fichier, vect_monstre, "m");
		}
		else if (input == 2)
		{
			//Création monstre
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
    vect_perso = loadAllEntiteFromFile(duh, nom_fichier);

    //Affichage tous personnages
    int cpt = 0;
    for (itp = vect_perso.begin(); itp != vect_perso.end(); itp++)	///Penser à remettre begin() + 3 pour persos par défaut
	{
		cout << ++cpt << "- ";
        (* itp).afficher_brut();
	}

	while(1)
	{
		//Choix action
		cout << "Voulez-vous supprimer un de ces personnages, ou en créer un nouveau?" << endl;
		cout << "1- Supprimer personnage existant     2- Créer nouveau personnage     3- Quitter" << endl;

		char c_input = de();                                            //Input utilisateur
		int input = c_input - '0';                                      //Transcription en chiffres

		while (input <= 0 || input > 3)                //Input incorrect
		{
			std::puts("Input incorrect. Réessayez!");
			c_input = de();                                             //Input utilisateur
			input = c_input - '0';                                      //Trancription en chiffres
		}

		if (input == 1)
		{
			deleteLineElement(nom_fichier, vect_perso, "m");
		}
		else if (input == 2)
		{
			//Création personnage
		}
		else
		{
			break;
		}
	}
	return;
}
