#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include "../headers/carte.h"
#include "../headers/io.h"

using namespace io;
using namespace std;

int Carte::nbElemProt = 0;

Carte::Carte()
{
	this->id = "";
	this->nom = "";
	this->description = "";
	this->taille = 0;
	this->plateau = NULL;
	this->nbr_monstre = 0 ;
	this->case_dispo = 0;

}

Carte::Carte (int taille, string name, string desc, int nb_monstre)
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

void Carte::coordonneejoueur()
{
	puts("- Choix placement joueur -");

	int coordonneejoueur1 = 0;
	int coordonneejoueur2 = 0;
	string s_input = "";
	int input = 0;

	puts("- Choix première coordonnée du joueur -");
	try
	{
		s_input = long_input();
		input = atoi(s_input.c_str());

		while (isNumber(s_input) == false || (input < 0 || input > taille - 1))
		{
			puts("\n Input incorrect! Réessayez!\n");
			puts("- Choix première coordonnée du joueur -");
			s_input = long_input();
			input = atoi(s_input.c_str());
		}
		coordonneejoueur1 = input;
	}
	catch (int longInputError)
	{
		std::cout << "Placement joueur quitté. Retour au menu principal." << std::endl;
		return;
	}

	puts("- Choix seconde coordonnée du joueur -");
	try
	{
		s_input = long_input();
		input = atoi(s_input.c_str());

		while (isNumber(s_input) == false || (input < 0 || input > taille - 1))
		{
			puts("\n Input incorrect! Réessayez!\n");
			puts("- Choix seconde coordonnée du joueur -");
			s_input = long_input();
			input = atoi(s_input.c_str());
		}
		coordonneejoueur2 = input;
	}
	catch (int longInputError)
	{
		std::cout << "Placement joueur quitté. Retour au menu principal." << std::endl;
		return;
	}

	plateau[coordonneejoueur1][coordonneejoueur2] = "j";
	case_dispo = case_dispo - 1;
}

void Carte::coordonneeobstacle()
{
	puts("- Choix obstacles -");

	int nbr_obstacle=0;
	int coordonneeobstacle1 = 0;
	int coordonneeobstacle2 = 0;
	int i = 1;
	string s_input = "";
	int input = 0;

	puts("- Choix nombre d'obstacles -");
	try
	{
		s_input = long_input();
		int input = atoi(s_input.c_str());

		while (isNumber(s_input) == false || (input < 0 || input >= case_dispo))
		{
			puts("\n Input incorrect! Réessayez!\n");
			puts("- Choix nombre d'obstacles -");
			s_input = long_input();
			input = atoi(s_input.c_str());
		}
		nbr_obstacle = input;
	}
	catch (int longInputError)
	{
		std::cout << "Placement obstacle quitté. Retour au menu principal." << std::endl;
		return;
	}

	while (i <= nbr_obstacle)
	{
		std::cout << "Placement obstacle quitté. Retour au menu principal." << std::endl;
		try
		{
			s_input = long_input();
			input = atoi(s_input.c_str());

			while (isNumber(s_input) == false || (input < 0 || input > taille - 1))
			{
				puts("\n Input incorrect! Réessayez!\n");
				puts("- Choix première coordonnée de l'obstacle -");
				s_input = long_input();
				input = atoi(s_input.c_str());
			}
			coordonneeobstacle1 = input;
		}
		catch (int longInputError)
		{
			std::cout << "Placement obstacle quitté. Retour au menu principal." << std::endl;
			return;
		}

		cout << "- Choix seconde coordonnée de l'obstacle " << i << " -\n";
		try
		{
			s_input = long_input();
			input = atoi(s_input.c_str());

			while (isNumber(s_input) == false || (input < 0 || input > taille - 1))
			{
				puts("\n Input incorrect! Réessayez!\n");
				cout << "- Choix seconde coordonnée de l'obstacle " << i << " -\n";
				s_input = long_input();
				input = atoi(s_input.c_str());
			}
			coordonneeobstacle2 = input;
		}
		catch (int longInputError)
		{
			std::cout << "Placement obstacle quitté. Retour au menu principal." << std::endl;
			return;
		}

		if (plateau[coordonneeobstacle1][coordonneeobstacle2] == "v")
		{
			plateau[coordonneeobstacle1][coordonneeobstacle2] = "o";
			i++;
		}
		else
		{
			puts("Cette case est deja occupée, veuillez en choisir une autre!");
		}
	}
	case_dispo = case_dispo - nbr_obstacle;
}

