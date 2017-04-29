#include "../headers/carte.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <string>
#include "../headers/io.h"

using namespace io;
using namespace std;

Carte :: Carte()
{
	this->id = "";
	this->nom = "";
	this->description = "";
	this->taille = 0;
	this->plateau = NULL;
	this->nbr_monstre = 0 ;
	this->case_dispo = 0;

}

Carte :: Carte (int taille, string name, string desc, int nb_monstre)
{
	this->nom = name;
	this->description = desc;
	this->taille = taille;

	this->plateau = new string * [taille];
	for (int i = 0; i < taille ; i++)
	{
		plateau[i] = new string [taille];
	}

	for (int i = 0; i < taille; i++)
	{
		for (int j = 0; j < taille; j++)
		{
			plateau[i][j] = "v";
		}
	}

	this -> nbr_monstre = nb_monstre;
	this -> case_dispo = taille * taille;
}

void Carte :: coordonneejoueur()
{
	puts("- Choix placement joueur -");

	int coordonneejoueur1 = 0;
	int coordonneejoueur2 = 0;
	bool placement_fait = false;

	while (placement_fait == false)
	{
		cout << "Choisissez la premiere coordonnée où le joueur doit apparaître: ";
		string s_input = long_input();
		coordonneejoueur1 = atoi(s_input.c_str());

		cout << "Choisissez la deuxieme coordonnée où le joueur doit apparaître: ";
		s_input = long_input();
		coordonneejoueur2 = atoi(s_input.c_str());

		if (coordonneejoueur1 < taille && coordonneejoueur2 < taille && coordonneejoueur1 >= 0 && coordonneejoueur2 >= 0)
		{
			plateau[coordonneejoueur1][coordonneejoueur2] = "j";
			placement_fait = true;
		}
		else
		{
			puts("Vos coordonnées sont hors de la carte!!");
		}
	}
	case_dispo = case_dispo - 1;
}

void Carte::coordonneeobstacle()
{
	puts("Choix placement obstacles");

	int nbr_obstacle=0;
	int coordonneeobstacle1 = 0;
	int coordonneeobstacle2 = 0;
	int i = 1;

	cout << "Combien d'obstacle voulez-vous sur la carte?";
	string s_input = long_input();
	nbr_obstacle = atoi(s_input.c_str());

	while (nbr_obstacle >= case_dispo)
	{
		cout << "Vous avez choisi trop d'obstacles.\nCombien d'obstacles voulez-vous sur la carte?";
		s_input = long_input();
		nbr_obstacle = atoi(s_input.c_str());
	}

	while (i <= nbr_obstacle)
	{
		cout << "Choisissez la premiere coordonnée où l'obstacle doit apparaître :";
		s_input = long_input();
		coordonneeobstacle1 = atoi(s_input.c_str());

		cout << "Choisissez la deuxieme coordonnée où l'obstacle doit apparaître :";
		s_input = long_input();
		coordonneeobstacle2 = atoi(s_input.c_str());

		if (coordonneeobstacle1 < taille && coordonneeobstacle2 < taille && coordonneeobstacle1 >= 0 && coordonneeobstacle2 >= 0)
		{
			if (plateau[coordonneeobstacle1][coordonneeobstacle2] == "v")
			{
				plateau[coordonneeobstacle1][coordonneeobstacle2] = "o";
				i++;
			}
			else
			{
				puts("Cette case est deja occupée, veuillez en choisir une autre ");
			}
		}
		else
		{
			puts("Vos coordonnées sont hors de la carte!!");
		}
	}
	case_dispo = case_dispo - nbr_obstacle;
}

