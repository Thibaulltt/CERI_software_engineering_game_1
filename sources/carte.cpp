#include "../headers/carte.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <string>

using namespace std;

Carte :: Carte()
{
	this->nom = "";
	this->description = "";
	this->nbr_monstre = 0 ;
	this->case_dispo = 0;
}

Carte :: Carte (int taille, string name, string desc)
{
	this->taille = verif_taille(taille);
	this->nom = name;
	this->description = desc;

	this->plateau = new string * [taille];
	for (int i = 0; i < taille ; i++)
	{
		plateau[i] = new string [taille];
	}
	this -> case_dispo = taille*taille;
}


int Carte::verif_taille(int taille)
{
	while ( taille < 4  || taille > 255)
	{
		cout << "Taille impossible, veuillez choisir une taille entre 5 et 255 "<<endl << "choix de la taille :" << endl;
		cin >> taille;
	}
	return taille;
}

void Carte :: coordonneejoueur()
{
	int coordonneejoueur1;
	int coordonneejoueur2;
	bool placement_fait = false;
	while (placement_fait==false)
	{
		cout << "Choisissez la premiere coordonnée où le joueur doit apparaître :" ;
		cin >> coordonneejoueur1;
		cout << "Choisissez la deuxieme coordonnée où le joueur doit apparaître :" ;
		cin >> coordonneejoueur2;
		if (coordonneejoueur1 < taille && coordonneejoueur2 < taille)
		{
			plateau[coordonneejoueur1][coordonneejoueur2]="j";
			placement_fait=true;
		}
		else
		{
			cout << "Vos coordonnées sont hors de la carte!!" << endl;
		}
	}
	case_dispo = case_dispo - 1;
}

void Carte::coordonneeobstacle()
{
	int nbr_obstacle=0;
	int coordonneeobstacle1;
	int coordonneeobstacle2;
	cout<< "Combien d'obstacle voulez-vous sur la carte?";
	cin >> nbr_obstacle;
	while (nbr_obstacle >= case_dispo)
	{
		cout<< "Vous avez choisi trop d'obstacles." << endl << "Combien d'obstacles voulez-vous sur la carte?";
		cin >> nbr_obstacle;
	}
	int i = 1;
	while (i <= nbr_obstacle)
	{
		cout << "Choisissez la premiere coordonnée où l'obstacle doit apparaître :" ;
		cin >> coordonneeobstacle1;
		cout << "Choisissez la deuxieme coordonnée où l'obstacle doit apparaître :" ;
		cin >> coordonneeobstacle2;
		if (coordonneeobstacle1 < taille && coordonneeobstacle2 < taille)
		{
			if (plateau[coordonneeobstacle1][coordonneeobstacle2] == "v")
			{
				plateau[coordonneeobstacle1][coordonneeobstacle2] = "o";
				i++;
			}
			else
			{
				cout << "Cette case est deja occupée, veuillez en choisir une autre " << endl;
			}
		}
		else
		{
			cout << "Vos coordonnées sont hors de la carte!!" << endl;
		}
	}
	case_dispo = case_dispo - nbr_obstacle;
}

void Carte::coordonneemonstre()
{
	int nombre_monstre = 0;
	int coordonneemonstre1;
	int coordonneemonstre2;
	while ((nombre_monstre < taille) || (nombre_monstre > case_dispo))
	{
		cout<< "Combien de monstre voulez-vous sur la carte?";
		cin >> nombre_monstre;
	}
	this -> nbr_monstre = nombre_monstre;
	int i = 1;
	while (i <= nombre_monstre)
	{
		cout << "Choisissez la premiere coordonnée où le monstre doit apparaître :" ;
		cin >> coordonneemonstre1;
		cout << "Choisissez la deuxieme coordonnée où le monstre doit apparaître :" ;
		cin >> coordonneemonstre2;
		if (coordonneemonstre1 < taille && coordonneemonstre2 < taille)
		{
			if (plateau[coordonneemonstre1][coordonneemonstre2] == "v")
			{
				plateau[coordonneemonstre1][coordonneemonstre2] = "m";
				i++;
			}
			else
			{
				cout << "Cette case est deja occupée, veuillez en choisir une autre " << endl;
			}
		}
		else
		{
			cout << "Vos coordonnées sont hors de la carte!!" << endl;
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


void Carte::sauvegarde()
{
	// Nom de la carte
	string carte = "fichierCarte.txt" ;
	string type_obstacle;
	string monstre;
	int nbligne=nbLigneFichier(carte);

	//ouverture du fichier en écriture
	ofstream fichier(carte, ios :: app) ;

	// Si fichier bien ouvert
	if (fichier)
	{
		fichier << "c" << nbligne << "|" ;
		fichier << nom << "|" ;
		fichier << description << "|";
		fichier << taille << "|";
		for (int i = 0 ; i < taille; i++)
		{
			for (int j = 0 ; j < taille ; j++)
			{
				if (plateau[i][j]=="o")
				{
					cout << "Quel est l'obstacle à la case "<< i << " "<< j << ":";
					cin >> type_obstacle;
					fichier << "(" << i << "," << j << ","<< type_obstacle << ")";
				}
				if (plateau[i][j]=="m")
				{
					cout << "Quel est le monstre à la case "<< i << " "<< j << ":";
					cin >> monstre;
					fichier << "(" << i << "," << j << ","<< monstre << ")";
				}
				if (plateau[i][j]=="j")
					fichier << "(" << i << "," << j << ",joueur" << ")";
			}

		}
		fichier << '\n' ;
		// On referme le fichier
		fichier.close() ;
		cout << "Carte sauvegardée" << endl ;
	}
	else cerr << "Echec de la sauvegarde" << endl ;
	return ;
}

string Carte :: getName()
{
	return this->nom;
}

string Carte :: getDescription()
{
	return this->description;
}

void Carte::setTaille(int taille)
{
	this -> taille = taille;
}

void Carte :: setName(string name)
{
	nom = name;
}

void Carte :: setDescription(string desc)
{
	description = desc;
}

void Carte :: setPlateau(int taille)
{
	plateau = new string * [taille];

	for (int i = 0; i < taille ; i++)
	{
		plateau[i] = new string [taille];
	}
}

void Carte :: setCase(int i, int j, string value)
{
	plateau[i][j] = value;
	if (value == "joueur")
		io::setPlayerPosition(i,j);
}

void Carte :: setNbrMonstre(int nbr_monstre)
{
	this -> nbr_monstre = nbr_monstre;
}

void Carte :: setCaseDispo(int case_dispo)
{
	this -> case_dispo = case_dispo;
}

Carte Carte::operator=(const Carte & a_copier)
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
	cout << "Nombre d'obstacles présents sur la carte: " << case_dispo << endl;
	cout << "Description: " << description << endl;

	cout << endl;
}
