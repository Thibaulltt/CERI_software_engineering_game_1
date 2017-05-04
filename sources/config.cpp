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
			deleteLineElement(nom_fichier, vect_carte, "c", Carte::nbElemProt);
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
			deleteLineElement(nom_fichier, vect_monstre, "m", monstre::nbElemProt);
		}
		else if (input == 2)
		{
			creationEntite(duh, nom_fichier);
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
			deleteLineElement(nom_fichier, vect_perso, "p", personnage::nbElemProt);
		}
		else if (input == 2)
		{
			creationEntite(duh, nom_fichier);
		}
		else
		{
			break;
		}
	}
	return;
}

string config::choix_carac_string(string carac)
{
	cout << "\n- Choix " << carac << " -\n";

	string input = long_input();

	while (inputSepCheck(input) == false)
	{
		puts("\n Input incorrect! Réessayez!\n");
		cout << "\n- Choix " << carac << " -\n";
		input = long_input();
	}

	return input;
}

int config::choix_carac_int(string carac)
{
	cout << "\n- Choix " << carac << " -\n";

	string s_input = long_input();                                            //Input utilisateur

	while (inputSepCheck(s_input) == false)
	{
		puts("\n Input incorrect! Réessayez!\n");
		cout << "\n- Choix " << carac << " -\n";
		s_input = long_input();
	}

	int input = To_int(s_input);

	while(input == 0)
	{
		cout << "Veuillez choisir un entier différent de 0! \n - Choix " << carac << " -\n";
		s_input = long_input();                                            //Input utilisateur
		input = To_int(s_input);
	}

	return input;
}

int config::choix_taille()
{
	puts("\n- Choix taille -");

	string s_input = long_input();                                            //Input utilisateur

	while (inputSepCheck(s_input) == false)
	{
		puts("\n Input incorrect! Réessayez!\n");
		puts("\n- Choix taille -");
		s_input = long_input();
	}

	int input = To_int(s_input);

	while (input < 5 || input > 254)                				//Input incorrect
	{
		puts("Taille impossible, veuillez choisir une taille entre 5 et 254!");
		s_input = long_input();
		input = To_int(s_input);
	}

	return input;
}

void config::creationCarte()
{
	string name = choix_carac_string("nom");
	string desc = choix_carac_string("description");
	int tail = choix_taille();

	Carte a_creer(tail, name, desc, 0);

	a_creer.coordonneejoueur();
	a_creer.coordonneeobstacle();
	a_creer.coordonneemonstre();

	a_creer.saisie();
}

competence config::createCompetenceEntite(entite dummy, int rang, int manaMax) //Permet à l'utilisateur de créer une compétence pour monstre
{
	cout << "- Configuration compétence " << rang + 1 << " -\n";

	string skillName = choix_carac_string("nom compétence");
	int skillDamage = choix_carac_int("dégats compétence (négatif pour soin)");

	if (dummy.is_personnage())
	{
		int skillManaCost = choix_carac_int("coût en mana compétence (négatif pour régénération)");

		while (skillManaCost > manaMax)
		{
            cout << "Coût en mana supérieur à la mana disponible (" << manaMax << ")!\n";
			skillManaCost = choix_carac_int("coût en mana compétence (négatif pour régénération)");
		}
		competence creation(skillName, skillDamage, skillManaCost);
		return creation;
	}

	competence creation(skillName, skillDamage);
	return creation;
}