void Carte::coordonneemonstre()
{
	puts("- Choix placement monstres -");;

	int nombre_monstre = 0;
	int coordonneemonstre1 = 0;
	int coordonneemonstre2 = 0;
	int i = 1;

	cout << "Combien de monstres voulez-vous sur la carte?";
	string s_input = long_input();
	nombre_monstre = atoi(s_input.c_str());

	while ((nombre_monstre < taille) && (nombre_monstre > case_dispo))
	{
		cout << "test nombre monstres: " << nombre_monstre;
		cout << "test case dispo: " << case_dispo;
		cout << "Combien de monstres voulez-vous sur la carte?";
		s_input = long_input();
		nombre_monstre = atoi(s_input.c_str());
	}

	setNbrMonstre(nombre_monstre);

	while (i <= nombre_monstre)
	{
		cout << "Choisissez la premiere coordonnée où le monstre doit apparaître :";
		s_input = long_input();
		coordonneemonstre1 = atoi(s_input.c_str());


		cout << "Choisissez la deuxieme coordonnée où le monstre doit apparaître :";
		s_input = long_input();
		coordonneemonstre2 = atoi(s_input.c_str());

		if (coordonneemonstre1 < taille && coordonneemonstre2 < taille && coordonneemonstre1 >= 0 && coordonneemonstre2 >= 0)
		{
			if (plateau[coordonneemonstre1][coordonneemonstre2] == "v")
			{
				plateau[coordonneemonstre1][coordonneemonstre2] = "m";
				i++;
			}
			else
			{
				puts("Cette case est déjà occupée, veuillez en choisir une autre ");
			}
		}
		else
		{
			puts("Vos coordonnées sont hors de la carte!!");
		}
	}
	case_dispo = case_dispo - nbr_monstre;
}

void Carte :: affichage_normal()
{
	for (int i=0; i<taille; i++)
	{
		for (int j=0; j<taille; j++)
		{
			cout << plateau[i][j];
		}
		cout << endl;
	}
}

int Carte::nbLigneFichier(string nomFichier) //Compte le nb de ligne du fichier pour créer l'identifiant unique d'un monstre
{
	ifstream fichier(nomFichier.c_str()); //Ouverture en mode lecture
	int nbLigne = 0;
	if(fichier)
	{
		string ligne="";

		while(getline(fichier, ligne)) //Stockage de chaque ligne du fichier
		{
			nbLigne++;
		}
		fichier.close(); //On ferme le fichier
	}

	else
	{
		cerr << "Impossible d'ouvrir le fichier." << endl;
	}

	return nbLigne;
}

void Carte::saisie()
{
	// Nom de la carte
	string carte = "fichierCarte.txt" ;
	string type_obstacle = "";
	string monstre = "";
	int nbligne=nbLigneFichier(carte);

	//ouverture du fichier en écriture
	ofstream fichier(carte, ios :: app) ;

	// Si fichier bien ouvert
	if (fichier)
	{
		fichier << "c" << nbligne << "|";
		fichier << nom << "|";
		fichier << description << "|";
		fichier << taille << "|";
		fichier << nbr_monstre << "|";

		for (int i = 0 ; i < taille; i++)
		{
			for (int j = 0 ; j < taille ; j++)
			{
				if (plateau[i][j]=="o")
				{
					cout << "Quel est l'obstacle à la case ("<< i << ","<< j << "): ";
					type_obstacle = long_input();

					fichier << "(" << i << "," << j << ","<< type_obstacle << ")";
				}
				if (plateau[i][j]=="m")
				{
					cout << "Quelle est l'id du monstre à la case ("<< i << ","<< j << "): ";
					monstre = long_input();
					fichier << "(" << i << "," << j << ","<< monstre << ")";
				}
				if (plateau[i][j]=="j")
					fichier << "(" << i << "," << j << ",joueur" << ")";
			}

		}
		fichier << '\r';
		fichier << '\n';
		// On referme le fichier
		fichier.close() ;
		cout << "Carte sauvegardée" << endl ;
	}
	else cerr << "Echec de la sauvegarde" << endl ;
	return ;
}

