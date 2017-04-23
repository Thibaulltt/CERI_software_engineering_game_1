#include <iostream>	// à remplacer avec notre librairie I/O plus tard
#include <vector>
#include "../headers/carte.h"
#include "../headers/fonctionsjeu.h"

using namespace std;

jeu::jeu()
{
//	personnage jeu_perso = new personnage();		// À COMPLÉTER UNE FOIS QUE CLASSE PERSO FINIE
//	jeu_carte = new Carte();			// À COMPLÉTER UNE FOIS QUE CLASSE CARTE FINIE
//	jeu_nombre_monstre = 0;				// À COMPLÉTER UNE FOIS QUE CLASSE CARTE FINIE
//	// Normalement, à ca point là, la carte doit être chargée, le personnage est choisi et chargé, les monstres sont chargés et il ne reste qu'à lancer le jeu.
}

jeu::~jeu()
{}

Carte jeu::getCarte()
{
	return jeu_carte;
}

personnage jeu::getPerso()
{
	return jeu_perso;
}

vector<monstre> jeu::getMonstres()
{
	return jeu_monstres;
}

int jeu::getNbMonstres()
{
	return jeu_nombre_monstres;
}

void jeu::preparation_partie()
{
	bienvenue();

		//Choix personnage
	vector<personnage> tous_persos;							//Vecteur personnages
	personnage pers;										//Dummy identification type template
	string nom_file = "fichierPersonnage.txt";				//Nom fichier source personnages
	tous_persos = loadAllEntiteFromFile(pers, nom_file);	//Remplissage vecteur personnages depuis fichier
	jeu_perso = choix_unique_element(tous_persos);			//Choix + assignation personnage partie

		//Choix carte
	vector<Carte> toutes_cartes;							//Vecteur cartes
	nom_file = "fichierCarte.txt";					//Nom fichier source cartes
	toutes_cartes = loadAllCarteFromFile(nom_file);			//Chargement carte depuis fichier
	Carte jeu_carte = choix_unique_element(toutes_cartes);	//Choix + assignation carte partie

//		//Chargement monstres
//	vector<monstre> jeu_monstres;							//Vecteur monstres
//	monstre mons;											//Dummy identification type template
//	nom_file = "fichierMonstre.txt";						//Nom fichier source monstres
//	jeu_monstres = loadAllEntiteFromFile(mons, nom_file);	//Chargement monstres depuis fichier
}

bool sort_speed(entite a, entite b)
{
	return a.getSpeed() < b.getSpeed();
}
