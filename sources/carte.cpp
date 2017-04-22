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
	this->plateau = new string * ;
	this -> case_dispo = 0;
}

Carte :: Carte (int size, string name, string desc)
{
	verif_taille(size);
	this->nom = name;
	this->description = desc;
	this->plateau = new string * [taille];
	for (int i = 0; i < taille ; i++)
	{
		plateau[i] = new string [taille];
		for (int j = 0 ; j< taille ; j++)
		{
			plateau[i][j] = "v" ;

		}
	}
	this -> case_dispo= taille*taille;
}


void Carte::verif_taille(int size)
{
	while ( size < 4  || size > 255)
	{
		cout << "Taille impossible veuillez choisir une taille entre 5 et 255 "<<endl << "choix de la taille :" << endl;
		cin >> size;
	}
	this-> taille=size;
}

void Carte :: coordonneejoueur()
{
	int coordonneejoueur1;
	int coordonneejoueur2;
	bool placement_fait = false;
	while (placement_fait==false)
	{
		cout << "Choisissez la premiere coordonnée où le joueur doit apparaitre :" ;
		cin >> coordonneejoueur1;
		cout << "Choisissez la deuxieme coordonnée où le joueur doit apparaitre :" ;
		cin >> coordonneejoueur2;
		if (coordonneejoueur1 < taille && coordonneejoueur2 < taille)
		{
			plateau[coordonneejoueur1][coordonneejoueur2]="j";
			placement_fait=true;
		}
		else
		{
			cout << "vos coordonnées sont hors de la carte!!" << endl;
		}
	}
	case_dispo = case_dispo - 1;
}

void Carte::coordonneeobstacle()
{
	int nbr_obstacle=0;
	int coordonneeobstacle1;
	int coordonneeobstacle2;
	cout<< "Combien d'obstacles voulez vous sur la carte?";
	cin >> nbr_obstacle;
	while (nbr_obstacle >= case_dispo)
	{
		cout<< "Vous avez choisi trop d'obstacles." << endl << "Combien d'obstacle voulez vous sur la carte?";
		cin >> nbr_obstacle;
	}
	int i = 1;
	while (i <= nbr_obstacle)
	{
		cout << "Choisissez la premiere coordonnée où l'obstacle doit apparaitre :" ;
		cin >> coordonneeobstacle1;
		cout << "Choisissez la deuxieme coordonnée où l'obstacle doit apparaitre :" ;
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
				cout << "Cette case est deja occupée, Veuillez en choisir une autre " << endl;
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
				cout << "Cette case est deja occupée veuillez en choisir une autre " << endl;
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


void Carte :: sauvegarde()
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
					cout << "Quelle est l'obstacle à la case "<< i << " "<< j << ":";
					cin >> type_obstacle;
					fichier << "(" << i << "," << j << ","<< type_obstacle << ")";
				}
				if (plateau[i][j]=="m")
				{
					cout << "Quelle est le monstre à la case "<< i << " "<< j << ":";
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
	else cerr << "échec de la sauvegarde" << endl ;
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




vector <Carte> Carte :: chargement ()
{
	vector <Carte> selectionnable ;
	ifstream fichier("fichierCarte.txt", ios :: in) ;
	if (fichier)
	{
		string current_line;
		Carte carte_temporaire ;
		while (getline(fichier, current_line))
		{
			string id = "" ;
			string nom = "" ;
			string description = "" ;
			string taille= "";
			string coordonnee1 = "" ;
			string coordonnee2 = "" ;
			string type = "" ;
			int count = 0 ;
			int count_coordonnee = 0 ;
			int i = 0 ;

			while (current_line[i+1] != '\0')
			{
				char tmp = current_line[i] ;
				if (tmp == '|')
				{
					count ++ ;
					i++ ;
				}
				else if (count == 0)
				{
					id = id + tmp ;
					i++ ;
				}
				else if (count == 1)
				{
					nom = nom + tmp ;
					i++ ;
				}
				else if (count == 2)
				{
					description = description + tmp ;
					i++ ;
				}
				else if (count == 3)
				{
					taille = taille + tmp ;
					i++ ;
				}
				int t = atoi(taille.c_str());
				carte_temporaire.taille = t ;
				carte_temporaire.nom = nom ;
				carte_temporaire.description = description ;
				if (count == 4)
				{
					if (tmp == ')')
					{
						count_coordonnee = 0 ;
						i++ ;
						int coor1 = atoi(coordonnee1.c_str()) ;
						int coor2 = atoi(coordonnee1.c_str()) ;
						carte_temporaire.plateau[coor1][coor2]= type;
					}
					else if (tmp == ',')
					{
						count_coordonnee ++ ;
						i++ ;
					}
					else if (tmp == '(')
					{
						i ++ ;
					}
					else if ((tmp != '(') && (tmp != ')') && (tmp != ','))
					{
						if (count_coordonnee == 0)
						{
							coordonnee1 = coordonnee1 + tmp ;
							i ++ ;
						}
						else if (count_coordonnee == 1)
						{
							coordonnee2 = coordonnee2 + tmp ;
							i++ ;
						}
						else if (count_coordonnee == 2)
						{
							type = type + tmp ;
							i++ ;
						}
					}
				}
			}
		}
		selectionnable.push_back(carte_temporaire) ;
	}
	return selectionnable ;
}




