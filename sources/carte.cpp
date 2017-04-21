#include "../headers/carte.h"
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

Carte :: Carte()
{

}

Carte :: Carte (int size, string name, string desc)
{
	this->nom = name;
	this->description = desc;
	this->taille = size ;
	this->plateau = new char * [taille];
	for (int i = 0; i < taille ; i++)
	{
		plateau[i] = new char [taille];
		for (int j = 0 ; j< taille ; j++)
		{
			plateau[i][j] = /*remplir client*/'?' ;
		}
	}
}

void Carte :: sauvegarde()
{
	// Nom de la carte
	string nom_de_la_carte ;
	string carte ;
	cout << "Choisir le nom de la carte : " << endl ;
	cin >> nom_de_la_carte ;
	carte = nom_de_la_carte + ".txt" ;

	// Vérification que le fichier n'existe pas déjà
	if (!carte_existe(carte))
	{
		//ouverture du fichier en écriture
		ofstream fichier(carte, ios :: out | ios :: trunc) ;

		// Si fichier bien créé
		if (fichier)
		{
			for (int i = 0 ; i < taille; i++)
			{
				for (int j = 0 ; j < taille ; j++)
				{
					fichier << plateau[i][j] ;
				}
				fichier << '\n' ;
			}
			// On referme le fichier
			fichier.close() ;
			cout << "Carte sauvegardée" << endl ;
		}
		else cerr << "Echec de la sauvegarde" << endl ;
		return ;
	}
	else
	{
		cout << "Nom existant" << endl ;
		sauvegarde() ;
	}

}


string Carte :: getName()
{
    return this->nom;
}

string Carte :: getDescription()
{
    return this->description;
}

bool Carte :: carte_existe(string nom)
{
	ifstream fichier(nom , ios :: in) ;
	if (fichier)
	{
		fichier.close() ;
		return true ;
	}
	else
	{
		fichier.close() ;
		return false ;
	}
}


void Carte :: chargement (string nom_selection)
{
	string carte = nom_selection + ".txt" ;
	if (carte_existe(carte))
	{
	    cout << "existe";
		ifstream fichier(carte, ios:: in) ;
		if (fichier)
		{
			this->taille = quel_taille(carte) ;
			for (int i = 0 ; i < taille ; i++ )
			{
				for (int j = 0 ; j < taille ; j++)
				{
					fichier >> plateau[i][j];
				}
			}
		}
	}
}

int Carte :: quel_taille(string nom)
{
	ifstream fichier(nom, ios :: in) ;
	int count = -1 ;
	char current ;
	while (current != '\n')
	{
		fichier.get(current) ;
		count ++ ;
	}
	fichier.close() ;
	return count ;
}

void Carte :: suppression(string nom)
{
	string nom_carte = nom + ".txt" ;
	//delete nom_carte ;
	if( carte_existe(nom_carte)) cout << "Echec de la suppression" << endl ;
	else cout << "Carte supprimée" << endl ;
}