string Carte::carteString(string lettreCarte, string nomFichier) //Convertit toutes les caracs. d'un entite en string
{
	string ligneFichier = "";;

	//Génération ID
	int nbCarte = this -> nbLigneFichier(nomFichier.c_str());
	string sNbCarte;
	sNbCarte = toString(nbCarte);

	string carteId;
	carteId = lettreCarte + sNbCarte;
	//Fin génération ID


	//Génération obstacles / entités sur carte
	string allElements = "";

	for (int i = 0; i < taille; i++)
	{
		for (int j = 0; j < taille; j++)
		{
            if (plateau[i][j] != "v")
			{
				allElements += "(" + toString(i) + "," + toString(j) + "," + plateau[i][j] + ")";
			}
		}
	}

	ligneFichier = carteId + "|" + nom + "|" + description + "|" + toString(taille) + "|" + toString(nbr_monstre) + "|" + allElements;

	return ligneFichier;
}

void Carte::saveInFile(string lettreCarte, string nomFichier) //Ecrit les carac d'un entite dans un fichier
{
	ofstream fichiercarte(nomFichier.c_str(), ios::out | ios::app); // Ouverture du fichier en écriture, avec curseur en fin de fichier.

	string carteLigne = this->carteString(lettreCarte, nomFichier);

	if(fichiercarte) //Vérification ouverture du fichier
	{
		fichiercarte << carteLigne; //Ecriture de la ligne
		fichiercarte.close();
	}

	else
	{
		cerr << "Impossible d'ouvrir le fichier." << endl;
	}
}

string Carte::getName()
{
    return this->nom;
}

string Carte::getDescription()
{
    return this->description;
}

void Carte::setTaille(int taille)
{
	cout << "TAILLE DEMANDEE : " << taille << endl;
	this->taille = taille;
	cout << "TAILLE ASSIGNéE : " << this->taille << endl;
}

void Carte::setName(string name)
{
	nom = name;
}

void Carte::setDescription(string desc)
{
	description = desc;
}

void Carte::setPlateau(int taille)
{
	plateau = new string * [taille];

	for (int i = 0; i < taille ; i++)
	{
		plateau[i] = new string [taille];
	}
}

void Carte::setCase(int i, int j, string value)
{
	plateau[i][j] = value;
	if (value == "joueur")
		io::setPlayerPosition(i,j);
}

void Carte::setNbrMonstre(int nbr_monstre)
{
	this -> nbr_monstre = nbr_monstre;
}

void Carte::setCaseDispo(int case_dispo)
{
	this -> case_dispo = case_dispo;
}

Carte Carte::operator=(const Carte a_copier)
{
	this -> id = a_copier.id;
	this -> nom = a_copier.nom;
	this -> description = a_copier.description;
	this -> taille = a_copier.taille;

	delete [] this -> plateau;
	this -> plateau = new string * [taille];

	for (int i = 0; i < taille; i++)
	{
		this -> plateau[i] = new string [taille];
	}

	for (int i = 0; i < taille; i++)
	{
		for (int j = 0; j < taille; j++)
		{
			this -> plateau[i][j] = a_copier.plateau[i][j];
		}
	}

	this -> nbr_monstre = a_copier.nbr_monstre;
	this -> case_dispo = a_copier.case_dispo;

	return * this;
}

bool Carte::caseAccessible(int i, int j)
{
	if (i < 0 || i > taille || j < 0 || j > taille)
		return false;
	return plateau[i][j] == "v";
}

void Carte::afficher_detail()
{
	cout << endl << endl << "Détails de la carte " << nom << endl << endl;
	cout << "Taille: " << taille << " * " << taille << " = " << taille * taille << " cases au total." << endl;
	cout << "Nombre total de monstres sur la carte: " << nbr_monstre << endl;
	cout << "Description: " << description << endl;

	cout << endl;
}

void Carte::afficher_brut()
{
    cout << nom << ", " << taille * taille << " cases, " << nbr_monstre << " monstres" << endl;
}
