#include "../headers/personnage.h"
#include <fstream>

using namespace std;

//FONCTIONS GET ATTRIBUTS PERSONNAGE


int personnage::getManaMax() //Retourne les points de mana MAX d'un perso
{
	return this->manaMax;
}

int personnage::getManaCurrent() //Retourne les points de mana actuel d'un perso
{
	return this->manaCurrent;
}

string personnage::getDescription() //Retourne la description d'un personnage
{
	return this->description;
}


//FONCTIONS DE SAUVEGARDE DE PERSONNAGES


string personnage::personnageString() //Convertit toutes les caracs. d'un personnage en string
{
	string ligneFichier;

	int nbPerso = this->nbLigneFichier("fichierPersonnage.txt");
	string sNbPerso;
	sNbPerso = toString(nbPerso);

	string ID;
	ID = "p" + sNbPerso;

	string sHpMax;
	sHpMax = toString(this->hpMax);

	string sSpeed;
	sSpeed = toString(this->speed);

	string sManaMax;
	sManaMax = toString(this->manaMax);

	string allSkill="";

	for (int i=0 ; i<skillVect.size() ; i++) //Conversion de toutes les compétences en une ligne de string
	{
		allSkill += skillVect[i].competenceString() + ":";
	}

	ligneFichier = ID + "/" + this->name + "/" + sHpMax + "/" + sSpeed + "/" + allSkill + "|" + sManaMax + "|" + this->description + '\n'; //Création de la ligne compléte

	return ligneFichier;
}


void personnage::savePersoInFile() //Ecrit les carac d'un personnage dans un fichier
{
	ofstream fichierPersonnage("fichierPersonnage.txt", ios::out | ios::app); // Ouverture du fichier en écriture, avec curseur en fin de fichier.

	string persoLigne = this->personnageString();

	if(fichierPersonnage) //Vérification ouverture du fichier
	{
		fichierPersonnage << persoLigne; //Ecriture de la ligne
		fichierPersonnage.close();
	}

	else
	{
		cerr << "Impossible d'ouvrir le fichier." << endl;
	}
}


//FONCTIONS DE JEU PERSONNAGE

///Problème ici, si la dépense de mana n'est pas possible, la mana est quand même dépensée
bool personnage::enleverMana(int manaCost)
{
	this->manaCurrent -= manaCost;
	if(this->manaCurrent <=0)
	{
		return false;
	}

	return true;
}


//FONCTIONS DE TEST



void personnage::printPersonnage()
{
	cout << "nom : " << this->name<< endl;
	cout << "hp max : " << this->hpMax<< endl;
	cout << "speed : " << this->speed<< endl;
	cout << "mana max : " << this->manaMax<<endl;
	cout << "description : " <<this->description<<endl;

	for (int i=0 ; i<3 ; i++)
	{
		this->skillVect[i].printCompetence();
	}

	cout << endl;
}
