#include <fstream>
#include <iostream>
#include "../headers/entite.h"

using namespace std;


// --------------------CONSTRUCTEURS

entite::entite()      //Constructeur vide
{
	this->entiteId="";
	this->entiteName = "Inconnu";
	this->entiteDescription = "";
	this->entiteHpMax = 0;
	this->entiteHpCurrent = entiteHpMax;
	this->entiteManaMax = 0;
	this->entiteManaCurrent = 0;
	this->entiteSpeed = 0;
	this->entiteAlive = true;
	vector<competence> entiteSkillVect;
}


entite::entite(string entiteId, string entiteName, int entiteHpMax, int entiteSpeed, int entiteManaMax, string entiteDescription, std::vector<competence> allSkills) //Constructeur avec arguments de caractéristiques du entite
{
	this->entiteId=entiteId;
	this->entiteName = entiteName;
	this->entiteDescription = entiteDescription;
	this->entiteHpMax = entiteHpMax;
	this->entiteHpCurrent = this->entiteHpMax;
	this->entiteManaMax = entiteManaMax;
	this->entiteManaCurrent = entiteManaMax;
	this->entiteSpeed = entiteSpeed;
	this->entiteAlive = true;
	this->entiteSkillVect = allSkills;
}


//-------------------------------------------FONCTIONS


template<typename T>string entite::toString( const T & valeur ) //Conversion de n'importe quoi en string
{
	ostringstream flux;
	flux << valeur;
	return flux.str();
}


//-----GET ATTRIBUTS

string entite::getID() //Rretourne l'id d'une entite
{
	return this->entiteId;
}


string entite::getName() //Retourne le nom d'une entite
{
	return this->entiteName;
}


string entite::getDescription() //Retourne la description d'une entite
{
	return this->entiteDescription;
}


int entite::getHpMax() //Retourne le nombre de points de vie max d'une entite
{
	return this->entiteHpMax;
}


int entite::getHpCurrent() //Retourne le nombre de points de vie actuel d'une entite
{
	return this->entiteHpCurrent;
}


int entite::getManaMax() //Retourne les points de mana MAX d'une entite
{
	return this->entiteManaMax;
}

int entite::getManaCurrent() //Retourne les points de mana actuels d'une entite
{
	return this->entiteManaCurrent;
}


int entite::getSpeed() //Retourne la vitesse d'une entite
{
	return this->entiteSpeed;
}


bool entite::getAlive() //Retourne l'état de vie ou de mort d'une entite
{
	return this->entiteAlive;
}


vector<competence> entite::getSkillVect() //Retourne le vecteur de compétences d'un entite
{
	return this->entiteSkillVect;
}


// POUR SAUVEGARDE DANS FICHIER


int entite::nbLigneFichier(string nomFichier) //Compte le nb de lignes du fichier pour créer l'identifiant unique d'un entite
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


string entite::entiteString(string lettreEntite, string nomFichier) //Convertit toutes les caracs. d'un entite en string
{
	string ligneFichier;

	int nbEntite = this->nbLigneFichier(nomFichier.c_str());
	string sNbEntite;
	sNbEntite = toString(nbEntite);

	string entiteId;
	entiteId = lettreEntite + sNbEntite;

	string sentiteHpMax;
	sentiteHpMax = toString(this->entiteHpMax);

	string sentiteSpeed;
	sentiteSpeed = toString(this->entiteSpeed);

	string sentiteManaMax;
	sentiteManaMax = toString(this->entiteManaMax);

	string allSkill="";
	for (int i=0 ; i< entiteSkillVect.size() ; i++) //Conversion de toutes les compétences en une ligne de string
	{
		allSkill += entiteSkillVect[i].competenceString() + ":";
	}

		ligneFichier = entiteId + "/" + this->entiteName + "/" + sentiteHpMax + "/" + sentiteSpeed + "/" + allSkill + "|" + sentiteManaMax + "|" + this->entiteDescription + '\n'; //Création de la ligne compléte


	return ligneFichier;
}


void entite::saveInFile(string lettreEntite,string nomFichier) //Ecrit les carac d'un entite dans un fichier
{
	ofstream fichierentite(nomFichier.c_str(), ios::out | ios::app); // Ouverture du fichier en écriture, avec curseur en fin de fichier.

	string entiteLigne = this->entiteString(lettreEntite, nomFichier);

	if(fichierentite) //Vérification ouverture du fichier
	{
		fichierentite << entiteLigne; //Ecriture de la ligne
		fichierentite.close();
	}

	else
	{
		cerr << "Impossible d'ouvrir le fichier." << endl;
	}
}


// FONCTIONS


void entite::enleverVie(int degats)
{
	this->entiteHpCurrent-=degats;

	if(this->entiteHpCurrent <= 0)
	{
		this->entiteAlive = false;
	}
}


bool entite::enleverMana(int skillManaCost)
{
	if (this->entiteManaCurrent>= skillManaCost)
	{
		this->entiteManaCurrent -= skillManaCost;
		return true;
	}

	if(this->entiteManaCurrent < skillManaCost)
	{
		return false;
	}
}


// TESTS


void entite::printEntite()
{
	cout << "nom : " << this->entiteName<< endl;
	cout << "hp max : " << this->entiteHpMax<< endl;
	cout << "entiteSpeed : " << this->entiteSpeed<< endl;

	for (int i=0 ; i<this->entiteSkillVect.size() ; i++)
	{
		this->entiteSkillVect[i].printCompetence();
	}

	cout << endl;
}