void Carte::coordonneemonstre()
{
	puts("- Choix monstres -");;

	int nbr_monstre = 0;
	int coordonneemonstre1 = 0;
	int coordonneemonstre2 = 0;
	int i = 1;
	std::string s_input = "";
	int input = 0;

	puts("- Choix nombre de monstres -");
	try
	{
		s_input = long_input();
		int input = atoi(s_input.c_str());

		while (isNumber(s_input) == false || input <= taille || input >= case_dispo)
		{
			puts("\n Input incorrect! Réessayez!\n");
			puts("- Choix nombre de monstres -");
			s_input = long_input();
			input = atoi(s_input.c_str());
		}
		nbr_monstre = input;
	}
	catch (int longInputError)
	{
		std::cout << "Placement monstre quitté. Retour au menu principal." << std::endl;
		return;
	}

	while (isNumber(s_input) == false || nbr_monstre < taille || nbr_monstre > case_dispo)
	{
		puts("\n Input incorrect! Réessayez!\n");
		puts("- Choix nombre de monstres -");
		try
		{
			s_input = long_input();
		}
		catch (int longInputError)
		{
			std::cout << "Placement monstre quitté. Retour au menu principal." << std::endl;
			return;
		}
	}

	nbr_monstre = atoi(s_input.c_str());
	setNbrMonstre(nbr_monstre);

	while (i <= nbr_monstre)
	{
		cout << "- Choix première coordonnée du monstre " << i << " -\n";
		try
		{
			s_input = long_input();
			input = atoi(s_input.c_str());

			while (isNumber(s_input) == false || (input < 0 || input > taille - 1))
			{
				puts("\n Input incorrect! Réessayez!\n");
				cout << "- Choix première coordonnée du monstre " << i << " -\n";
				s_input = long_input();
				input = atoi(s_input.c_str());
			}
			coordonneemonstre1 = input;
		}
		catch (int longInputError)
		{
			std::cout << "Placement monstre quitté. Retour au menu principal." << std::endl;
			return;
		}

		cout << "- Choix seconde coordonnée du monstre " << i << " -\n";
		try
		{
			s_input = long_input();
			input = atoi(s_input.c_str());

			while (isNumber(s_input) == false || (input < 0 || input > taille - 1))
			{
				puts("\n Input incorrect! Réessayez!\n");
				cout << "- Choix seconde coordonnée du monstre " << i << " -\n";
				s_input = long_input();
				input = atoi(s_input.c_str());
			}
			coordonneemonstre2 = input;
		}
		catch (int longInputError)
		{
			std::cout << "Placement monstre quitté. Retour au menu principal." << std::endl;
			return;
		}

		if (plateau[coordonneemonstre1][coordonneemonstre2] == "v")
		{
			plateau[coordonneemonstre1][coordonneemonstre2] = "m";
			i++;
		}
		else
		{
			puts("Cette case est déjà occupée, veuillez en choisir une autre!");
		}
	}
	case_dispo = case_dispo - nbr_monstre;
}

void Carte::affichage_normal()
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
	int nbligne = nbLigneFichier(carte);
	int parc = 1;
	string s_input = "";
	int input = 0;

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


		//Choix joueur + obstacles
		for (int i = 0 ; i < taille; i++)
		{
			for (int j = 0 ; j < taille ; j++)
			{
				if (plateau[i][j]=="j")
				{
					fichier << "(" << i << "," << j << ",joueur" << ")";
				}
				if (plateau[i][j]=="o")
				{
					cout << "- Choix obstacle " << parc << "[case ("<< i << ","<< j << ")] -\n";
					parc++;
					try
					{
						type_obstacle = long_input();
					}
					catch (int longInputError)
					{
						std::cout << "Saisie obstacle quittée. Retour au menu principal." << std::endl;
						return;
					}

					fichier << "(" << i << "," << j << ","<< type_obstacle << ")";
				}
			}
		}


		if (nbr_monstre > 0)
		{
			puts("- Monstres disponibles -");

			monstre duh;
			vector<monstre> vect_monstre;

			vect_monstre = loadAllEntiteFromFile(duh, "fichierMonstre.txt");

			for (int i = 0; i < vect_monstre.size(); i++)
			{
				cout << i + 1 << "- ";
				vect_monstre[i].afficher_brut();
				cout << "\n";
			}

			for (int i = 0 ; i < taille; i++)
			{
				for (int j = 0 ; j < taille ; j++)
				{
					if (plateau[i][j]=="m")
					{
						cout << "- Choix numéro du monstre de la case ("<< i << ","<< j << ") -\n";
						try
						{
							s_input = long_input();
							input = atoi(s_input.c_str());

							while (isNumber(s_input) == false || input > vect_monstre.size())
							{
								puts("\n Input incorrect! Réessayez!\n");
								cout << "- Choix numéro du monstre de la case ("<< i << ","<< j << ") -\n";
								s_input = long_input();
								input = atoi(s_input.c_str());
							}
						}
						catch (int longInputError)
						{
							std::cout << "Placement monstre quitté. Retour au menu principal." << std::endl;
							return;
						}

						fichier << "(" << i << "," << j << "," << vect_monstre[input - 1].getID() << ")";
					}
				}
			}
		}

		fichier << "\r\n";
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

	ligneFichier = carteId + "|" + nom + "|" + description + "|" + toString(taille) + "|" + toString(nbr_monstre) + "|" + allElements + "\r\n";

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
	this->taille = taille;
}

void Carte::setId(std::string id)
{
    this -> id = id;
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
	if (value.find("joueur") != std::string::npos)
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
	if (i < 0 || j < 0)
		return false;
	if (i >= taille || j >= taille)
		return false;
	if (plateau[i][j].find("joueur") != std::string::npos)
		return true;
	if (plateau[i][j][0] == 'm')
		return true;
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

void Carte::echangerContenuCase(int i1, int j1, int i2, int j2)
{
	std::string old_content = plateau[i1][j1];
	std::string new_content = plateau[i2][j2];
	if (plateau[i2][j2][0] == 'v')	// Si la case a atteindre est vide
		plateau[i2][j2] = "joueur";	// On met le joueur la
	else	// Sinon (la case contient qqchose qui a été rendu accessible (monstre par exemple)).
		plateau[i2][j2] = std::string(plateau[i2][j2]+"/"+old_content);	// On rajoute "/joueur" a la fin de la chaîne
	if (old_content == "joueur")	// Si la case d'origine ne contenait que le joueur
		plateau[i1][j1] = "v";	// La case devient vide
	else				// Si la case d'origine contenait qqchose d'autre que le joueur
		plateau[i1][j1] = plateau[i1][j1].substr(0,plateau[i1][j1].find("/"));	// On enlève "/joueur" de la fin de la chaîne si il existe
	return;
}

void Carte::monstreMort(int x, int y)
{
	if (plateau[x][y][0] == 'm')
	{
		plateau[x][y] = 'x'+plateau[x][y];
		nbr_monstre--;
	}
	return;
}
