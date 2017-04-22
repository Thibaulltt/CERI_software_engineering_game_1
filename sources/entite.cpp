#include "../headers/entite.h"
#include <iostream>
#include <fstream>

using namespace std;


// --------------------CONSTRUCTEURS

entite::entite()      //Constructeur ventiteIde
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
	this->entiteDescription = "";
	this->entiteHpMax = entiteHpMax;
	this->entiteHpCurrent = this->entiteHpMax;
	this->entiteManaMax = entiteManaMax;
	this->entiteManaCurrent = entiteManaMax;
	this->entiteSpeed = entiteSpeed;
	this->entiteAlive = true;
	vector<competence> entiteSkillVect = allSkills;
}


//-------------------------------------------FONCTIONS


template<typeentiteName T>string entite::toString( const T & valeur ) //Conversion de n'importe quoi en string
{
	ostringstream flux;
	flux << valeur;
	return flux.str();
}


//-----GET ATTRIBUTS

string entite::getEntiteId() //Rretourne l'entiteId d'une entite
{
	return this->entiteId;
}


string entite::getentiteName() //Retourne le nom d'une entite
{
	return this->entiteName;
}


string entite::getEntiteDescription() //Retourne la entiteDescription d'une entite
{
	return this->entiteDescription;
}


int entite::getEntiteHpMax() //Retourne le nombre de points de vie max d'une entite
{
	return this->entiteHpMax;
}


int entite::getEntiteHpCurrent() //Retourne le nombre de points de vie actuel d'une entite
{
	return this->entiteHpCurrent;
}


int entite::getEntiteManaMax() //Retourne les points de mana MAX d'une entite
{
	return this->entiteManaMax;
}

int entite::getEntiteManaCurrent() //Retourne les points de mana actuel d'une entite
{
	return this->entiteManaCurrent;
}


int entite::getEntiteSpeed() //Retourne la vitesse d'une entite
{
	return this->entiteSpeed;
}


bool entite::getEntiteAlive() //Retourne l'�tat de vie ou de mort d'un entite
{
	return this->entiteAlive;
}


vector<competence> entite::getEntiteSkillVect() //Retourne le vecteur de compétence d'un entite
{
	return this->entiteSkillVect;
}


// POUR SAUVEGARDE DANS FICHIER


int entite::nbLigneFichier(string nomFichier) //Compte le nb de ligne du fichier pour créer l'entiteIdentifiant unique d'un entite
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


voentiteId entite::saveInFile(string lettreEntite,string nomFichier) //Ecrit les carac d'un entite dans un fichier
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


bool entite::enleverVie(int degats)
{
	this->entiteHpCurrent-=degats;

	if(this->entiteHpCurrent <= 0)
	{
		this->entiteAlive = false;
		return true; //Si mort, return true
	}
	return false;
}

///Problème ici, si la dépense de mana n'est pas possible, la mana est quand même dépensée.
///De même, <= 0 empêche d'utiliser les compétences qui utilisent exactement le bon montant de mana.
bool entite::enleverMana(int manaCost)
{
	if (this->entiteManaCurrent>= manaCost)
	{
		this->entiteManaCurrent -= manaCost;
		return true;
	}

	if(this->entiteManaCurrent < manaCost)
	{
		return false;
	}
}


// TESTS


voentiteId entite::printEntite()
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
